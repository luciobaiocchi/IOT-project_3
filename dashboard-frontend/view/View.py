import matplotlib
matplotlib.use('TkAgg')
import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from datetime import datetime
from aiohttp import ClientSession
import asyncio

class TemperatureDashboard:
    def __init__(self, connection, loop):
        self.connection = connection
        self.loop = loop
        self.root = tk.Tk()
        self.root.tk.call('tk', 'scaling', 2.0)
        self.start_time = datetime.now()  # Tempo iniziale
        self.elapsed_times = []           # Lista tempi trascorsi
        self.temperatures = []            # Lista temperature
        self.status_history = []          # Lista stati
        self.opening_level = 0
        self.mode = "AUTOMATIC"
        self._setup_gui()
        self.schedule_auto_update()

    def _setup_gui(self):
        self.root.title("Monitor Temperatura")
        self.root.geometry("1200x800")
        
        main_container = tk.Frame(self.root)
        main_container.pack(fill=tk.BOTH, expand=True, padx=20, pady=20)
        
        self.figure = Figure(figsize=(10, 6), dpi=100)
        self.ax = self.figure.add_subplot(111)
        self.canvas = FigureCanvasTkAgg(self.figure, master=main_container)
        self.canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)
        
        button_frame = tk.Frame(main_container)
        button_frame.pack(pady=10)
        
        tk.Button(button_frame, text="Change mode", command=self.change_mode,
                 font=('Helvetica', 12), padx=15, pady=10).pack(side=tk.LEFT, padx=10)

        tk.Button(button_frame, text="Stop Allarm", command=self.stop_alarm,
                 font=('Helvetica', 12), padx=15, pady=10).pack(side=tk.LEFT, padx=10)


    def update_data(self):
        async def async_update():
            async with ClientSession() as session:
                try:
                    data = await self.connection.get_data(session)
                    # Calcola tempo trascorso dall'avvio
                    elapsed = (datetime.now() - self.start_time).total_seconds()
                    self.elapsed_times.append(elapsed)
                    
                    # Estrai ultimi valori
                    latest = data[-1]
                    self.temperatures.append(latest['val'])
                    self.status_history.append(latest['tst'])

                    self.opening_level = latest['opn']
                    self.mode = latest['main_state']
                    
                    # Filtra i dati degli ultimi 30 secondi
                    current_time = self.elapsed_times[-1]
                    last_30_seconds = [t for t in self.elapsed_times if t >= current_time - 30]
                    last_30_temps = self.temperatures[-len(last_30_seconds):]
                    last_30_status = self.status_history[-len(last_30_seconds):]
                    
                    # Calcola valore medio
                    avg_temp = sum(last_30_temps) / len(last_30_temps) if last_30_temps else 0
                    
                    # Aggiorna grafico con dati degli ultimi 30 secondi
                    self.root.after(0, lambda: self._update_plot(
                        last_30_seconds,
                        last_30_temps,
                        max(last_30_temps) if last_30_temps else 0,
                        min(last_30_temps) if last_30_temps else 0,
                        avg_temp,
                        last_30_status[-1] if last_30_status else "N/A",
                        self.opening_level,
                        self.mode
                    ))
                except Exception as e:
                    print(f"Errore: {e}")
        asyncio.run_coroutine_threadsafe(async_update(), self.loop)

    def _update_plot(self, times, temps, current_max, current_min, avg_temp, current_status, opening_level, mode):
        self.ax.clear()
        
        # Ultimo valore
        latest_temp = temps[-1] if temps else "N/A"

        # Plot dati principali
        self.ax.plot(times, temps, marker='o', linestyle='-', color='#2c7bb6', label='Temperatura')
        
        # Linee max/min
        self.ax.axhline(current_max, color='#d7191c', linestyle='--', label=f'Max: {current_max}°C')
        self.ax.axhline(current_min, color='#1a9641', linestyle='--', label=f'Min: {current_min}°C')
        
        # Linea media
        self.ax.axhline(avg_temp, color='#fdae61', linestyle='-.', label=f'Avg: {avg_temp:.2f}°C')
        
        # Informazioni a destra
        textstr = (f"Latest: {latest_temp}°C\n"
                   f"Max: {current_max}°C\n"
                   f"Min: {current_min}°C\n"
                   f"Avg: {avg_temp:.2f}°C\n"
                   f"Status: {current_status}\n"
                   f"Opening Level: {opening_level}\n"
                   f"Mode: {mode}")
        self.ax.text(
            1.05, 0.5, textstr, 
            transform=self.ax.transAxes,
            va='center',
            bbox=dict(facecolor='white', alpha=0.5)
        )
        
        # Formattazione assi
        self.ax.set_xlabel("Tempo trascorso (s)")
        self.ax.set_ylabel("Temperatura (°C)")
        self.ax.set_title("Andamento Temperatura (Ultimi 30 secondi)")
        self.ax.grid(True, alpha=0.3)
        self.ax.legend(loc='upper left')
        
        self.figure.tight_layout()
        self.canvas.draw()

    def schedule_auto_update(self):
        self.root.after(500, self.schedule_auto_update)
        self.update_data()

    def change_mode(self):
        async def async_post_mode():
            async with ClientSession() as session:
                await self.connection.post_mode(session, "new_mod")
        asyncio.run_coroutine_threadsafe(async_post_mode(), self.loop)
        
    def stop_alarm(self):
        async def async_post_mode():
            async with ClientSession() as session:
                await self.connection.post_alarm(session, "stop_alarm")
        asyncio.run_coroutine_threadsafe(async_post_mode(), self.loop)
