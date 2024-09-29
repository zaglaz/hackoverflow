/*#include <LiquidCrystal.h>
#include <math.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define DISTANCE_BOUND 30

double duration, radius;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

double getDistance(double duration) {
  return (duration * 0.0343)/2;
}

void setup() {

  //Initialize LCD screen/serial monitor
  lcd.begin(16, 2);
  Serial.begin(9600);

  //Initialize ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //Start serial monitor/LCD dialogue
  Serial.print("VOLCALC");
  lcd.print("Measuring...");
  delay(2000);
  lcd.clear();
}

void loop() {
  //LCD update
  lcd.setCursor(0, 1);

  //US sensor capture
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  radius = (DISTANCE_BOUND - getDistance(duration)) / 2;
  Serial.println(getDistance(duration));
  Serial.println(radius);
  lcd.print("Radius: ");
  lcd.print(radius);

  delay(2000);
}
*/
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;
int fixedDistance = 30; // The known distance between the sensor and a reference point
int bottleDistance;
int diameter;
int radius;

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.print("Measuring...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set trigPin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and return the sound wave travel time
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  bottleDistance = duration * 0.034 / 2;

  // Calculate the diameter and radius
  diameter = fixedDistance - bottleDistance;
  radius = diameter / 2;

  // Clear the LCD
  lcd.clear();

  // Display distance, diameter, and radius
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(bottleDistance);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  lcd.print("Diam: ");
  lcd.print(diameter);
  lcd.print(" Rad: ");
  lcd.print(radius);

  delay(100);  // Slow down the loop for readability
}
