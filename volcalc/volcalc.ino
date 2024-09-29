#include <LiquidCrystal.h>
#include <math.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define DISTANCE_BOUND 30

double duration, radius, volume; 
double height = 0;
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
  delay(3000);
  lcd.clear();
  volume = (M_PI * pow(radius, 2) * 2);
  lcd.print("Volume: ");
  lcd.print(volume);
}
