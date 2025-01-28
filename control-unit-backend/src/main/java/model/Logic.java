package model;

import model.TempManager;
import connections.http.DataService;
import io.vertx.core.Vertx;
import model.ModeType;
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
            if (mode.getMode() == ModeType.AUTOMATIC){
                runAuto();
            }else{
                runMan();
            }
        }
    }

    private void runAuto(){
        //System.out.println(tManager.getTempState());
        switch (tManager.getTempState()) {
            /*entry/f=f1
            entry/winClosed()
            do/readFreq()*/
            case NORMAL:
                tManager.setFreq(Constants.F1);
                tManager.setOpening(0);
            break;
            /*entry/f=f2
            do/winOpenProp()
            do/readFreq()*/
            case HOT:
                tManager.setFreq(Constants.F2);
            break;
            
            /*entry/f=
            do/winOpenProp()
            do/readFreq()*/
            case TOO_HOT:
                if(tManager.isOver()){
                    tManager.startAllarm();
                }
            break;

            case ALLARM:
            break;
        
            default:
                break;
        }
    }

    private void runMan(){
        /*Send 'm' */
    }
}
