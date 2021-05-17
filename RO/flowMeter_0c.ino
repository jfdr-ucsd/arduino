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
// variable for the calculations 
double flowL;
// variable for the display
double flowML;

// the initial, one-time code
void setup () {
  // setup the flow sensor pin
  pinMode (flowPin, INPUT);
  attachInterrupt (0, flow, RISING);

  // initialize the LCD
  tm.init();
  // set LCD brightness 0-7
  tm.set(2);

  Serial.begin (9600);
}


// the main loop
void loop () {
  // count pulses for a while
  count = 0;
  interrupts();
  delay (1000);
  noInterrupts();  

  // do some math
  /*
   * there is a required "conversion factor"
   * to go from pulses to SI units.
   * Adafruit suggest 2.25 for plastic flow meter
   *              and 2.00 for brass flow meter
   * But also STRONGLY suggest calibrating             
   */
   
  flowML = (count * 2.25);    // Conversion for plastic flow meter
  flowML = flowML * 60;     // convert seconds to minutes
  flowL = flowML / 1000;   // mL to Liters

  displayNumber (flowML);

  Serial.print ("Flow is: "); Serial.print (flowML); Serial.println (" mililiters / minute");
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
