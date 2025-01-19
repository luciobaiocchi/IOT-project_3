**Embedded Systems and IoT  \- a.y. 2024-2025**

**Assignment \#03 \- *Smart Temperature Monitoring*** 

**v1.0.0-20241211**

We want to realise an IoT system monitoring the temperature of a closed environment, equipped with a window. The system is composed of 4 subsystems: 

![][image1]

- **Temperature Monitoring subsystem (based on ESP)**   
  - embedded system to monitor the temperature of the closed environment  
  - It interacts with the Control Room subsystem (via MQTT)  
- **Control Unit subsystem  (backend \- running on a PC)**   
  - main subsystem, governing and coordinating  the whole system  
  - it interacts via MQTT with the Temperature Monitoring  
  - it interacts through the serial line with the Window Controller   
  - it interacts via HTTP with the Dashboard   
- **Window Controller subsystem (Arduino)**   
  - embedded system controlling the window (opening) and providing a panel for operators interaction in place  
  - it interacts via serial line with the Control Unit backend   
- **Dashboard subsystem (Frontend/web app on the PC)**   
  - front-end for operators to remotely visualise data and interact with the system  
  - it interacts via HTTP with the Control Unit backend

*Hardware components* 

- Temperature Monitoring subsystem  
  - SoC ESP32 board (or ESP8266) including  
    - 1 temperature sensor  
    - 1 green led   
    - 1 red led  
- Window Controller subsystem  
  - Microcontroller Arduino UNO board including:  
    - 1 servo motor  
    - 1 potentiometer  
    - 1 tactile button  
    - 1 LCD display

    

*General Behaviour of the system*

The system is meant to monitor the temperature of the closed environment and \- depending on the value \- control the opening of the window.  It can be in two different modes: AUTOMATIC or MANUAL. In AUTOMATIC mode, the system automatically decides how much the window must be opened, depending on the current temperature. In MANUAL mode, the opening is controlled manually by an operator. The starting mode when booting is AUTOMATIC.

Details:

* About the Temperature Monitoring subsystem  
  * The Temperature Monitoring subsystem is responsible for continuously monitoring the level of the temperature, by means of the temperature sensor.  
    * The temperature value is sampled and sent to the Control Unit subsystem with some  frequency F   
    * This frequency actually depends on the state of the system and is established by the Control Unit subsystem (see later).  
  * When the system is working correctly (network ok, sending data ok)  the green led is on and the red is off; otherwise – in the case of network problems – the red led should be on and the green led off.  
* About the Window Controller subsystem  
  * The Window Controller subsystem is responsible for controlling the motor opening the window – from 0% \= window closed (motor position 0 degree), up to 100% \= full open (motor position 90° degree)  
  * The window opening level depends on the state of the system, established by the Control Unit subsystem (see later)   
  * The Window Controller provides also a button to enable the MANUAL mode, in particular:  
    * When the button is pressed, the controller enters in MANUAL mode, so that the window opening level can be manually controlled by operators using a potentiometer.   
    * To exit from the MANUAL model, the button should be pressed again.    
  * The Window Controller subsystem is equipped also with an LCD display reporting:  
    * the current opening level of the window  
    * current mode (AUTOMATIC or MANUAL)  
    * the current temperature value,  when the modality is MANUAL  
* About the Control Unit subsystem  
  * This subsystem is in charge to keep track of:  
    * the last N temperature measurements  
    * the average / min / max temperature values per period (e.g. daily)  
  * It is also in charge of deciding the opening of the window when the system is in AUTOMATIC mode, depending on the value of the current temperature T. In particular:  
    * When T \< T1, then the system is considered in a "NORMAL state". In this state:  
      * the frequency to be used for monitoring the temperature is  F1  
      * the window should be closed  
    * When T1 \<= T \<= T2, the system is in an "HOT state". In this state:  
      * the frequency to be used for monitoring the temperature must be   F2 \> F1  
      * the window should be opened, of a percentage P proportional to the range \[T1,T2\], so that: when  T \= T1, then P 0.01; when T \= T2, then P \= 1.00;    
    * When T \> T2,  the system is in a "TOO\_HOT state". In this state:  
      * the window should be fully open;  
      * if this condition lasts for at least DT time, then the system goes into an "ALARM state"  
    * In the ALARM state, the system waits for the operator's intervention through the Dashboard.  
* About the Dashboard subsystem  
  * The dashboard has two main functionalities:  
    * To visualise the state of the Temperature Monitoring system. In particular:  
      * A graph of the temperature considering the last N measurements  
      * Current average/max/min value  
      * The state of the system:  NORMAL, HOT, TOO-HOT, ALARM   
      * The window opening level (percentage)  
    * To enter in MANUAL mode and control the opening of the window, through some specific GUI controller  
    * To manage the ALARM state (pressing a button to notify that the problem has been solved, bringing back the system into a NORMAL state) 

*The assignment*

Design and develop a prototype of the Temperature Monitoring system, considering as further  requirements:

- **Temperature  Monitoring subsystem**   
  - Run on ESP32 or ESP8266 (or an equivalent SoC board  
  - The control logic must be designed and implemented using finite state machines (synchronous or asynchronous) and (possibly, if useful) task-based architectures  
  - Must use MQTT to communicate with the Control Unit subsystem  
- **Window Controller subsystem**  
  - Run on Arduino (or an equivalent MCU board)  
  - The control logic must be designed and implemented using finite state machines (synchronous or asynchronous) and  (possibly, if useful) task-based architectures  
  - Communicate with the Control Unit subsystem via serial line  
- **Control Unit subsystem**   
  - Runs on a PC  
    - No specific constraints about the programming/sw technology to be used  
  - Uses:  
    - MQTT to communicate with the Temperature Monitoring subsystem,   
    - HTTP to communicate  with the dashboard, and   
    - via serial line with the Window Controller  
- **Dashboard subsystem**  
  - Run on a PC  
    - No specific constraints about the programming/sw technology to be used  
  - Use HTTP to interact with the Control Unit backend

**The Deliverable**

The deliverable consists in a zipped folder **assignment-03.zip** including:

*  4 subfolders (one for each subsystem)   
- temperature-monitoring-subsystem   
- control-unit-backend  
- window-controller  
- dashboard-frontend  
    
* **doc** folder  
  * including a brief report **(report.pdf)** describing the system, including also a description of FSMs, a representation of the schema/breadboard and the link to a short video demonstrating the system.

[image1]: <data:image/png;base64,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>