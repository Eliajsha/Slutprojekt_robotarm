#include <Servo.h>

Servo thumbServo;
Servo indexServo;
Servo middleServo;

int servoPin_thumb = 9;
int servoPin_index = 7;
int servoPin_middle = 6;
int flexValue1;
int flexValue2;
int flexValue3;
int prevThumb = 0;
int prevIndex = 0;
int prevMiddle = 0;

const int thumbPin = A0;
const int indexPin = A1;
const int middlePin = A2;
const int buttonPin = 11;
const int thresh = 20;
 
bool which = true;

void setup() {
  Serial.begin(9600);
  thumbServo.attach(servoPin_thumb);
  indexServo.attach(servoPin_index);
  middleServo.attach(servoPin_middle);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int raw1 = analogRead(thumbPin);
  int raw2 = analogRead(indexPin);
  int raw3 = analogRead(middlePin);

  flexValue1 = applyDeadzone(raw1, prevThumb, thresh);
  flexValue2 = applyDeadzone(raw2, prevIndex, thresh);
  flexValue3 = applyDeadzone(raw3, prevMiddle, thresh);
  
  int buttonState = digitalRead(buttonPin);



  if (buttonState == HIGH) {
    which = !which;
    delay(500);
  }

  if (which == true) {
    camera();
  }
  else {
    thumb();
    index();
    middle();
  }
}


void thumb() {
 int servoAngle_thumb = map(flexValue1, 650, 800, 0, 180);
  servoAngle_thumb = constrain(servoAngle_thumb, 0, 180);

  thumbServo.write(servoAngle_thumb);
}

void index() {
  int servoAngle_index = map(flexValue2, 800, 1000, 0, 180);
  servoAngle_index = constrain(servoAngle_index, 0, 180);

  indexServo.write(servoAngle_index);
}

void middle() {
  int servoAngle_middle = map(flexValue3, 800, 930, 0, 180);
  servoAngle_middle = constrain(servoAngle_middle, 0, 180);

  middleServo.write(servoAngle_middle);
}

void camera () {
   if (Serial.available() > 0) {
    int command = Serial.parseInt();

    if (command == 0) {
      thumbServo.write(0);
      indexServo.write(0);
      middleServo.write(0);
    }

    else if (command == 1) {
      thumbServo.write(90);
      indexServo.write(0);
      middleServo.write(0);      
    }

    else if (command == 2) {
      thumbServo.write(0);
      indexServo.write(90);
      middleServo.write(0);
    }

    else if (command == 3) {
      thumbServo.write(0);
      indexServo.write(0);      
      middleServo.write(90);      
    }
    
    else if (command == 12) {
      thumbServo.write(90);
      indexServo.write(90);      
      middleServo.write(0);  
    }

    else if (command == 123) {
      thumbServo.write(90);
      indexServo.write(90);      
      middleServo.write(90);  
    }

    else if (command == 23) {
      thumbServo.write(0);
      indexServo.write(90);      
      middleServo.write(90);  
    }

    else if (command == 13) {
      thumbServo.write(90);
      indexServo.write(0);      
      middleServo.write(90);  
    }
  }
}

int applyDeadzone(int rawValue, int &prevValue, int threshold) {
  if (abs(rawValue - prevValue) > threshold) {
    prevValue = rawValue;
  }
  return prevValue;
}