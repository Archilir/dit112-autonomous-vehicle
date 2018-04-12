#include <Smartcar.h>
#include <String.h>

Odometer encoderRight;
Odometer encoderLeft;
Car car;
int offset = 25;
Gyroscope gyro(offset);

const int pinLeft = 2;
const int pinRight = 3;
const int lDegrees = -75; //degrees to turn left
const int rDegrees = 75; //degrees to turn right
int carSpeed = 1.5;
int carAngle = 75;

int currentAngularDisplacement;
bool onCourse = false;
String debug;

void setup() {
  // put your setup code here, to run once:
  Serial3.begin(9600);

  gyro.attach();
  Serial.begin(9600);
  delay(1500);
  gyro.begin(60);

  encoderLeft.attach(pinLeft);
  encoderRight.attach(pinRight);

  encoderLeft.begin();
  encoderRight.begin();
  car.begin(encoderLeft, encoderRight, gyro);
  car.enableCruiseControl();
  car.setSpeed(0.2);

}

void loop() {
  // put your main code here, to run repeatedly:
  gyro.update();
  car.updateMotors();
  Serial.println(gyro.getAngularDisplacement());

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
        car.setAngle(-45);
      }
      else if(gyro.getAngularDisplacement()<currentAngularDisplacement)
      {
        car.setAngle(45);
      }
    }
    else
    {
      if(gyro.getAngularDisplacement()>currentAngularDisplacement)
      {
        car.setAngle(-45);
      }
      else if(gyro.getAngularDisplacement()<360 && gyro.getAngularDisplacement()>currentAngularDisplacement)
      {
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
