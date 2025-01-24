from model.Connection import Connection  # Importa la classe Connection
import asyncio  # Aggiungi questa linea


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

        # Esegui le operazioni asincrone
        asyncio.run(connection.run())


if __name__ == "__main__":
    # Avvia il programma
    Main.main()
