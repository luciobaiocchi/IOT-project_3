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
            this.channel = new SerialCommChannel("/dev/cu.usbmodem2101", 9600);
            log("Channel created");
            log("Waiting Arduino for rebooting...");
            Thread.sleep(4000);
            log("Ready.");
            log("Done. Let's start.");

        } catch (Exception e) {
            log("errore connessione");
            throw new RuntimeException(e);
        }

        while(true) {
            try {
                receive();
            } catch (Exception ignored){

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
                //msg.length() > 1 per controllare che ci siano dei valori
                if (firstChar == 'N' && mode.getMode() == ModeType.MANUAL && msg.length() > 1){
                    log("opening ------------- " + Integer.parseInt(msg.substring(1)));
                    tManager.setOpening(Integer.parseInt(msg.substring(1)));
                    try {
                    }catch(NumberFormatException e){
                        e.printStackTrace();
                    }
                }else if(isNewMode(firstChar)){
                    mode.changeMode();
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
            e.printStackTrace();
        }
    }

    /*
     formato messaggio [MAAA]
     M = modalità ----> A M N
     A = apertura
     T = temperatura

     A000
     M000
     N000

     */
    void send() throws InterruptedException {
        log("SEND");
        StringBuilder msg = new StringBuilder();

        if (mode.isChanged()){
            mode.setChangeFalse();
            if (mode.getMode() == ModeType.AUTOMATIC){
                msg.append("A");
            }else if (mode.getMode() == ModeType.MANUAL){
                msg.append("M");
        }}else {
            msg.append("N");
        }

        if (mode.getMode() == ModeType.AUTOMATIC){
            int opening = tManager.getOpening();
            if (opening < 100 && opening > 9) {
                msg.append("0").append(opening);
            } else if (opening < 10) {
                msg.append("00").append(opening);
            } else {
                msg.append(opening);
            }
        }else if (mode.getMode() == ModeType.MANUAL){
            if (tManager.getLast() < 0){
                msg.append("-");
                msg.append(Math.abs(tManager.getLast()));
            }else if (tManager.getLast() > 0){
                msg.append("+");
                msg.append(Math.abs(tManager.getLast()));
            }
        }

        /* 
        if (mode.getMode() == ModeType.AUTOMATIC){
            msg.append("A");
            int opening = tManager.getOpening();
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
        }*/

        // Invia il messaggio
        channel.sendMsg(msg.toString());
        log("           send -> " + msg.toString());
    }

    private void log (final String msg){
        //System.out.println("[SERIAL LOOP] " + msg);
    }

    private boolean isNewMode(final char firstChar){
        return (firstChar == 'M' && mode.getMode() == ModeType.AUTOMATIC 
        || firstChar == 'A' && mode.getMode() == ModeType.MANUAL);
    }
}