#include <LiquidCrystal.h>
const int trigPin = 1;  // Ultrasonic sensor trigger pin
const int echoPin = 2; // Ultrasonic sensor echo pin
const int blueLedPin = 3;
const int greenLedPin = 4;
const int yellowLedPin = 5;
const int redLedPin = 6;
const int buzzerPin = 7;
long duration;
int distance , currentCase = 0 , waterLevelPercent;
int previousCase = -1;  // Variable to store the previous water level case
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);  // LCD pins (RS, E, D4, D5, D6, D7)
void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Welcome to our ");
  lcd.setCursor(0,1);
  lcd.print("    Project     ");
  delay(5000);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034 / 2 ) - 2;
  waterLevelPercent = (8 - distance) * 18 * 28 * 100 / 4000;
  if (distance >= 0 && distance <= 2) {
    currentCase = 1;
    digitalWrite(blueLedPin, HIGH);
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("FULL            ");
  } else if (distance > 2 && distance <= 4) {
    currentCase = 2;
    digitalWrite(blueLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Almost FULL     ");
  } else if (distance > 4 && distance <= 6) {
    currentCase = 3;
    digitalWrite(blueLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Half FULL       ");
  }
  else if (distance > 6 && distance < 8) {
    currentCase = 4;
    digitalWrite(blueLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Almost EMPTY    ");
  }
  if (currentCase != previousCase) {
    triggerBuzzer();
    previousCase = currentCase;
  }
  lcd.setCursor(0, 1);
  lcd.print("Water Level: ");
  lcd.print(waterLevelPercent);
  lcd.print("%");
  if (distance >=8)
  {
    currentCase = 5;
    digitalWrite(blueLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("EMPTY           ");
  }
  delay(1000);
}
void triggerBuzzer() {
  tone(buzzerPin, 1000, 500);
  delay(500);
  noTone(buzzerPin);
}
