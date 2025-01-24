# view/View.py
import matplotlib
matplotlib.use('TkAgg')  # Forza il backend prima di ogni import

import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from datetime import datetime


class TemperatureDashboard:
    def __init__(self, connection):
        """
        Inizializza il dashboard con una connessione.
        """
        self.connection = connection  # Salva l'istanza di Connection
        self.root = tk.Tk()
        self.root.tk.call('tk', 'scaling', 2.0)  # Risoluzione HiDPI
        self._setup_gui()

    def _setup_gui(self):
        """Configura l'interfaccia grafica"""
        self.root.title("Monitor Temperatura")
        self.root.geometry("1200x800")

        # Container principale
        main_container = tk.Frame(self.root)
        main_container.pack(fill=tk.BOTH, expand=True, padx=20, pady=20)

        # Frame per il grafico
        self.graph_frame = tk.Frame(main_container)
        self.graph_frame.pack(fill=tk.BOTH, expand=True)

        # Inizializza il grafico vuoto
        self.figure = Figure(figsize=(10, 6), dpi=100)
        self.ax = self.figure.add_subplot(111)
        self.canvas = FigureCanvasTkAgg(self.figure, master=self.graph_frame)
        self.canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

        # Pulsante di aggiornamento
        btn_refresh = tk.Button(
            main_container,
            text="Aggiorna Dati",
            command=self.update_data,
            font=('Helvetica', 12),
            padx=15,
            pady=10
        )
        btn_refresh.pack(pady=20)

    def update_data(self):
        """Aggiorna il grafico con dati reali"""
        try:
            # Recupera dati dalla connessione
            data = self.connection.get_data()  # Supponiamo che Connection abbia un metodo get_data()

            # Elabora i dati
            dates = [datetime.fromtimestamp(entry['time'] / 1000) for entry in data]  # Converti timestamp in datetime
            temps = [entry['value'] for entry in data]

            # Aggiorna il grafico
            self._update_plot(dates, temps)

        except Exception as e:
            print(f"Errore: {e}")

    def _update_plot(self, dates, temperatures):
        """Aggiorna il grafico con nuovi dati"""
        self.ax.clear()

        # Plot dati
        self.ax.plot(dates, temperatures, marker='o', linestyle='-', color='#2c7bb6')

        # Linee max/min
        max_temp = max(temperatures)
        min_temp = min(temperatures)
        self.ax.axhline(max_temp, color='#d7191c', linestyle='--', label=f'Max: {max_temp}°C')
        self.ax.axhline(min_temp, color='#1a9641', linestyle='--', label=f'Min: {min_temp}°C')

        # Formattazione
        self.ax.set_title("Andamento Temperatura Ultimi 7 Giorni", fontsize=14, pad=20)
        self.ax.set_xlabel("Data", fontsize=12)
        self.ax.set_ylabel("Temperatura (°C)", fontsize=12)
        self.ax.tick_params(axis='x', rotation=45)
        self.ax.grid(True, alpha=0.3)
        self.ax.legend()

        # Ridisegna il canvas
        self.figure.tight_layout()
        self.canvas.draw()