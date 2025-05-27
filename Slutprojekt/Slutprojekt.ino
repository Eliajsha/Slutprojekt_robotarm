/*
  File: Slutprojekt
  Author: Elias Svensson
  Date: 2025-05-13
  Description: This program uses 3 flex sensors or Open-cv and a camera in python to control a 3 fingered robotarm. 
*/



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

// All the pins are started
void setup() {
  Serial.begin(9600);
  thumbServo.attach(servoPin_thumb);
  indexServo.attach(servoPin_index);
  middleServo.attach(servoPin_middle);
  pinMode(buttonPin, INPUT);
  pinMode(13, OUTPUT);
}


// Runs all the code
void loop() {

  // This part calculates the value of the flex sensors.
  int raw1 = analogRead(thumbPin);
  int raw2 = analogRead(indexPin);
  int raw3 = analogRead(middlePin);

  flexValue1 = applyDeadzone(raw1, prevThumb, thresh);
  flexValue2 = applyDeadzone(raw2, prevIndex, thresh);
  flexValue3 = applyDeadzone(raw3, prevMiddle, thresh);

  int buttonState = digitalRead(buttonPin);


  // This if-statement checks if the button is being pressed, and if it is, it changes the value of the variable which from true to false or from false to true.
  if (buttonState == HIGH) {
    which = !which;
    delay(500);
  }

  // This if-statment runs the code for the camera and the flexsensors. If the button has been pressed and is set to true, it will run the cameras code, otherwise it will run the code for the flex sensors.
  if (which == true) {
    camera();
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
    thumb();
    index();
    middle();
  }
}

/*
  Maps the value of the flex sensor for the thumb to 0-180 degrees and then changes angle depending on the value
  Parameters: None
  Returns: Void
*/
void thumb() {
  int servoAngle_thumb = map(flexValue1, 990, 1010, 0, 180);
  servoAngle_thumb = constrain(servoAngle_thumb, 0, 180);

  thumbServo.write(servoAngle_thumb);
}

/*
  Maps the value of the flex sensor for the index finger to 0-180 degrees and then changes angle depending on the value
  Parameters: None
  Returns: Void
*/
void index() {
  int servoAngle_index = map(flexValue2, 995, 1020, 0, 180);
  servoAngle_index = constrain(servoAngle_index, 0, 180);

  indexServo.write(servoAngle_index);
}

/*
  Maps the value of the flex sensor for the middle finger to 0-180 degrees and then changes angle depending on the value
  Parameters: None
  Returns: Void
*/
void middle() {
  int servoAngle_middle = map(flexValue3, 900, 1023, 0, 180);
  servoAngle_middle = constrain(servoAngle_middle, 0, 180);

  middleServo.write(servoAngle_middle);
}

/*
  Changes angle of the servomotors depending on what value is sent from python
  Paramteters: None
  Returns: void
*/
void camera() {
  if (Serial.available() > 0) {
    int command = Serial.parseInt();

    if (command == 0) {
      thumbServo.write(180);  //The values of the thumb servomotor is reversed since the motor was placed on the wrong side of the thumb. The thumb will be closed if the value is 180 and will be open if the value is 0. When the value is 180 on the other motors i means they open and then are closed when the value is 0.
      indexServo.write(0);
      middleServo.write(0);
    }

    else if (command == 1) {
      thumbServo.write(0);  // Open
      indexServo.write(0);
      middleServo.write(0);
    }

    else if (command == 2) {
      thumbServo.write(180);  // Closed
      indexServo.write(180);
      middleServo.write(0);
    }

    else if (command == 3) {
      thumbServo.write(180);  // Closed
      indexServo.write(0);
      middleServo.write(180);
    }

    else if (command == 12) {
      thumbServo.write(0);  // Open
      indexServo.write(180);
      middleServo.write(0);
    }

    else if (command == 123) {
      thumbServo.write(0);  // Open
      indexServo.write(180);
      middleServo.write(180);
    }

    else if (command == 23) {
      thumbServo.write(180);  // Closed
      indexServo.write(180);
      middleServo.write(180);
    }

    else if (command == 13) {
      thumbServo.write(0);  // Open
      indexServo.write(0);
      middleServo.write(180);
    }
  }
}

/*
  This function sets a deadzone for the flex sensors
  Parameters: 
  - rawValue: The exact value that the sensor sends
  - prevValue: The value that was before the rawValue
  - threshold: The size of the deadzone
  Returns: The value which should be sent to the motors. 
*/
int applyDeadzone(int rawValue, int &prevValue, int threshold) {
  if (abs(rawValue - prevValue) > threshold) {
    prevValue = rawValue;
  }
  return prevValue;
}