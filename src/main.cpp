/*
The steering wheel headers are as below for the left / radio side:
Pin 1 = Ground
Pin 2 = R/T and phone button
Pin 3 = Audio buttons (track and volume)
Pin 4 = 12V for back light LED's

The below are the voltage readings on the Arduino when feeding
pins 2 and 3 from the Arduino's 5V line via a 1.5kohm resistor.
The measurements are taken after the resistor and before the header.

State       Audio   Misc   PCB Switch Number
--------------------------------------------
Resting   | 880  |  865 |
Vol +     | 679  |      |  S2
Vol -     | 148  |      |  S3
Track +   | 315  |      |  S1
Track -   | 494  |      |  S4
Phone     |      |  578 |  S6
R/T       |      |  308 |  S5

The Alpine interface code is copied from
https://github.com/Wnthr/arduino-alpine-remote/tree/master
*/

#include "AlpineRemote.h"
#include <AnalogButtons.h>
#include <Arduino.h>

#define ANALOG_PIN_AUDIO A0
#define ANALOG_PIN_MISC A1

// Define the pin used for output to the head unit
const int alpinePin = 5;

// Create the Alpine output object
AlpineRemote alpine(alpinePin);

// Button Definition: Track +
void b1Click() {
  SERIAL_PORT_MONITOR.println("Track + click");
  alpine.writeTrackUp();
}
void b1Hold() {
  SERIAL_PORT_MONITOR.println("Track + hold");
  alpine.writeTrackUp();
}

// Button Definition: Volume +
void b2Click() {
  SERIAL_PORT_MONITOR.println("Volume + click");
  alpine.writeVolumeUp();
}
void b2Hold() {
  SERIAL_PORT_MONITOR.println("Volume + hold");
  alpine.writeVolumeUp();
}

// Button Definition: Volume -
void b3Click() {
  SERIAL_PORT_MONITOR.println("Volume - click");
  alpine.writeVolumeDown();
}
void b3Hold() {
  SERIAL_PORT_MONITOR.println("Volume - hold");
  alpine.writeVolumeDown();
}

// Button Definition: Track -
void b4Click() {
  SERIAL_PORT_MONITOR.println("Track - click");
  alpine.writeTrackDown();
}
void b4Hold() {
  SERIAL_PORT_MONITOR.println("Track - hold");
  alpine.writeTrackDown();
}

// Button Definition: R/T
void b5Click() {
  SERIAL_PORT_MONITOR.println("R/T click");
  alpine.writeSourceSelect();
}

// Button Definition: Phone
void b6Click() {
  SERIAL_PORT_MONITOR.println("Phone click");
  alpine.writePhone();
}

// Create our button objects
AnalogButtons analogButtonsAudio(ANALOG_PIN_AUDIO, INPUT);
AnalogButtons analogButtonsMisc(ANALOG_PIN_MISC, INPUT);

// Define our button behaviors. We are over-riding some of the defaults so
// that held buttons repeat every 100ms or 300ms and a hold is detected after
// 500ms.
Button b1 = Button(315, &b1Click, &b1Hold, 500, 300);
Button b2 = Button(679, &b2Click, &b2Hold, 500, 100);
Button b3 = Button(148, &b3Click, &b3Hold, 500, 100);
Button b4 = Button(494, &b4Click, &b4Hold, 500, 300);
Button b5 = Button(308, &b5Click);
Button b6 = Button(578, &b6Click);

// Perform the main setup
void setup() {
  SERIAL_PORT_MONITOR.begin(115200);
  while (!Serial) {
  };
  SERIAL_PORT_MONITOR.println("Initialising the buttons here ...");

  analogButtonsAudio.add(b1);
  analogButtonsAudio.add(b2);
  analogButtonsAudio.add(b3);
  analogButtonsAudio.add(b4);
  analogButtonsMisc.add(b5);
  analogButtonsMisc.add(b6);
}

// Start executing the main loop
void loop() {
  analogButtonsAudio.check();
  analogButtonsMisc.check();
  // SERIAL_PORT_MONITOR.println(analogRead(ANALOG_PIN_AUDIO));
  // SERIAL_PORT_MONITOR.println(analogRead(ANALOG_PIN_MISC));
  // SERIAL_PORT_MONITOR.println();
  // delay(2000);
}
