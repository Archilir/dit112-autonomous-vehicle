#include <Smartcar.h>

Car car;

int carSpeed = 50;
int carAngle = 80;

void setup() {
  Serial.begin(9600);
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
        case 'w': //go ahead
          car.setSpeed(carSpeed);
          car.setAngle(0);
          break;
        case 's': //go back
          car.setSpeed(-carSpeed);
          car.setAngle(0);
          break;
        case 'a': //rotate counter-clockwise going forward
          car.setSpeed(carSpeed);
          car.setAngle(-carAngle);
          break;
        case 'd': //turn clock-wise
          car.setSpeed(carSpeed);
          car.setAngle(carAngle);
          break;
        case 'i': //increase speed by 10
          if (carSpeed < 100) {
            carSpeed = carSpeed + 10;
          }
          break;
        case 'k':
          if (carSpeed > 0) {
            carSpeed = carSpeed - 10;
          }
          break;
        case 'l':
          if (carAngle < 90) {
            carAngle = carAngle + 10;
          }
          break;
        case 'j':
          if (carAngle > 0) {
            carAngle = carAngle - 10;
          }
          break;
        default: //if you receive something that you don't know, just stop
          car.setSpeed(0);
          car.setAngle(0);
      }
          Serial.print("Speed: ");
          Serial.println(carSpeed);
          Serial.print("Angle: ");
          Serial.println(carAngle);
    } else {
      delay(150);
      car.setSpeed(0);
      car.setAngle(0);
    }
}
