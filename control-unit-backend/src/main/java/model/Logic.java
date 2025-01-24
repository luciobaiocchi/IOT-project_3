package model;

import model.TempManager;
import model.MainState;
import model.TempState;

public class Logic {
    private final TempManager tManager;
    /*Contiene stato automatico o manuale */
    private MainState mState = MainState.AUTOMATIC;
    private TempState tState = TempState.NORMAL;
    private int doorPos = 0;

    public Logic(final TempManager tManager){
        this.tManager = tManager;
    }

    public void run(){
        while (true) {
            switch (mState) {
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
        tState = tManager.getTempState();
        switch (tState) {
            case NORMAL:
            
                break;
            case HOT:
                
            break;
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
