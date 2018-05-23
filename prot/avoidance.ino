#include <Smartcar.h>

Car car;

#include <Smartcar.h>

SR04 sonicA;
SR04 sonicB;

// Front Sensor, fill in with correct pin please
const int TRIGGER_PIN_FR = 45;
const int ECHO_PIN_FR    = 43;
const int TRIGGER_PIN_RR = 44;
const int ECHO_PIN_RR    = 42;

/*
backwards 5
4
A8
*/
//#include <Servo.h>
//int servoPin = -; //placeholder
//Servo Servo1; //placeholder

int medianreadFront = sonicA.getMedianDistance(5);
int medianreadRight = sonicB.getMedianDistance(5);

void setup() {
  Serial.begin(9600);
  car.begin(); //initialize the car using the encoders and the gyro
  sonicA.attach(45, 43);
  sonicB.attach(44, 42);
  //Servo1.attach(servoPin); //placeholder
}

int distanceLeft = 0;
int distanceRight = 0;
int distanceCenter = 0;

void loop() {
  car.setSpeed(40);
    firstPart();
    printDebug();
 }


void firstPart() {

if (medianreadFront >= 15)
{}
  //givendistance do nothing

  else
{

if (medianreadRight <= 15)
  {moveleft();}

if (medianreadRight <=15 && medianreadFront <=15)
  {moveback();}

}

}

void printDebug() {
  Serial.println();
}


//second part, arguably
 void moveleft() {
car.setAngle(90);
car.setSpeed(10):

}

  void moveback() {

    car.setSpeed(-10):

  }

   void moveright() {

   }




/*
//servo and measurments
void servo() {
  Servo1.write(45);
  delay(500);
  distanceLeft = sonicA.getMedianDistance();
  Servo1.write(90);
  distanceCenter =sonicA.getMedianDistance();
  Servo1.write(135);
  distanceLeft = sonicA.getMedianDistance();
}
*/


//stuff to be implemented, maybe(?)
/*
  int minusspeed = 100-sonicFR.getMedianDistance(3);
  if (medianreadFront < 5 && 0 < medianreadFront ) {
  car.setAngle(-45);
  car.setSpeed(getspeed-minusspeed);
 }
 else
 car.setSpeed(0);
}
*/
