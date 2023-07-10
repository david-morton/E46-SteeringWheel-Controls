#include <Arduino.h>

// Define pins which will read voltages from the board
const byte pinReadMisc = A0;
const byte pinReadAudio = A1;

// Define variables to store values
int inputValueAudio; 
int inputValueMisc;

float voltageAudio;
float voltageMisc;

/* 
################## SETUP STARTS HERE ##################
*/
void setup() {
  SERIAL_PORT_MONITOR.begin(115200);
  while (!Serial) {};

  // Initialise my input pins, not necessary as they are inputs but done for clarity
  pinMode(pinReadAudio, INPUT);
  pinMode(pinReadMisc, INPUT);
}

/* 
################## MAIN LOOP STARTS HERE ##################
*/
void loop() {
  // Get latest values from input pins
  inputValueAudio = analogRead(pinReadAudio);
  inputValueMisc = analogRead(pinReadMisc);
  // Some debug output is ok for now
  SERIAL_PORT_MONITOR.print("\nAudio pin is reading: ");
  SERIAL_PORT_MONITOR.println(inputValueAudio);
  SERIAL_PORT_MONITOR.print("Misc pin is reading: ");
  SERIAL_PORT_MONITOR.println(inputValueMisc);
  delay(1000);
}
