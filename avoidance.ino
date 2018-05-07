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
  sonicFR.attach(TRIGGER_PIN_FR, ECHO_PIN_FR); //trigger pin, echo pin
  sonicBR.attach(TRIGGER_PIN_BR, ECHO_PIN_BR); //trigger pin, echo pin
  sonicB.attach(TRIGGER_PIN_B, ECHO_PIN_B); //trigger pin, echo pin
}


void loop() {
    debugPrint();
    testdone();
 }
void debugPrint() {
 // if (Serial.available()) {
    //Serial.print("Ultrasonic, FR: ");
    //Serial.println(sonicFR.getDistance());
    //Serial.print("Ultrasonic, BR: ");
    //Serial.println(sonicBR.getDistance());
    //Serial.print("Ultrasonic,  B: ");
    //Serial.println(sonicB .getDistance());
    //medianBack = sonicFR.getMedianDistance(30);
    medianBack = sonicFR.getDistance();
    Serial.print("Ultrasonic, FR: ");

    Serial.println(medianBack);
  //}
}



void testdone() {
  int lastread = 0;
  int getspeed = car.getSpeed();
  for (int i=0;i<5;i++) lastread = sonicFR.getDistance(); //take an example of data
  if (sonicFR.getMedianDistance(5) > lastread + lastread*0.5) //if reading now is much bigger than lastread, then scrap it
  {}
  else {
    int minusspeed = 100-sonicFR.getMedianDistance(3);
    if (medianreadFront < 5 && 0 < medianreadFront ) {
    car.setAngle(-45);
    car.setSpeed(getspeed-minusspeed);
   }
   else
   car.setSpeed(0);
  }
}
