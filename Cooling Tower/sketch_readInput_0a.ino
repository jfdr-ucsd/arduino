const int DIN_PIN = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode (DIN_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value;

  value = digitalRead (DIN_PIN);
  Serial.println(value);

  delay(1000);
}
