#include <Servo.h>

Servo thumbServo;
Servo indexServo;
Servo middleServo;

int servoPin_thumb = 9;
int servoPin_index = 7;
int servoPin_middle = 6;


const int thumbPin = A0;
const int indexPin = A1;
const int middlePin = A2;

int flexValue1;
int flexValue2;
int flexValue3;

void setup() {
  // put your setup code here, to run once:
  thumbServo.attach(servoPin_thumb);
  indexServo.attach(servoPin_index);
  middleServo.attach(servoPin_middle);
  Serial.begin(9600);
}

void loop() {
  // Läser av analoga värdet (0-1023)
  flexValue1 = analogRead(thumbPin) - 30;
  flexValue2 = analogRead(indexPin);
  flexValue3 = analogRead(middlePin);

  // Skriver ut värdet i Serial Monitor
  Serial.print("Flexsensorvärde för tumme: ");
  Serial.print(flexValue1);
  Serial.print("  Flexsensorvärde för pekfinger: ");
  Serial.print(flexValue2);
  Serial.print("  Flexsensorvärde för långfinger: ");
  Serial.println(flexValue3);


  // Kort fördröjning för att undvika överflödig data
 

  thumb();
  index();
  middle();


  if (Serial.available() > 0) {
    int command = Serial.parseInt();

    if (command == 0) {
      indexServo.write(0);
      middleServo.write(0);
    }
    else if (command == 1) {
      indexServo.write(90);
      middleServo.write(0);      
    }
    else if (command == 2) {
      indexServo.write(0);
      middleServo.write(90);
    }
    else if (command == 12) {
      indexServo.write(90);      
      middleServo.write(90);      
    }
  }
}


void thumb() {
 int servoAngle_thumb = map(flexValue1, 800, 880, 0, 180);
  servoAngle_thumb = constrain(servoAngle_thumb, 0, 180);

  thumbServo.write(servoAngle_thumb);
}

void index() {
  int servoAngle_index = map(flexValue2, 800, 980, 0, 180);
  servoAngle_index = constrain(servoAngle_index, 0, 180);

  indexServo.write(servoAngle_index);
}

void middle() {
  int servoAngle_middle = map(flexValue3, 800, 930, 0, 180);
  servoAngle_middle = constrain(servoAngle_middle, 0, 180);

  indexServo.write(servoAngle_middle);
}