#include <LiquidCrystal.h>
#include <math.h>

#define TRIG_PIN 6
#define ECHO_PIN 9
#define MOTOR_PIN 8
#define VELOCITY 0.1
#define DISTANCE_BOUND 30

double duration, radius, volume, height; 
int timeMoved = 0;
static float currentDistance = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

double getDistance(double duration) {
  return (duration * 0.0343)/2;
}

void ultrasonicSensorSetup(unsigned int triggerPin) {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
}

void setup() {

  //Initialize LCD screen/serial monitor
  lcd.begin(16, 2);
  Serial.begin(9600);

  //Initialize components
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 // pinMode(motorPin, OUTPUT);

  //Start serial monitor/LCD dialogue
  Serial.print("VOLCALC");
  lcd.print("Measuring...");
  delay(2000);
  lcd.clear();
}

void loop() {
  //LCD update
  lcd.setCursor(0, 1);
  ultrasonicSensorSetup(TRIG_PIN);

  //Radius compute
  duration = pulseIn(ECHO_PIN, HIGH);
  if (getDistance(duration) <= 30 && getDistance(duration) >= 0) {
    radius = (DISTANCE_BOUND - getDistance(duration)) / 2;
  }

  //Radius output
  lcd.print("Radius: ");
  lcd.print(radius);
  delay(2000);
  lcd.clear();

  //Height compute 
  while (getDistance(duration) <= 30 && getDistance(duration) >= 0) {
    ultrasonicSensorSetup(TRIG_PIN);
    duration = pulseIn(ECHO_PIN, HIGH);
    currentDistance = getDistance(duration);

    if (currentDistance <= 30 && currentDistance >= 0) {
      ++timeMoved;
      delay(1000);
    } 

    else {
      height = timeMoved * VELOCITY;
      // LCD Output
      lcd.setCursor(0, 1);  
      lcd.print("Height: ");
      lcd.print(height);
      timeMoved = 0;
      break;
    }
  }
  delay(2000);

  //Volume output
  lcd.clear();
  volume = (M_PI * pow(radius, 2) * height);
  lcd.print("Volume: ");
  lcd.print(volume);
  delay(5000);
}
