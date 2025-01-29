package connections.serial;

import connections.serial.CommChannel;
import connections.serial.SerialCommChannel;
import model.Mode;
import model.ModeType;
import model.TempManager;

public class SerialLoop extends Thread{
    private CommChannel channel;
    private TempManager tManager;
    private Mode mode;

    public SerialLoop(final TempManager tManager, final Mode mode){
        this.tManager = tManager;
        this.mode = mode;
    }

    public void run() {
        try {
            this.channel = new SerialCommChannel("/dev/cu.usbmodem101", 9600);
            log("Channel created");
            log("Waiting Arduino for rebooting...");
            Thread.sleep(4000);
            log("Ready.");

            log("Done. Let's start.");

        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        while(true) {
            try {
                receive();
            } catch (Exception ignored) {

            }

        }
    }

    /*
     formato messaggio ricevuto [MAAA]
     M = modalità
     A = apertura
     */
    void receive(){
        try {
            // Riceve il messaggio dal canale
            String msg = channel.receiveMsg();
            log("Received: " + msg);

            // Controlla se il primo carattere è 'M' o 'A'
            if (msg != null && !msg.isEmpty()) { // Verifica che il messaggio non sia nullo o vuoto
                char firstChar = msg.charAt(0);
                if (firstChar == 'M' && mode.getMode() == ModeType.AUTOMATIC) {

                }else if (firstChar == 'A' && mode.getMode() == ModeType.MANUAL) {

                }else {
                    log("Invalid message start: " + firstChar);
                }
            } else {
                log("Received an empty or null message");
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    /*
     formato messaggio [MAAATT]
     M = modalità
     A = apertura
     T = temperatura
     */
    void send() throws InterruptedException {
        StringBuilder msg = new StringBuilder();

        // Determina il prefisso in base alla modalità
        msg.append(mode.getMode() == ModeType.AUTOMATIC ? "A" : "M");

        // Formatta l'apertura con zero padding
        int opening = tManager.getOpening();
        if (opening < 10) {
            msg.append("00").append((char) opening);
        } else if (opening < 100) {
            msg.append("0").append((char) opening);
        } else {
            msg.append((char) opening);
        }

        // Aggiunge l'ultimo valore
        msg.append((char) tManager.getLast());

        // Invia il messaggio
        channel.sendMsg(msg.toString());
        log("send -> " + msg.toString());
    }

    private void log (String msg){
        System.out.println("[SERIAL LOOP] " + msg);
    }


}