package model;

import connections.mqtt.MQTTAgent;
import connections.http.DataService;
import io.vertx.core.Vertx;

public class Logic {
    private final Mode mode = new Mode();
    private final TempManager tManager = new TempManager(200);
    private final Vertx vertx;
    private final MQTTAgent mqttAgent;

    public Logic() {
        vertx = Vertx.vertx();
        mqttAgent = new MQTTAgent(tManager);

        DataService service = new DataService(8080, tManager, mode);
        
        vertx.deployVerticle(service);
        vertx.deployVerticle(mqttAgent);

        vertx.setPeriodic(1000, id -> run());
    }

    public void run() {
        if (mode.getMode() == ModeType.AUTOMATIC) {
            runAuto();
        } else {
            runMan();
        }
    }

    private void runAuto() {
        System.out.println(tManager.getTempState().toString());
        switch (tManager.getTempState()) {
            case NORMAL:
                tManager.setFreq(Constants.F1);
                tManager.setOpening(0);
                break;

            case HOT:
                tManager.setFreq(Constants.F2);
                tManager.setOpening(50); 
                break;

            case TOO_HOT:
                tManager.setFreq(Constants.F2);
                tManager.setOpening(100);
                if (tManager.isOver()) {
                    tManager.startAllarm();
                }
                break;

            case ALLARM:
                break;
        }
        mqttAgent.sendFrequency(tManager.getFreq());
    }

    private void runMan() {
    }
}
