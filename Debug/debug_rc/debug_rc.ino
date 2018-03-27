#include <Smartcar.h>

Car car;

int carSpeed = 50, carAngle = 75;
int direction = 1;

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

bool deadlockState = false;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  car.begin(); //initialize the car using the encoders and the gyro
  sonicFR.attach(TRIGGER_PIN_FR, ECHO_PIN_FR); //trigger pin, echo pin
  sonicBR.attach(TRIGGER_PIN_BR, ECHO_PIN_BR); //trigger pin, echo pin
  sonicB.attach(TRIGGER_PIN_B, ECHO_PIN_B); //trigger pin, echo pin
}

void loop() {
  debugPrint();
  taskmaster();
}

// Printing out ultrasonic sensor readings to the Serial as long as it's attached
void debugPrint() {
  if (Serial.available()) {
    Serial.print("Ultrasonic, FR: ");
    Serial.println(sonicFR.getDistance());
    Serial.print("Ultrasonic, BR: ");
    Serial.println(sonicBR.getDistance());
    Serial.print("Ultrasonic,  B: ");
    Serial.println(sonicB .getDistance());
  }
}

// Main switch between the deadlock and drive options
void taskmaster() { 
  if (Serial3.available()) {
    if (deadlockState && 
       ((sonicFR.getDistance() >  0 && sonicFR.getDistance() < 15) ||  
        (sonicBR.getDistance() >  0 && sonicBR.getDistance() < 15) ||
        (sonicB .getDistance() >  0 && sonicB .getDistance() < 15))) {

        deadlock( Serial3.read() );
    }
    else {
        manualDrive( Serial3.read() );
    }
  } else {
    delay(150);
    car.setSpeed(0);
    car.setAngle(0);
  } 
}

// Driving state block
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

// Deadlock
void deadlock(char input) {
  if (input == 'n') {
      deadlockState = (deadlockState) ? false : true;
  }
  if (deadlockState) {
    car.setAngle(0);
    car.setSpeed(0); 
  }
}

