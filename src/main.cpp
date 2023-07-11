#include <AnalogButtons.h>
#include <Arduino.h>

#define ANALOG_PIN_MISC A0
#define ANALOG_PIN_AUDIO A1

// A call back function that you pass into the constructor of AnalogButtons, see
// example below. Alternativly you could extend the Button class and re-define
// the methods pressed() or held() which are called
void b1Click() { Serial.print("button 1 clicked"); }
void b1Hold() { Serial.print("button 1 held"); }

void b2Click() { Serial.print("button 2 clicked"); }
void b2Hold() { Serial.print("button 2 held"); }

void b3Click() { Serial.print("button 3 clicked"); }
void b3Hold() { Serial.print("button 3 held"); }

void b4Click() { Serial.print("button 4 clicked"); }
void b4Hold() { Serial.print("button 4 held"); }

void b5Click() { Serial.print("button 5 clicked"); }
void b5Hold() { Serial.print("button 5 held"); }

void b6Click() { Serial.print("button 6 clicked"); }
void b6Hold() { Serial.print("button 6 held"); }

AnalogButtons analogButtonsAudio(ANALOG_PIN_AUDIO, INPUT);
AnalogButtons analogButtonsMisc(ANALOG_PIN_MISC, INPUT);
Button b1 = Button(1002, &b2Click, &b2Hold);
Button b2 = Button(1002, &b2Click, &b2Hold);
Button b3 = Button(970, &b3Click, &b3Hold);
// Default hold activation frequency of 250ms is overriden for button 4 so to
// get it activated (hold function invoked) only every 500ms
Button b4 = Button(929, &b4Click, &b4Hold, 1000, 500);
// Default hold duration is 1 second, lets make it 5 seconds for button5
Button b5 = Button(860, &b5Click, &b5Hold, 5000);
Button b6 = Button(1002, &b2Click, &b2Hold);

void setup() {
  SERIAL_PORT_MONITOR.begin(115200);
  while (!Serial) {
  };
  SERIAL_PORT_MONITOR.println("Testing your Analog buttons");

  analogButtonsAudio.add(b1);
  analogButtonsAudio.add(b2);
  analogButtonsAudio.add(b3);
  analogButtonsAudio.add(b4);
  analogButtonsMisc.add(b5);
  analogButtonsMisc.add(b6);
}

void loop() {
  // To check values when button are pressed
  analogButtonsAudio.check();
  analogButtonsMisc.check();
}

/*
State       Audio       Misc      Switch Number
Resting     880         865
Vol +       679                   S2
Vol -       148                   S3
Track +     315                   S1
Track -     494                   S4
Phone                   578       S6
R/T                     308       S5
*/