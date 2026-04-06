# Super Sailbot Sailcode
 It's Sailcoded.
![Image](Resources/Sailbot.png "Sailbot")

# About the Project
This project is the software that does the sailcode for the Sailbot sailboat.
- [Discord](https://discord.gg/UttQ8HDzf3)
# Project Setup
## Setup PlatformIO (Necessary, for all IDEs)
1. Install Python
2. Install the [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/methods/installer-script.html)

## Setup the Project In Your IDE
### CLion (Recommended, it's free with your student email)
1. Install the PlatformIO Plugin (Settings -> Plugins -> Search for PlatformIO)
2. Restart CLion
3. Open the Project (This can be done directly from Github, File -> New -> Project from Version Control -> Github)

### Visual Studio Code (Alternative, it's just normal free)
1. Clone the repo from GitHub.
2. Install the recommended extensions.
3. Restart Visual Studio Code.

# Project Structure
The project is structured as follows:
- `src/`: The source code for the project.
- `include/`: The header files for the project.
- `lib/`: The libraries for the project.
- `test/`: The tests for the project.
- `platformio.ini`: The configuration file for the project.

# Wiring the Arduino
As of 4/6/2026,
Pins:
- SparkfunICM20948 Magnetometer: 'Wire'
- GPS: 'Wire1'
- These ones are in the Electronics Manager:
- WinchServo = new Servos::WinchServo: 'pin 9'
- MinLimitSwitchWinch = new InterruptLimitSwitchWithCallbacks: 'pin 2'
- MaxLimitSwitchWinch = new InterruptLimitSwitchWithCallbacks: 'pin 3'
- JibWinchServo = new Servos::ArduinoServo: 'pin 11'
- RudderServo = new Servos::ArduinoServo: 'pin 10'
- WindSensor = new WindSensors::FancyWindSensor: 'Serial3, 115200 baud'
# Compiling and Running the Project
    You should just be able to click the play button in your IDE.

![Image](Resources/SoTrue.jpeg "So True")
idfk figure it out
