#include <Smartcar.h>


// Car instance
Car car; 

int speedLeft;
int speedRight;

// A Variable to store the direction inputed in the console
String directionAndSpeed;


void setup() {
 Serial.begin(9600);
 Serial3.begin(9600);
 car.begin();

}
void loop() {


if (Serial.available() > 0) {
    while (directionAndSpeed.length() < 1) {
      char input = Serial.read();
      // Stopping case
      if ( input == 'x') {
        directionAndSpeed = String(input) + "00";
      }
      else {
        // set default speed to 60
        directionAndSpeed = String(input) + "60";
      }
    }
  }


  char direction = directionAndSpeed.charAt(0);


  switch (direction) {

    case 'w' :

      speedLeft = derive();
      speedRight = derive();
      car.setMotorSpeed(derive(), derive());
      break;

    case 'a' :
    
      car.setMotorSpeed(-derive(), derive());
      break;

    case 's' :
    
      speedLeft = -derive();
      speedRight = -derive();
      car.setMotorSpeed(-derive(), -derive());
      break;

    case 'd' :

      car.setMotorSpeed(derive(), -derive());
      
      break;

    case 'q' :

      speedLeft = derive() / 2;
      speedRight = derive();
      car.setMotorSpeed(derive() / 2, derive());
      break;

    case 'e' : 


      speedLeft = derive();
      speedRight = derive() / 2;
      car.setMotorSpeed(derive(), derive() / 2);
      break;

    case 'z' :

      speedLeft = -derive() / 2;
      speedRight = -derive();
      car.setMotorSpeed(-derive() / 2, -derive());
      break;

    case 'c' :


      speedLeft = -derive();
      speedRight = -derive() / 2;
      car.setMotorSpeed(-derive(), -derive() / 2);
      break;

    case 'x' :

      car.setMotorSpeed(0, 0);
      break;


    default :
      break;
  }
  
  directionAndSpeed = "";
}

int derive() {
  int speed = directionAndSpeed.substring(1, 3).toInt();
  return speed;
}





