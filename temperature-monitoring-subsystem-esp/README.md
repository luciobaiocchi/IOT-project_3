Per la esp di pippo la configurazione da usare è la seguente:
```
[env:upesy_wroom]
platform = espressif32
board = esp32-s3-devkitm-1
framework = arduino
```

const char* ssid = "lucio";
const char* password = "lupolucio";

const char *serviceURI = "http://172.20.10.13:8080";

Per trovare l'indirizzo IP :
Macos/linux

```bash
ifconfig
```

Windows

```bash
ipconfig
```