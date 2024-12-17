#include <Servo.h>

class Sweeper {
  Servo servo;             
  int pos;      // current position
  int increment;   
  int updateInterval;   
  unsigned long lastUpdate; 

public:
  Sweeper(int interval) {
    updateInterval = interval;
    increment = 1;
    pos = 0; // Initialize position
    lastUpdate = 0; //last update time
  }

  void Attach(int pin) {
    servo.attach(pin);
  }

  void Detach() {
    servo.detach();
  }

  void Update() {
    if((millis() - lastUpdate) > updateInterval) { // time to update
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      if ((pos >= 180) || (pos <= 0)) { // end of sweep
        increment = -increment; // reverse direction
      }
    }
  }
};

class Flasher {
  int ledPin;              // the number of the LED pin
  long OnTime;             // milliseconds of on-time
  long OffTime;            // milliseconds of off-time
  int ledState;            // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

public:
  Flasher(int pin, long on, long off) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    OnTime = on;
    OffTime = off;
    ledState = LOW;
    previousMillis = 0;
  }

  void Update() {
    unsigned long currentMillis = millis();
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime)) {
      ledState = LOW;  // off
      previousMillis = currentMillis;  
      digitalWrite(ledPin, ledState);  // update LED
    } else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime)) {
      ledState = HIGH;  //  on
      previousMillis = currentMillis;  // time remember
      digitalWrite(ledPin, ledState);  // update state
    }
  }
};
//////////////FOR 3 LEDs with seperate timings
Flasher led1(11, 1000, 1000);  // Flasher for LED on pin 11, on and off time 1 second
Flasher led2(12, 500, 1500);   // Flasher for LED on pin 12, on time 500 ms, off time 1500 ms
Flasher led3(13, 2000, 500);   // Flasher for LED on pin 13, on time 2000 ms, off time 500 ms
Sweeper servo1(15);            // Sweeper for servo with 15 ms update interval

void setup() {
  servo1.Attach(9);  // servo pin 9
}

void loop() {
  led1.Update();
  led2.Update();
  led3.Update();
  servo1.Update();
}
