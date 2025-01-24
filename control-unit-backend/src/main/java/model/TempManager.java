package model;


import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import model.TempState;

public class TempManager {
    private final List<Integer> tempList = new ArrayList<>();
    private TempState tState = TempState.NORMAL;
    private int maxVal;
    long startTime;

    public TempManager(final int max){
        this.maxVal = max;
    }

    public List<Integer> getHistory(){
        return this.getHistory();
    }

    public int getMax(){
        return Collections.max(tempList);
    }

    public int getMin(){
        return Collections.max(tempList);
    }

    public int getLast(){
        return tempList.get(tempList.size());
    }
    
    public TempState getTempState(){
        return this.tState;
    }

    /**
     * Update the list every time, also update the current temp state
     * @param temp
     */
    public void addTemp(final int temp){
        if (tempList.size() == maxVal){
            tempList.remove(0);
            tempList.add(temp);
        }else{
            tempList.add(temp);
        }
        updateState();
    }

    public void startTimer(){
        this.startTime = System.currentTimeMillis();
    }

    public boolean checkTimer(){
        return startTime + Constants.DT_millis <= System.currentTimeMillis();
    }

    private void updateState(){
        if (getLast() > Constants.max_normal){
            this.tState = TempState.HOT;
        }
        if (getLast() > Constants.max_hot){
            this.tState = TempState.TOO_HOT;
        }
    }
}
