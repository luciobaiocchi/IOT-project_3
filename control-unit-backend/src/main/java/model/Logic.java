package model;

import model.TempManager;
import connections.http.DataService;
import io.vertx.core.Vertx;
import model.MainStateType;
import model.TempState;

public class Logic {
    /*Contiene stato automatico o manuale */
    private Mode mode = new Mode();
    private TempManager tManager = new TempManager(200);

    public Logic(){
        Vertx vertx = Vertx.vertx();
        DataService service = new DataService(8080, tManager, mode);
        vertx.deployVerticle(service);
        
    }

    public void run(){

        while (true) {
            switch (mode.getMode()) {
                case AUTOMATIC:
                    runAuto();
                    break;
                case MANUAL:
                    runMan();
                    break;
                default:
                    break;
            }
        }
    }

    private void runAuto(){
        switch (tManager.getTempState()) {
            /*entry/f=f1
            entry/winClosed()
            do/readFreq()*/
            case NORMAL:

                break;
            /*entry/f=f2
            do/winOpenProp()
            do/readFreq()*/
            case HOT:
                
            break;
            /*entry/f=
            do/winOpenProp()
            do/readFreq()*/

            case TOO_HOT:
                
            break;
        
            default:
                break;
        }
    }

    private void runMan(){
        /*Send 'm' */
    }
}
