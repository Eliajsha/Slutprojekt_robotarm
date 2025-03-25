#include <Servo.h>

Servo thumbServo;
Servo indexServo;
int servoPin_thumb = 9;
int servoPin_index = 7;


const int thumbPin = A0;
const int indexPin = A1;
const int middlePin = A2;

void setup() {
  // put your setup code here, to run once:
  thumbServo.attach(servoPin_thumb);
  indexServo.attach(servoPin_index);
  Serial.begin(9600);
}

void loop() {
  // Läser av analoga värdet (0-1023)
  int flexValue1 = analogRead(thumbPin) - 30;
  int flexValue2 = analogRead(indexPin);
  int flexValue3 = analogRead(middlePin);

  // Skriver ut värdet i Serial Monitor
  Serial.print("Flexsensorvärde för tumme: ");
  Serial.print(flexValue1);
  Serial.print("  Flexsensorvärde för pekfinger: ");
  Serial.print(flexValue2);
  Serial.print("  Flexsensorvärde för långfinger: ");
  Serial.println(flexValue3);


  // Kort fördröjning för att undvika överflödig data
 


  int servoAngle_thumb = map(flexValue1, 800, 880, 0, 180);
  servoAngle_thumb = constrain(servoAngle_thumb, 0, 180);

  thumbServo.write(servoAngle_thumb);

  int servoAngle_index = map(flexValue2, 830, 900, 0, 180);
  servoAngle_index = constrain(servoAngle_index, 0, 180);

  indexServo.write(servoAngle_index);
}
