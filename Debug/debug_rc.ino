#include <Smartcar.h>

Car car;

const int fSpeed = 70; //70% of the full speed forward
const int bSpeed = -70; //70% of the full speed backward
const int lDegrees = -75; //degrees to turn left
const int rDegrees = 75; //degrees to turn right
int carSpeed = 50;
int carAngle = 75;

void setup() {
  Serial3.begin(9600);
  car.begin(); //initialize the car using the encoders and the gyro
}

void loop() {
  handleInput();
}

void handleInput() { //handle serial input if there is any
  if (Serial3.available()) {
    char input = Serial3.read(); //read everything that has been received so far and log down the last entry
      switch (input) {
        case 'l': //rotate counter-clockwise going forward
          car.setSpeed(carSpeed);
          car.setAngle(lDegrees);
          break;
        case 'r': //turn clock-wise
          car.setSpeed(carSpeed);
          car.setAngle(rDegrees);
          break;
        case 'f': //go ahead
          car.setSpeed(carSpeed);
          car.setAngle(0);
          break;
        case 'b': //go back
          car.setSpeed(-carSpeed);
          car.setAngle(0);
          break;
        case 'u': //increase spead by 10
          if (carSpeed < 100) {
            carSpeed += 5;
          }
          break;
        case 'd':
          if (carSpeed > 0) {
            carSpeed -= 5;
          }
          break;
        case 'i':
          if (carAngle < 90) {
            carAngle += 5;
          }
          break;
        case 'k':
          if (carAngle > 40) {
            carAngle -= 5;
          }
          break;
        default: //if you receive something that you don't know, just stop
          car.setSpeed(0);
          car.setAngle(0);
      }
    } else {
      delay(150);
      car.setSpeed(0);
      car.setAngle(0);
    }
}
