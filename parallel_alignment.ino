#include <Smartcar.h>

Car car;


int carSpeed = 50, carAngle = 75;
int direction = 1;

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
  car.begin();
  sonicFR.attach(TRIGGER_PIN_FR, ECHO_PIN_FR);
  sonicBR.attach(TRIGGER_PIN_BR, ECHO_PIN_BR);
  sonicB.attach(TRIGGER_PIN_B, ECHO_PIN_B);
}

void loop() {
  debugPrint();
  fun();
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

void (){
    
    int distanceFR = sonicFR.getDistance(),
        distanceBR = sonicBR.getDistance();
    
    if((distanceFR > 0 && distanceFR < 10) || (distanceBR > 0 && distanceBR < 10))  {
      if(car.getSpeed() != 0) {
        car.setSpeed(0);
       }
    }
    else{
       if(car.getSpeed() != 30) {
        car.setSpeed(30);
       }
       align1(distanceFR, distanceBR);
    }
}

void align(int distanceFR, int distanceBR) {
  
  if((distanceFR > 0 && distanceFR < 35) && (distanceBR > 0 && distanceBR < 35)){  
       if(distanceFR > distanceBR) {
            car.setAngle(45);
        }
       else if(distanceFR < distanceBR){
            car.setAngle(-45);
       }
        else{
        car.setAngle(0); 
        }
    } else{
      car.setAngle(0);
    }
}

