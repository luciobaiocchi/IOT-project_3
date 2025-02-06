package model;

public class Mode {
    private ModeType mainState = ModeType.AUTOMATIC;
    private boolean isChanged = false;

    public void Mode(){
    }

    public void changeMode(){
        if (isChanged == false){
            isChanged = true;
        }
        System.out.println("IS CHANGED       " + isChanged);
        
        if (mainState == ModeType.AUTOMATIC) {
            mainState = ModeType.MANUAL;
        } else {
            mainState = ModeType.AUTOMATIC;
        }
    }

    public ModeType getMode(){
        return mainState;
    }

    
    public boolean isChanged(){
        return isChanged;
    }
    
    public void setChangeFalse(){
        isChanged = false;
    }

}
