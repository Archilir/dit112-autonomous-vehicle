#include <StackArray.h>
#include <Smartcar.h>

Car car;

int carSpeed = 50, carAngle = 75;
#include <Smartcar.h>

SR04 sonicFR, sonicBR, sonicB;
// Front - Right ultrasonic sensor
const int TRIGGER_PIN_FR = 5;
const int ECHO_PIN_FR    = 4;

// Back - Right ultrasonic sensor 
const int TRIGGER_PIN_BR = 6;
const int ECHO_PIN_BR    = 7;

// Back ultrasonic sensor
const int TRIGGER_PIN_B = 44;
const int ECHO_PIN_B    = 42;

Odometer encoderLeft(188), encoderRight(188);

const int encoderLeftPin = 2;
const int encoderRightPin = 3;

int encCheck = 0;

bool park = false;

enum drive: byte 
{ 
  MOVE, BRAKE
};



void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  encoderLeft.attach(encoderLeftPin);
  encoderRight.attach(encoderRightPin);
  car.begin(encoderLeft, encoderRight); //initialize the car using the encoders and the gyro
  //car.enableCruiseControl(); //using default PID values
  sonicB.attach(TRIGGER_PIN_FR, ECHO_PIN_FR); //trigger pin, echo pin
  sonicBR.attach(TRIGGER_PIN_BR, ECHO_PIN_BR); //trigger pin, echo pin
  sonicFR.attach(TRIGGER_PIN_B, ECHO_PIN_B); //trigger pin, echo pin
  
}

void loop() {
  remoteControl();
  parking();
  //debugSensors();
}

// PARALLEL PARKING

void debugSensors() {
  String buff = "Ultrasonic, FR, BR, B: ";
  String spac = " ";
  buff = buff + sonicFR.getMedianDistance() + spac + sonicBR.getMedianDistance() + spac + sonicB.getMedianDistance();
  Serial.println(buff);
}

const int borderLimit = 20;
const int viableDistance = 50;

void parking() {
  if (park) {
    int startDistance = encoderLeft.getDistance(); // starting distance point relative to parking algorithm's initialization
    int lastSensor = sonicFR.getMedianDistance(), currentSensor = 0;
    int lastDistance = 0;
    bool gap = false;
    StackArray<int> distanceStack;
    defaultDrive(MOVE);

    do {
      rcParkingOverride();
      currentSensor = sonicFR.getMedianDistance();
      
      // Step 1: Detecting obstacle / difference

      if (currentSensor > 0 & currentSensor < 20) {
        gap = false;
        int currentDistance = encoderLeft.getDistance();
        lastDistance = currentDistance - startDistance;
        startDistance = currentDistance;
      } else if (currentSensor == 0 || currentSensor > 15) {
        gap = true;
        int currentDistance = encoderLeft.getDistance();
        lastDistance = currentDistance - startDistance;
        startDistance = currentDistance;
      }

      if (!gap & lastDistance >= viableDistance)
        park = false;
        
      lastSensor = currentSensor;
      
    } while (park);   

    
    defaultDrive(BRAKE);  
  }

}

int distanceCal(int lastSensor) {
  lastSensor = lastSensor - 5;
  if (lastSensor <= 0)
    return 1;
  return lastSensor;
}

void rcParkingOverride() {
  if (Serial3.available() && Serial3.read() == 'p') 
    parkingSwitch();
}

void parkingSwitch() {
  park = park ? false : true;
}


// FRAMEWORK

void defaultDrive(byte drive) {
  switch (drive) {
    case MOVE:
      car.setSpeed(100);
      car.setAngle(0);
      break;
    case BRAKE:
      car.stop();
      break;
    default:
      break;
  }
}

void remoteControl() {
  if (Serial3.available()) {
    switch (Serial3.read()) {
      case 'p': 
        parkingSwitch();
        break;
      case 'g':
        encCheck = encoderLeft.getDistance() + 100;
        defaultDrive(MOVE);
        while (encoderLeft.getDistance() < encCheck) {
          Serial.println(encoderLeft.getDistance());
        }
        defaultDrive(BRAKE);
        break;
        //car.go(100);
        //car.updateMotors();
      default:
        break;
    }
  } 
}

