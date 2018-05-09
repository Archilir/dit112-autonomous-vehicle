#include <Smartcar.h>

Car car;

#include <Smartcar.h>

SR04 sonicA;
// Front Sensor, fill in with correct pin please
const int TRIGGER_PIN_FR = --;
const int ECHO_PIN_FR    = --;


#include <Servo.h>
int servoPin = -; //placeholder
Servo Servo1; //placeholder

int medianreadFront = sonicFR.getMedianDistance(5);

void setup() {
  Serial.begin(9600);
  car.begin(); //initialize the car using the encoders and the gyro
  sonicA.attach(TRIGGER_PIN_FR, ECHO_PIN_FR); //trigger pin, echo pin
  Servo1.attach(servoPin); //placeholder
}

int distanceLeft = 0;
int distanceRight = 0;
int distanceCenter = 0;
void loop() {
    servo();
    firstPart();
 }


void firstPart() {
if (distanceCenter >= 15)
{} //givendistance do nothing

  else
{

if (distanceLeft > distanceRight)
  {moveleft()}

if (distanceRight > distanceLeft)
  {moveright();}

if (distanceLeft <= 10 && distanceCenter <= 10 || distanceRight <= 10 && distanceCenter <= 10)
  {moveback();}

}

}


//second part, arguably
 void moveleft() {
   car.setAngle(car.getAngle() - 10)
 }

  void moveback() {
    car.setSpeed(-50);
    car.setAngle(0);
  }

   void moveright() {
     car.setAngle(car.getAngle() + 10);
   }

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



//stuff to be implemented, maybe(?)
  int minusspeed = 100-sonicFR.getMedianDistance(3);
  if (medianreadFront < 5 && 0 < medianreadFront ) {
  car.setAngle(-45);
  car.setSpeed(getspeed-minusspeed);
 }
 else
 car.setSpeed(0);
}
