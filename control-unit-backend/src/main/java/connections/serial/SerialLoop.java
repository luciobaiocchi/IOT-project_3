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
            this.channel = new SerialCommChannel("COM3", 9600);
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
                    mode.changeMode();
                }else if (firstChar == 'A' && mode.getMode() == ModeType.MANUAL) {
                    log("ENTRATO");
                    mode.changeMode();
                }
                if (mode.getMode() == ModeType.MANUAL){
                    tManager.setOpening(Integer.parseInt(msg.substring(1)));
                }
            } else {
                log("Received an empty or null message");
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            send();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
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

        if (mode.getMode() == ModeType.AUTOMATIC){
            msg.append("A");
            // Formatta l'apertura con zero padding
            int opening = tManager.getOpening();
            opening = 1;
            if (opening < 100 && opening > 9) {
                msg.append("0").append(opening);
            } else if (opening < 10) {
                msg.append("00").append(opening);
            } else {
                msg.append(opening);
            }
        }else if (mode.getMode() == ModeType.MANUAL){
            msg.append("M");
            if (tManager.getLast() < 0){
                msg.append("-");
                msg.append(Math.abs(tManager.getLast()));
            }else if (tManager.getLast() > 0){
                msg.append("+");
                msg.append(Math.abs(tManager.getLast()));
            }

        }
        // Aggiunge l'ultimo valore
        


        // Invia il messaggio
        channel.sendMsg(msg.toString());
        log("send -> " + msg.toString());
    }

    private void log (String msg){
        System.out.println("[SERIAL LOOP] " + msg);
    }


}