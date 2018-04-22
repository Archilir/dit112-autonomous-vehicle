#include <Smartcar.h>


// Car instance
Car car; 

// Variables used to update the speed of the wheels when controling the car in the console
int speedLeft;
int speedRight;

// A variable to store the direction inputed in the console
String directionAndSpeed;

//Front UltraSound sensor
SR04 FrontUSSensor;
//const int TRIGGER_PIN_FRONT = ?;
//const int ECHO_PIN_FRONT = ?;

//Back UltraSound sensor
SR04 BackUSSensor;
const int TRIGGER_PIN_BACK = 5;
const int ECHO_PIN_BACK = 4;

// A variable used for the switch case for the obstacle detection
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

  //int frontDistance = FrontUSSensor.getDistance();
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
    
     case 'w':
     
    // TODO: add obstacle avoidance for the front sensor
    
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

    // TODO: add obstacle avoidance for the front sensor

        car.setMotorSpeed(speedLeft, speedRight);

      break;

    case 'e':

    // TODO: add obstacle avoidance for the front sensor

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

    // Move Forward

    case 'w' :

      speedLeft = derive();
      speedRight = derive();
      switchVar = 'w';
      car.setMotorSpeed(derive(), derive());
      break;

    // Turn in place to the left

    case 'a' :

      switchVar = 'a';     
      car.setMotorSpeed(-derive(), derive());
      break;

    // Move Backwards 

    case 's' :
    
      speedLeft = -derive();
      speedRight = -derive();
      switchVar = 's';
      car.setMotorSpeed(-derive(), -derive());
      break;

    // Turn in place to the right

    case 'd' :

      switchVar = 'd';
      car.setMotorSpeed(derive(), -derive());
      
      break;

    // Move Forward diagonally to the left

    case 'q' :

      speedLeft = derive() / 2;
      speedRight = derive();
      switchVar = 'q';
      car.setMotorSpeed(derive() / 2, derive());
      break;

    // Move Forward diagonally to the right

    case 'e' : 

      speedLeft = derive();
      speedRight = derive() / 2;
      switchVar = 'e';
      car.setMotorSpeed(derive(), derive() / 2);
      break;

    // Move Backwards diagonally to the left

    case 'z' :
    
      speedLeft = -derive() / 2;
      speedRight = -derive();
      switchVar = 'z';
      car.setMotorSpeed(-derive() / 2, -derive());
      break;

    // // Move Backwards diagonally to the right

    case 'c' :


      speedLeft = -derive();
      speedRight = -derive() / 2;
      switchVar = 'c';
      car.setMotorSpeed(-derive(), -derive() / 2);
      break;

    // stop the car

    case 'x' :

      switchVar = 'w';
      car.setMotorSpeed(0, 0);
      break;

    // default case

    default :
    Serial.println("Wrong command, try another command");
      break;
  }
  
  directionAndSpeed = "";
}

// a method to extract the inputed speed

int derive() {
  int speed = directionAndSpeed.substring(1, 3).toInt();
  return speed;
}





