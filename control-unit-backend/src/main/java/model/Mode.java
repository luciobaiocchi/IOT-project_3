package model;

public class Mode {
    private MainStateType mainState = MainStateType.AUTOMATIC;

    public void MainState(){

    }

    public void changeMode(){
        if (mainState == MainStateType.AUTOMATIC) {
            mainState = MainStateType.MANUAL;
        } else {
            mainState = MainStateType.AUTOMATIC;
        }
    }

    public MainStateType getMode(){
        return mainState;
    }
}
