package model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class TempManager {
    private final List<Integer> tempList = new ArrayList<>();
    private TempState tState = TempState.NORMAL;
    private int maxVal;
    private int freq = Constants.F1;
    long startTime;
    /* from 0 to 100 */
    int openLevel = 0;

    public TempManager(final int max) {
        this.maxVal = max;
        tempList.add(2);
        tempList.add(14);
        tempList.add(25);
    }

    public List<Integer> getHistory() {
        return Collections.unmodifiableList(tempList); // Restituisce una lista non modificabile
    }

    public int getMax() {
        return Collections.max(tempList);
    }

    public int getMin() {
        return Collections.min(tempList); // Correzione: usa min() invece di max()
    }

    public int getLast() {
        //Random random = new Random();

        // Generate a random integer between 0 and 99
        //int randomNumber = random.nextInt(40);
        int randomNumber = 50;
        return randomNumber;
        //return tempList.get(tempList.size() - 1); // Correzione: usa size() - 1
    }

    public TempState getTempState() {
        if (this.tState != TempState.ALLARM){
            this.updateState();
        }
        return this.tState;
    }

    /**
     * Aggiorna la lista e lo stato della temperatura.
     *
     * @param temp La temperatura da aggiungere.
     */
    public void addTemp(final int temp) {
        if (tempList.size() == maxVal) {
            tempList.remove(0);
        }
        tempList.add(temp);
    }

    public void setOpening(final int opening){
        this.openLevel = opening;
    }

    public int getOpening(){
        return openLevel;
    }

    public void startTimer() {
        this.startTime = System.currentTimeMillis();
    }

    public boolean isOver() {
        return startTime + Constants.DT_millis <= System.currentTimeMillis();
    }

    public void setFreq(final int freq){
        this.freq = freq;
    }

    public int getFreq(){
        return this.freq;
    }

    public void startAllarm(){
        tState = TempState.ALLARM;
    }

    private void updateState() {
        int lastTemp = getLast();
        if (lastTemp > Constants.max_too_hot && tState != TempState.TOO_HOT) {
            this.startTimer();
            this.tState = TempState.TOO_HOT;
            System.out.println("ok");
        } else if (lastTemp > Constants.max_too_hot) {
            this.tState = TempState.TOO_HOT;
        } else if (lastTemp > Constants.max_hot) {
            this.tState = TempState.HOT;
        } else {
            this.tState = TempState.NORMAL;
        }
    }
}