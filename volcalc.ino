#include <LiquidCrystal.h>
#include <math.h>

const int trigPin = 9; 
const int echoPin = 10;
float duration, distance;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//String volume = String(tan(M_PI * 45/180));

void setup(){
  //LCD screen
  lcd.begin(16, 2);

  //Ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop(){
  //LCD update
  lcd.setCursor(0, 1);

  //US sensor capture
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  

  //US sensor distance calculation and output
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  lcd.print(distance);
  delay(100);
}
