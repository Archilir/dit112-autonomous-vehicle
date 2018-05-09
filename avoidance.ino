#include <Smartcar.h>

Car car;
int medianBack = 0;
int carSpeed = 50, carAngle = 75;
int direction = 1;

#include <Smartcar.h>

SR04 sonicFR, sonicBR, sonicB;
// Front - Right ultrasonic sensor
const int TRIGGER_PIN_FR = 44;
const int ECHO_PIN_FR    = 42;

// Back - Right ultrasonic sensor
const int TRIGGER_PIN_BR = 6;
const int ECHO_PIN_BR    = 7;

// Back ultrasonic sensor
const int TRIGGER_PIN_B = 5;
const int ECHO_PIN_B    = 4;

int medianreadFront = sonicFR.getMedianDistance(5);

void setup() {
  Serial.begin(9600);
  car.begin(); //initialize the car using the encoders and the gyro
  sonicA.attach(TRIGGER_PIN_FR, ECHO_PIN_FR); //trigger pin, echo pin
}


void loop() {
    debugPrint();
    testdone();
 }

void debugPrint() {

}

void firstPart() {

if (distanceCenter >= 15)

{}

  else
{

if (distanceLeft > distanceRight)
  {moveleft}

if (distanceRight > distanceLeft)
  {moveright}

if (distanceLeft <= 10 && distanceCenter <= 10 || distanceRight <= 10 && distanceCenter <= 10)
  {moveback}

}

}

 void moveleft() {
   car.setAngle(car.getAngle() - 10)
 }

  void moveback() {
    car.setSpeed(-50)
    car.setAngle(0)
  }

   void moveright() {
     car.setAngle(car.getAngle() + 10)
   }


  int minusspeed = 100-sonicFR.getMedianDistance(3);
  if (medianreadFront < 5 && 0 < medianreadFront ) {
  car.setAngle(-45);
  car.setSpeed(getspeed-minusspeed);
 }
 else
 car.setSpeed(0);
}
