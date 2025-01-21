# Guida per configurare e utilizzare il progetto

Questo progetto richiede l'uso di un ambiente virtuale Python per gestire le dipendenze. Segui questa guida per configurare il tuo ambiente di sviluppo.

---

## 1. Creare un ambiente virtuale

Un ambiente virtuale ti permette di isolare le dipendenze del progetto senza interferire con le installazioni globali di Python.

### Passi:
1. Apri un terminale nella cartella del progetto.
2. Crea un ambiente virtuale chiamato `myenv` (puoi scegliere un nome diverso):

```bash
python -m venv myenv
```
3. Su alcuni sistemi, potrebbe essere necessario usare python3 invece di python:

```bash
python3 -m venv myenv
```

4. Dopo aver creato l'ambiente virtuale, devi attivarlo per iniziare a usarlo. WINDOWS

```bash
myenv\Scripts\activate
```
LINUX/MACOS
```bash
source myenv/bin/activate
```
Install requirements
```bash
pip install -r requirements.txt
```
Close virtual environment
```bash
deactivate
```