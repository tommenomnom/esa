# ESA (Emergency Service Assistant) user study setup
Repository with necessary files to replicate the user study that has been done on ESA. This involved researching a system to inform drivers of a level 3 automated vehicle of an incoming emergency vehicle like an ambulance, firetruck or police car.


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

The Arduino is then connected via USB to the windows computer.


