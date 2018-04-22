#include <Smartcar.h>


// Car instance
Car car; 

int speedLeft;
int speedRight;

// A Variable to store the direction inputed in the console
String directionAndSpeed;

//Front UltraSound sensor
//const int TRIGGER_PIN_FRONT = ?;
//const int ECHO_PIN_FRONT = ?;

//Back UltraSound sensor
const int TRIGGER_PIN_BACK = 5;
const int ECHO_PIN_BACK = 4;


SR04 FrontUSSensor;
SR04 BackUSSensor;

char switchVar;


void setup() {
 Serial.begin(9600);
 Serial3.begin(9600);
 car.begin();
 //FrontUSSensor.attach(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
  BackUSSensor.attach(TRIGGER_PIN_BACK, ECHO_PIN_BACK);

  Serial.println("Use the following to Control the car");
  Serial.println("                 ⇧                  ");
  Serial.println(" ↖               w               ↗  ");
  Serial.println("  q                               e  ");
  Serial.println("                                     ");
  Serial.println("                                     ");
  Serial.println("   ↺ a           x            d  ↻  ");
  Serial.println("                                     ");
  Serial.println("                                     ");
  Serial.println("  z                               c  ");
  Serial.println(" ↙                s                ↘ ");
  Serial.println("                  ⇩                  ");

}
void loop() {

  int frontDistance = FrontUSSensor.getDistance();
  int backDistance = BackUSSensor.getDistance(); 

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

  switch (switchVar) {
 
        car.setMotorSpeed(speedLeft, speedRight);

      break;

    case 's':

      if (backDistance > 2 && backDistance < 20) {
 
        car.setMotorSpeed(0, 0);

      } else {
 
        car.setMotorSpeed(speedLeft, speedRight);

      }

      break;

    case 'q':

        car.setMotorSpeed(speedLeft, speedRight);

      break;

    case 'e':

        car.setMotorSpeed(speedLeft, speedRight);

      break;

    case 'z':

      if (backDistance > 2 && backDistance < 20) {

        car.setMotorSpeed(0, 0);


      } else {
  
        car.setMotorSpeed(speedLeft, speedRight);

      }

      break;

    case 'c':
      if (backDistance > 2 && backDistance < 20) {

        car.setMotorSpeed(0, 0);


      } else {
  
        car.setMotorSpeed(speedLeft, speedRight);

      }

      break;
  }


  char direction = directionAndSpeed.charAt(0);


  switch (direction) {

    case 'w' :

      speedLeft = derive();
      speedRight = derive();
      switchVar = 'w';
      car.setMotorSpeed(derive(), derive());
      break;

    case 'a' :

      switchVar = 'a';     
      car.setMotorSpeed(-derive(), derive());
      break;

    case 's' :
    
      speedLeft = -derive();
      speedRight = -derive();
      switchVar = 's';
      car.setMotorSpeed(-derive(), -derive());
      break;

    case 'd' :

      switchVar = 'd';
      car.setMotorSpeed(derive(), -derive());
      
      break;

    case 'q' :

      speedLeft = derive() / 2;
      speedRight = derive();
      switchVar = 'q';
      car.setMotorSpeed(derive() / 2, derive());
      break;

    case 'e' : 

      speedLeft = derive();
      speedRight = derive() / 2;
      switchVar = 'e';
      car.setMotorSpeed(derive(), derive() / 2);
      break;

    case 'z' :
    
      speedLeft = -derive() / 2;
      speedRight = -derive();
      switchVar = 'z';
      car.setMotorSpeed(-derive() / 2, -derive());
      break;

    case 'c' :


      speedLeft = -derive();
      speedRight = -derive() / 2;
      switchVar = 'c';
      car.setMotorSpeed(-derive(), -derive() / 2);
      break;

    case 'x' :

      switchVar = 'w';
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





