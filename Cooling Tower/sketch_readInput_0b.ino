const int DIN_PIN = 7;
const int LED_PIN = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode (DIN_PIN, INPUT);
  pinMode (LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int value;

  value = digitalRead (DIN_PIN);

  if (value == HIGH) {
    digitalWrite (LED_PIN, LOW);
  }else{
    digitalWrite (LED_PIN, HIGH);
  }

  delay(100);
}
