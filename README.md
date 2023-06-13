# ESA (Emergency Service Assistant) user study setup
Repository with necessary files to replicate the user study that has been done on ESA. This involved researching a system to inform drivers of a level 3 automated vehicle of an incoming emergency vehicle like an ambulance, firetruck or police car.

The test exists of the following three scenarios: 

**Scenario 1:** Car is driving on a two-lane road with a car in front of him and an ambulance coming in form the back. The ambulance passes the car on the left.  

**Scenario 2:** Car is driving on a two-lane road with a car in front of him that he passes after a while. The ambulance is coming from the back and passes him on the left.  

**Scenario 3:** Car is driving on a one-lane road with the ambulance coming in from behind. The car then has to move to the right onto the grass to let the ambulance pass by on the left.  

## File structure


    .
    └── esa/  
    ├── arduino-scripts/  
    │   ├── Scenario_1/  
    │   │   └── Scenario_1.ino (Arduino code for scenario 1)  
    │   ├── Scenario_2/  
    │   │   └── Scenario_2.ino (Arduino code for scenario 2)  
    │   └── Scenario_3/  
    │       └── Scenario_3.ino (Arduino code for scenario 3)  
    ├── hud-videos/  
    │   ├── scenario_1_hud.mp4 (HUD video for scenario 1)  
    │   ├── scenario_2_hud.mp4 (HUD video for scenario 2)  
    │   └── scenario_3_hud.mp4 (HUD video for scenario 3)  
    ├── inc (Readme content)/  
    │   ├── LED_circuit.png (Readme image)  
    │   ├── Vibration_circuit.png (Readme image)  
    │   └── physical_setup.png (Readme image)  
    ├── python-scripts/  
    │   ├── scenario_1.ipynb (Jupyter Notebook thar runs scenario 1)  
    │   ├── scenario_2.ipynb (Jupyter Notebook thar runs scenario 2)  
    │   └── scenario_3.ipynb (Jupyter Notebook thar runs scenario 3)  
    ├── scenario-videos/  
    │   ├── scenario_1_road.mp4 (Scenario video for on-screen of scenario 1)  
    │   ├── scenario_2_road.mp4 (Scenario video for on-screen of scenario 2)  
    │   └── scenario_3_road.mp4 (Scenario video for on-screen of scenario 3)  
    └── README.md



## Equipment
The setup of this user study requires the following hardsware:
- A windows computer
- A reasonably big, external screen
- Chair for user seating
- An Arduino Uno
- A Breadboard
- Closed back headphones with goed stereo imaging. We used the Beyerdynamic DT770 Pro.
- Makeshift HUD. We used [this](https://www.youtube.com/watch?v=m9AUhavpY7o&ab_channel=ProjectDiY) tutorial for inspiration but created it into a stand.
- Makeshift steering wheel
- Makeshift dashboard to attach the LED's on
- A phone that has the [SuRT](https://www.researchgate.net/figure/Surrogate-reference-task-SuRT-example-screen_fig5_256446631) app installed to distract the participant
- 2x phone that can be linked to mirror screens. We used [Airdroid](https://play.google.com/store/apps/details?id=com.sand.aircast&hl=en_US&pli=1) for this.

LED setup:
- 2x 1.5m 2812b LED strip 
- 1x 100ohm resistor 
- 1x 100uF capacitor

Vibrating belt setup:
- 5x Small Vibration DC Motor 2.5-4V
- 5x 100ohm resistor 
- 1x Diode High-Speed 1N4148 
- 1x Transistor 2N3906 
- 1x Belt 
- 1x Sleeve around Belt   

## Prequisites
The following programs should be installed on your computer:
- [Arduino IDE](https://www.arduino.cc/en/software) (Tested on 2.1.0)
- Arduino FastLED library. This can be added in Arduino IDE via `Sketch -> Include library`.
- [Python](https://www.python.org/downloads/) (Tested on 3.10)
- [VLC Media Player](https://www.videolan.org/vlc/) (**VERY IMPORTANT!** Make sure to install the 64-bit version of this program)


## Environment
To setup the environment, the following Python packages should be installed via the console:
- `pip install pyserial` will install the package to be able to communicate with the Arduino.
- `pip install python-vlc` will install the package to control the VLC media player.
- `pip install notebook` will install Jupyter Notebook. This might not be necessary for advanced users but it is easier to adjust and test code with.


## Physical setup

The physical setup was built in a closed room with no public access. Curtains were closed to make sure the visibility of the screen and the HUD were optimal. As you can see, the LED's are attached to a dashboard that was created for this setup. In front of that is a steering wheel that the user can turn both left and right. Behind the setup, the researcher is seated to control the simulation setup.

![Physical_setup](https://github.com/tommenomnom/esa/blob/main/inc/physical_setup.jpg?raw=true)

To begin with, the Arduino and LED strip are connected in the following way:  

![LED circuit](https://github.com/tommenomnom/esa/blob/main/inc/LED_circuit.png?raw=true)


The vibrating modules inside of the belt sleeve are connected to the Arduino in this way:  

![VIB circuit](https://github.com/tommenomnom/esa/blob/main/inc/Vibration_circuit.png?raw=true)  

The following steps then need to be completed:
- Connect Arduino via USB to the windows computer.  
- Connect The big screen that is used to display the road scenario is via HDMI to the computer and set the display mode to duplicate screen.
- Connect a pair of headphones to the computer and set the sound output accordingly.

## Running the test

A participant may now be seated in the setup. Hand them the phone with the SuRT app and let them start playing the game. The headphones should be put on to make sure they hear the audio. You can then move on to running the scenario.

1. Open a console from the folder you pulled this repository to. run the following command: `jupyter notebook`
This will open a browser screen with Jupyter Notebook. In this window, navigate to the `python-scripts` folder and open the script of the scenario you want to test. Note that you will have to change the COM serial port in the python code to the one your Arduino is connected to. You can check this in the left top dropdown in the Arduino IDE.

2. Navigate to the `arduino-scripts` folder of the repository and open the arduino script of the scenario you want to test with Arduino IDE.
You should now have one window with the Python code and one window with the Arduino code.  

3. Make sure one of the mirrored phones is in the HUD display and the other one is ready with the HUD video of the scenario you want to test located in the `hud-videos` folder . The 'play' button on the phone should be pressed as soon as you start the test.

4. To start running the scenario, select the window of the Arduino script. Press the upload button to upload this code to the Arduino.
The right code is now on the Arduino and the simulation is ready to go.  

5. Navigate to the python notebook window and press the 'Restart kernel and run all code' button (fast-forward icon in toolbar).
The video will now launch and the cue will be sent to the Arduino to start running the code. Once the video launches, the play button on the HUD phone should be clicked to make sure this starts as simultaneously as possible. 

The scenario will now run!


