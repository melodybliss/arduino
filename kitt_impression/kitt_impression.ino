// Array for LED pins
byte ledPin[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int ledDelay;  // delay between changes
int direction = 1;
int currentLED = 0;
unsigned long changeTime;
int potPin = 2;  // where the pot lives

void setup() {
  for(int x = 0; x < 10; x++) {
    // Set all pins to output
    pinMode(ledPin[x], OUTPUT);
  }
  
  changeTime = millis();
}

void loop() {
  ledDelay = analogRead(potPin);  // read value from the pot
  
  if((millis() - changeTime) > ledDelay) {
    // if it has been ledDelay ms since last change
    changeLED();
    changeTime = millis();
  }
}

void changeLED() {
  for(int x = 0; x < 10; x++) {
    // Turn off all LED's
    digitalWrite(ledPin[x], LOW);
  }
  
  // Turn on current LED
  digitalWrite(ledPin[currentLED], HIGH);
  currentLED += direction;  // increment by the direction value
  // change direction if we reach the end
  if (currentLED == 9) { direction = -1; }
  if (currentLED == 0) { direction = 1; }
}
