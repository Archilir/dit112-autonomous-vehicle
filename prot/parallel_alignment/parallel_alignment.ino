9#include <Smartcar.h>
#include <String.h>


Car car;

Odometer encoderRight;
Odometer encoderLeft;
int offset = 25;
Gyroscope gyro(offset);

const int pinLeft = 2;
const int pinRight = 3;
const int lDegrees = -75; //degrees to turn left
const int rDegrees = 75; //degrees to turn right

int carSpeed = 50, carAngle = 75;
int direction = 1;
unsigned int currentAngularDisplacement;
bool onCourse = false;
String debug;


#include <Smartcar.h>

SR04 sonicFR, sonicBR, sonicB;

const int TRIGGER_PIN_FR = 44;
const int ECHO_PIN_FR    = 42;

const int TRIGGER_PIN_BR = 6;
const int ECHO_PIN_BR    = 7;


const int TRIGGER_PIN_B = 5;
const int ECHO_PIN_B    = 4;

bool deadlockState = false;


void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  gyro.attach();
  delay(1500);
  gyro.begin(60);
  encoderLeft.attach(pinLeft);
  encoderRight.attach(pinRight);
  encoderLeft.begin();
  encoderRight.begin();
  car.begin(encoderLeft, encoderRight, gyro);
  car.setSpeed(0.2);

  sonicFR.attach(TRIGGER_PIN_FR, ECHO_PIN_FR);
  sonicBR.attach(TRIGGER_PIN_BR, ECHO_PIN_BR);
  sonicB.attach(TRIGGER_PIN_B, ECHO_PIN_B);
}

void loop() {
  gyro.update();
  car.updateMotors();
  driftCorrection();
  debugPrint();
  carAlign();
}

void driftCorrection(){

    if(car.getAngle() == 0 && !onCourse)
    {
      onCourse = true;
      currentAngularDisplacement = gyro.getAngularDisplacement();
      debug = "reference offset set: " + currentAngularDisplacement;
      Serial.println(debug);
    }

    else if(car.getAngle()==0 && currentAngularDisplacement != gyro.getAngularDisplacement())
    {
      Serial.println("Drifting detected, correcting..");
      if(currentAngularDisplacement>1)
      {

        if(gyro.getAngularDisplacement()>currentAngularDisplacement)
        {
          Serial.println("Adjusting towards the left");
          car.setAngle(-45);
        }
        else if(gyro.getAngularDisplacement()<currentAngularDisplacement)
        {
          Serial.println("Adjusting towards the right");
          car.setAngle(45);
        }
      }
      else
      {
        if(gyro.getAngularDisplacement()>currentAngularDisplacement && gyro.getAngularDisplacement() <= 180)
        {
          Serial.println("Adjusting towards the left");
          car.setAngle(-45);
        }
        else if(gyro.getAngularDisplacement()<360 && gyro.getAngularDisplacement()>180)
        {
          Serial.println("Adjusting towards the right, taking ADisplacement overflow into consiteration");
          car.setAngle(45);
        }
      }
      onCourse = false;
    }

    else if(car.getAngle()!=0 && currentAngularDisplacement == gyro.getAngularDisplacement())
    {
      Serial.println("Drift corrected. Returning to previous state");
      onCourse = true;
      car.setAngle(0);
    }
}


void debugPrint() {

    Serial.print("Ultrasonic, FR, BR, B:\t");
    Serial.print(sonicFR.getDistance());
    Serial.print("\t");
    Serial.print(sonicBR.getDistance());
    Serial.print(" ");
    Serial.println(sonicB.getDistance());
}




void manualDrive(char input) {
  switch (input) {
    case 'w': //go ahead
      car.setSpeed(carSpeed);
      car.setAngle(0);
      break;
    case 's': //go back
      car.setSpeed(-carSpeed);
      car.setAngle(0);
      break;
    case 'a': //rotate counter-clockwise going forward
      car.setSpeed(carSpeed * direction);
      car.setAngle(-carAngle);
      break;
    case 'd': //turn clock-wise
      car.setSpeed(carSpeed * direction);
      car.setAngle(carAngle);
      break;
    case 'i': //increase spead by 10
      if (carSpeed < 100) { carSpeed += 5; }
      break;
    case 'k':
      if (carSpeed >   0) { carSpeed -= 5; }
      break;
    case 'l':
      if (carAngle <  90) { carAngle += 5; }
      break;
    case 'j':
      if (carAngle >   0) { carAngle -= 5; }
      break;
    case 'm':
      direction = direction * -1;
      break;
    case 'n':
      deadlockState = (deadlockState) ? false : true;
      break;
    default: //if you receive something that you don't know, just stop
      car.setSpeed(0);
      car.setAngle(0);
  }
}

void deadlock(char input) {
  if (input == 'n') {
      deadlockState = (deadlockState) ? false : true;
  }
  if (deadlockState) {
    car.setAngle(0);
    car.setSpeed(0);
  }
}

void carAlign(){

    int distanceFR = sonicFR.getDistance(),
        distanceBR = sonicBR.getDistance();

    if((distanceFR > 0 && distanceFR < 8) || (distanceBR > 0 && distanceBR < 8))  {
      if(car.getSpeed() != 0) {
        car.setSpeed(0);
       }
    }
    else4178t {
       if(car.getSpeed() != 30) {
        car.setSpeed(30);
       }
       align(distanceFR, distanceBR);
    }
}

void align(int distanceFR, int distanceBR) {

  if((distanceFR > 0 && distanceFR < 35) && (distanceBR > 0 && distanceBR < 35)){
       if(distanceFR > distanceBR) {
            car.setAngle(60);
        }
       else if(distanceFR < distanceBR){
            car.setAngle(-60);
       }
        else{
        car.setAngle(0);
        }
    } else{
      car.setAngle(0);
    }
}
