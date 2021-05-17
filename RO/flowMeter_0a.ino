/*********************************************
 * Test Code for an Adafruit brass flow meter
 * Red -> +5v
 * Blk -> GND
 * yellow -> pin 2
 * 
 * Code lifted from the Adafruit demo page 
 * for the flow meter, adapted by JFdR
 *********************************************/

// define some stuff

// what pin the flow sensor on?
#define flowSensorPin 2
// variable to count the pulses
volatile uint16_t pulses = 0;
// state of pulse pin
volatile uint8_t lastFlowPinState;
// pulse timer
volatile uint32_t lastFlowRateTimer = 0;
// use pulse count and timer to calculate flow rate
volatile float flowRate;

// interrupt to look for signal data
SIGNAL (TIMER0_COMPA_vect) {

  uint8_t x = digitalRead (flowSensorPin);
  
  // no new data
  if (x == lastFlowPinState){
    lastFlowRateTimer++;
    return;
  }
  
  // new data
  if (x == HIGH){
    pulses++;
  }

  lastFlowPinState = x;
  flowRate = 1000.0;
  flowRate /= lastFlowRateTimer; // this is Hertz
  lastFlowRateTimer = 0;
}

// no idea what this does
void useInterrupt (boolean v) {
  if(v) {
    // Timer0 is already used for millis() - we'll just
    // interupt in the middle and call the "Compare A"
    // function from above
    OCR0A = 0xAF;
    TIMSK0 |= _BV (OCIE0A);
  } else {
    // do not call COMPA
    TIMSK0 &= ~_BV (OCIE0A);
  }
}

// initiate the stuff what needs initiating
void setup() {
  Serial.begin (9600);
  Serial.print ("Flow sensor test!");
  
  pinMode (flowSensorPin, INPUT);
  digitalWrite (flowSensorPin, HIGH);
  lastFlowPinState = digitalRead (flowSensorPin);
  useInterrupt (true);
}

// the main event
void loop() {
  Serial.print ("Pulses: ");  Serial.println (pulses, DEC);
  Serial.print ("Freq: ");    Serial.println (flowRate);

  /* for brass sensor: 
   *  Sensor Frequency (Hz) = 8.1 * Q (Liters / min)
   *  
   *  Why 8.1? WHO KNOWS!! Calibrate this?
   *  
   *  Liters = Q * time elapsed (sec) / 60 (sec / min)
   *  Liters = (Frequency (pulses / sec) / 8.1) * time elapsed (sec) / 60
   *  Liters = pulses / (8.1 * 60)
   */

   float liters = pulses;
   liters /= 8.1;
   liters -= 6; // Why less 6? WHO KNOWS? Calibrate this!
   liters /= 60;

   Serial.print (liters);     Serial.println (" Liters");

   delay (100);
}
