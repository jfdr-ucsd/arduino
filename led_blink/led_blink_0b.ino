/*
 * Expanding the blink program beyond the onboard LED
 * or pin 13, which is tied to the onboard LED
 */

// define the LED pin

int led = 8;


void setup() {
  // initialize the chosen LED pin as an output
  pinMode(led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
