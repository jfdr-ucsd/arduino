/*********************************************
 * Test Code for an Adafruit brass flow meter
 * Red -> +5v
 * Blk -> GND
 * yellow -> pin 2
 * 
 * Adafruit demo page code didn't work
 * Adapted new code from bc-robotics.com
 *********************************************/
// the LCD library
#include <TM1637.h>
// define some stuff

// The pins for the LCD screen
int CLK_PIN = 12;
int DIO_PIN = 13;

// Set LCD pins
TM1637 tm (CLK_PIN, DIO_PIN);

// flow sensor pin
int flowPin = 2;

// variable to count the pulses
volatile int count;
// timer iteration
double seconds = 0;
// count total
double pulseTotal = 0;
// average of the counts
double pulseAvg = 0;

// flowrate in L / m
double flowL;
// flowrate in mL / m
double flowML;
// flowrate in mL / s
double flowMLS;


// the initial, one-time code
void setup () {
  // setup the flow sensor pin
  pinMode (flowPin, INPUT);
  attachInterrupt (0, flow, RISING);

  // initialize the LCD
  tm.init();
  // set LCD brightness 0-7
  tm.set(4);
  // send a test message to the display
  tm.display (0,1);
  tm.display (1,2);
  tm.point (1);
  tm.display (2,3);
  tm.display (3,4);
  
  Serial.begin (9600);
}


// the main loop
void loop () {
  // count pulses for a while
  count = 0;
  interrupts();
  delay (1000);
  noInterrupts();  
  seconds = seconds + 1;
  
  // do some math
  pulseTotal = pulseTotal + count;
  pulseAvg = pulseTotal / seconds;
  
  /*
   * there is a required "conversion factor"
   * to go from pulses to SI units.
   * Adafruit suggest 2.25 for plastic flow meter
   *              and 2.00 for brass flow meter
   * But also STRONGLY suggest calibrating             
*/
  Serial.print ("   Second: "); Serial.print (seconds);
  Serial.print ("   Counts: "); Serial.print (count);
  Serial.print ("   Total:  "); Serial.print (pulseTotal);
  Serial.print ("   Average: "); Serial.println (pulseAvg);

  // displaying L/m on the LCD
  flowMLS = (count * 2.6);    // Conversion for plastic flow meter
  flowML = flowMLS * 60;     // convert seconds to minutes
  flowL = flowML / 1000;   // mL to Liters

  displayNumber (flowML);
}

// an interrupt for when flow is detected
void flow () {
  count++;
}

// displays an integer passed to it
void displayNumber (int num) {
  // I think % is a modulo function
  tm.display (3, num /10 % 10);
  tm.display (2, num / 100 % 10);
  tm.point  (1);
  tm.display (1, num / 1000 % 10);
  tm.display (0, num / 10000 % 10);
}
