
// constants won't change. Used here to 
// set pin numbers:
const int trigger =  7;        // the Projector trigger pin
const int signal = 0;          // the Interrupt pin

// Variables will change:
long previousMicro = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in microseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 0;       // interval at which to blink (Microseconds)

long fullRotation = 0;         // Clock signal time in microseconds

void setup() {
  // set the digital pin as output:
  pinMode(trigger, OUTPUT);
  // Attach the interrupt
  attachInterrupt(signal, recievedClock, RISING);
}

void loop() {
  if (interval > 0) {
    previousMicro = micros();
    digitalWrite(trigger, HIGH);
    digitalWrite(trigger, LOW);
    delayMicroseconds(interval - (micros() - previousMicro));
  }
}

void recievedClock() {
  interval = micros() - fullRotation;
  interval = (interval / 12);
  fullRotation = micros();
}




