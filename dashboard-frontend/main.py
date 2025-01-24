# main.py
import asyncio
from model.connection import Connection  # Importa la classe Connection
from view.View import TemperatureDashboard  # Importa la classe TemperatureDashboard


class Main:
    @staticmethod
    async def run_connection(connection):
        """
        Esegue le operazioni di connessione con gestione degli errori.
        """
        try:
            return await connection.run()
        except Exception as e:
            print(f"Errore: {e}")
            return []

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

        # Esegui le operazioni asincrone e ottieni i dati
        data = asyncio.run(Main.run_connection(connection))

        # Avvia il dashboard con i dati recuperati
        dashboard = TemperatureDashboard(connection)
        dashboard.root.mainloop()


if __name__ == "__main__":
    # Avvia il programma
    Main.main()