#include <TM1637.h>

int CLK_PIN = 12;
int DIO_PIN = 13;

TM1637 tm (CLK_PIN, DIO_PIN);

void setup() {
  // initialize the LCD
  tm.init();
  // set LCD brightness 0-7
  tm.set(2);
}

void loop() {
  // the main loop
  /*  Generally:
   *  tm.display (position, character);
  */
   
  // example "12:ab"
  tm.display (0,1);
  tm.display (1,2);
  tm.point (1);
  tm.display (2,10);
  tm.display (3,11);

  delay (1000);

  displayNumber (1234);

  delay (1000);
}

void displayNumber (int num) {
  tm.display (3, num % 10);
  tm.display (2, num / 10 % 10);
  tm.display (1, num / 100 % 10);
  tm.display (0, num / 1000 % 10);
}
