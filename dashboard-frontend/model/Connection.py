import asyncio
import random
from aiohttp import ClientSession


class Connection:
    def __init__(self, host: str, port: int):
        """
        Inizializza la connessione con l'host e la porta specificati.
        """
        self.host = host
        self.port = port

    async def post_data(self, session: ClientSession):
        """
        Invia dati al server tramite una richiesta POST.
        """
        item = {
            "value": 20 + random.random() * 5,
            "place": "nowhere"
        }
        url = f"http://{self.host}:{self.port}/api/data"
        print("Posting new data item...")
        async with session.post(url, json=item) as response:
            print(f"Posting - Received response with status code: {response.status}")

    async def get_data(self, session: ClientSession):
        """
        Recupera dati dal server tramite una richiesta GET.
        """
        url = f"http://{self.host}:{self.port}/api/data"
        print("Getting data items...")
        async with session.get(url) as response:
            print(response)
            print(f"Getting - Received response with status code: {response.status}")
            return await response.json()

    async def post_mode(self, session: ClientSession, mode: str):
        """
        Invia una nuova modalità al server.
        """
        url = f"http://{self.host}:{self.port}/api/data"
        print(f"Posting new mode: {mode}...")
        async with session.post(url, json={"new_mode": mode}) as response:
            print(f"Posting mode - Received response with status code: {response.status}")
            return await response.json()

    async def run(self):
        """
        Esegue le operazioni di invio e recupero dati.
        """
        async with ClientSession() as session:
            await self.post_data(session)
            await asyncio.sleep(1)  # Attendi 1 secondo
            return await self.get_data(session)