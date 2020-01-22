# Arduino Magnetomer
Software to power a small, inexpensive Magnetometer sensitive to mT

## About
Bucknell University has a Scanning Electron Microscope (SEM) in which we wish to examine specimens of unknown compostion and origin but magnetic samples could damage the SEM thus we wish to use a rather sensitive magnetomer to screen specimens. We found off the shelf magnetomers to not be sufficently sensitive however acceptable sensor modules are available for use with Arduino hardware. Therefore a common microcontroller, sensor and display were selected, assembled, and programmed with the software in this repository.

## Dependencies

- Adafruit Unified Sensor@^1.0.3
- Adafruit BusIO@^1.0.10
- Adafruit LSM303AGR Mag@^1.1.2
- Adafruit SSD1306@^2.0.2
- Adafruit GFX Library@^1.7.0

See also platformio.ini

## Building / Installation
This project is setup to be built with Platformio. Provided the Platformio CLI is installed, after cloning the project locally one can change into the project directory issue the `pio run` command to cache the required libraries in the project directory and compile the code. There may be warnings about using a float in a double context, this is expected. To then program the microcontroller, it should be connected to the PC and the command `pio run -t upload` issued. Or using a PlatformIO extension to a GUI program editor, simply click the "Build" and "Upload" buttons.

```sh
git clone git@gitlab.bucknell.edu:research-support/magnetometer.git Magnetomer
cd Magnetomer
pio run
pio run -t upload
```

## Usage
Apply power to the microcontroller and bring the sample near the connected sensor.

## License
This project is licensed under the Apache 2.0 License - see the LICENSE file for details

## Author
2019 - present Tom Egan <tegan@bucknell.edu>