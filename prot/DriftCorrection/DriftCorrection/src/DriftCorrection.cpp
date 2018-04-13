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

unsigned int initialDisplacement;
unsigned int dRight;
unsigned int dLeft;
bool onCourse = false;
String debug;

void setup() {
  // put your setup code here, to run once:
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
    initialDisplacement = gyro.getAngularDisplacement();
    debug = "reference offset set: " + initialDisplacement;
    Serial.println(debug);
  }

  else if(car.getAngle()==0 && initialDisplacement != gyro.getAngularDisplacement())
  {
    Serial.println("Drifting detected, correcting..");
    if(initialDisplacement>gyro.getAngularDisplacement())
    {
      dRight = gyro.getAngularDisplacement() - initialDisplacement;
      dLeft = 360-dRight;
    }
    else
    {
      dLeft = gyro.getAngularDisplacement() - initialDisplacement;
      dRight = 360-dLeft;
    }

    if(dLeft<dRight)
    {
      car.setAngle(-45);
    }
    else
    {
      car.setAngle(45);
    }
    onCourse = false;
  }

  else if(car.getAngle()!=0 && initialDisplacement == gyro.getAngularDisplacement())
  {
    Serial.println("Drift corrected. Returning to previous state");
    onCourse = true;
    car.setAngle(0);
  }

}
