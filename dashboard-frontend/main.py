import asyncio
from threading import Thread
from view.View import TemperatureDashboard  # Importa la classe TemperatureDashboard
from model.Connection import Connection # Importa la classe Connection


class Main:
    @staticmethod
    def main():
        """
        Punto di ingresso del programma.
        """
        # Configurazione dell'host e della porta
        host = "localhost"  # "b1164b27.ngrok.io"
        port = 8080

        # Crea un'istanza della classe Connection
        connection = Connection(host, port)

        # Crea un event loop dedicato per operazioni asincrone
        loop = asyncio.new_event_loop()
        t = Thread(target=loop.run_forever, daemon=True)
        t.start()

        # Avvia il dashboard con i dati recuperati
        dashboard = TemperatureDashboard(connection, loop)
        dashboard.root.mainloop()


if __name__ == "__main__":
    # Avvia il programma
    Main.main()