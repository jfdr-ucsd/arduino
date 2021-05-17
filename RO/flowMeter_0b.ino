/*********************************************
 * Test Code for an Adafruit brass flow meter
 * Red -> +5v
 * Blk -> GND
 * yellow -> pin 2
 * 
 * Adafruit demo page code didn't work
 * Adapted new code from bc-robotics.com
 *********************************************/

// define some stuff

// what pin the flow sensor on?
int flowPin = 2;
// variable to count the pulses
volatile int count;
// variable for the calculations 
double flowRate;

// the initial, one-time code
void setup () {
  pinMode (flowPin, INPUT);
  attachInterrupt (0, flow, RISING);
  Serial.begin (9600);
}


// the main loop
void loop () {
  // count pulses for a second
  count = 0;
  interrupts();
  delay (2000);
  noInterrupts();  

  // do some math
  flowRate = (count * 2.25);    // This is magic constant to take pulses to mL
  flowRate = flowRate * 60;     // convert seconds to minutes
  flowRate = flowRate / 1000;   // mL to Liters

  Serial.print ("Flow is: "); Serial.println (flowRate);
}

// an interrupt for when flow is detected
void flow () {
  count++;
}
