package model;

public class Mode {
    private ModeType mainState = ModeType.AUTOMATIC;

    public void MainState(){

    }

    public void changeMode(){
        if (mainState == ModeType.AUTOMATIC) {
            mainState = ModeType.MANUAL;
        } else {
            mainState = ModeType.AUTOMATIC;
        }
    }

    public ModeType getMode(){
        return mainState;
    }
}
