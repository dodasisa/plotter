# Robot plotter
## The robot that draws portraits
Looks at you, meditates a bit, and start drawing

The full process of drawing a portrait is 
1. Raises the head
2. Takes a photo
3. Converts the photo in a set of lines, curves and spilines
4. Splits the stroke of each line in a servo moves (Shoulder, Elbow and Hand pressure)
5. Start moving the servos
6. Compare the result with the original photo and, eventually, go back to step 3

## Physical components and interfaces
- The brain and main component is ***Raspberry Pi 3 Model B Rev 1.2*** 
- The eyes use the Raspberry PI Camera v2.1 connected to the CSI interface
- The leds, command buttons and the neck servo are connected to the raspberry pins
- All the other servos are connected to other microcontrollers, using by I2C interface
- Two leds
- Two resistors
- The servos
- Two buttons
- Three microcontrollers
- Two separate power sources (The first for the microcontrollers, the second for the servos)

## Libraries and tools
- The raspberry OS is ***Raspbian GNU/Linux 11 (bullseye)***
- Camera controled through the library ***Raspicam version 0.1.3***
- Documentation produced by ***Doxygen version 1.9.5***
- Unit tests ran by ***CxxTest version 4.4***
- Raspberry pins and interfaces reached through ***pigpio version 1***
- Logs written by ***log4cxx version 11***
- The programmation language is C++
- C++ compiler version ***10.2.1***
