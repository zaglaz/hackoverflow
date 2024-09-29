#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 4, 5, 6, 3);

const int trigPin = 9;
const int echoPin = 10;

double duration;
double distance;
const int fixedDistance = 30; // Fixed distance to the reference point
double bottleDistance;
double diameter;
double radius;
double speed = 0.3; // Speed in cm/us (adjust as necessary)
double height;
double volume;

// Threshold for significant change in distance
const double changeThreshold = 20.0; // Change in distance threshold

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.print("Measuring...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets trigPin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance in centimeters
  bottleDistance = duration * 0.034 / 2; // Speed of sound in cm/us

  // Calculating the diameter and radius
  diameter = fixedDistance - bottleDistance;
  radius = diameter / 2;

  // Display distance, diameter, and radius
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(bottleDistance);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  lcd.print("Diam: ");
  lcd.print(diameter);
  lcd.print(" Rad: ");
  lcd.print(radius);  // Printing radius

  // Check for significant change in distance
  static double lastBottleDistance = 0; // Variable to store the last distance reading
  if (abs(bottleDistance - lastBottleDistance) > changeThreshold) {
    // Significant change detected; save last duration for height calculation
    double lastDuration = duration; // Store the last duration

    // Calculate height based on speed and lastDuration
    height = lastDuration * speed; // Height in cm based on sensor movement

    // Calculate volume of the cylinder
    volume = 3.14159 * radius * radius * height; // Volume in cubic centimeters (cm³)

    // Display height and volume
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Height: ");
    lcd.print(height);
    lcd.print(" cm");

    lcd.setCursor(0, 1);
    lcd.print("Volume: "); // Displaying "Volume:" instead of "Vol:"
    lcd.print(volume);
    lcd.print(" cm³");

    delay(1000); // Delay for readability
  }

  // Update lastBottleDistance for the next iteration
  lastBottleDistance = bottleDistance;

  delay(100); // Delay to slow down the loop
}
