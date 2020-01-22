#include <Arduino.h>

// Include libraries for magnetometer
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303AGR_Mag.h>

// Include libraries for display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define constants
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declare global vars
/** A reference to the Magnetometer (via I2C) */
Adafruit_LSM303AGR_Mag_Unified mag = Adafruit_LSM303AGR_Mag_Unified();

/** Create a reference to the Display (via I2C) */
Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

/**
 * fatal_error - busy halt the microprocessor and report the error over
 * 				the UART/USB serial port
 *
 * @param (const char *) message - the error to report over serial.
 */
void fatal_error(const char *message) {
	while(!Serial) {
		digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(200);                       // wait for a second
		digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
		delay(200); 
	}
	Serial.begin(9600);

	Serial.println(message);
	while(1) {
		digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(1000);                       // wait for a second
		digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
		delay(1000); 
	}
}

/**
 * setup - run once after the Arduino framework initialization but before loop.
 * 		Used to setup software bridges to hardware and display splash screen.
 */
void setup(void) {
	// a dreaded arbitrary delay because the display is not ready at poweron
	// though the constructor will succeed without error
	delay(1000);

	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		fatal_error("SSD1306 initialization failed");
	}

	display.setTextSize(2);      // Larger 2:1 pixel scale
	display.setTextColor(SSD1306_WHITE); // Draw white text
	display.cp437(true);         // Use full 256 char 'Code Page 437' font

	// Do a splash screen
	display.clearDisplay();
	display.setCursor(20, 9); // Center Splash text
	display.print("BUCKNELL");
	display.display();

	delay(500);

	display.setTextSize(1);      // Normal 1:1 pixel scale 

	/* Initialise the magnetometer */
	if(!mag.begin()) {
		fatal_error("No LSM303 detected... Check your wiring!");
	}
}

/**
 * loop - called by Arduino framework in an infinite loop. Used to read
 * 		magnetometer and draw display
 */
void loop(void) {
	/* Get a new sensor event */
	sensors_event_t magEvent;
	mag.getEvent(&magEvent);

	// Draw the display
	display.clearDisplay();

	// Admittedly slow but less sensitive to small evenly distributed
	// fluctuations
	double magnitude = pow(magEvent.magnetic.x, 2) + pow(magEvent.magnetic.y, 2) + pow(magEvent.magnetic.z, 2);
	// WARNING!!! Arbitrary magic constant in code
	if(magnitude > 10000.0) {
		display.setCursor(12, 0);
		display.setTextSize(2);
		display.print("Magnetic!");
		display.setTextSize(1);
	}

	display.setCursor(0, 25);
	display.print(" ");
	display.print(magEvent.magnetic.x);
	display.print(" ");
	display.print(magEvent.magnetic.y);
	display.print(" ");
	display.println(magEvent.magnetic.z);
	display.display();	// flush to display

	delay(500);
}