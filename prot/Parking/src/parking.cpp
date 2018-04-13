#include <Smartcar.h>
/* * * * * * * * * * * * * * * * * *
 *  This is the last version we used to
 *  meme Oliver, so it should work decently.
 *  Commented code is statements from
 *  previous versions of this,
 *  left in just in case the parking team needs
 *  some inspiration.
 * * * * * * * * * * * * * * * * * */
Car car;
SR04 uSoundNW;
SR04 uSoundSW;
SR04 uSoundS;
const int TRIGGER_PIN1 = 5; //D6
const int ECHO_PIN1 = 4; //D7

const int TRIGGER_PIN2 = 6;
const int ECHO_PIN2 = 7;

const int TRIGGER_PIN3 = 44;
const int ECHO_PIN3 = 42;

bool parked = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  car.begin();
  uSoundNW.attach(TRIGGER_PIN1, ECHO_PIN1);
  uSoundSW.attach(TRIGGER_PIN2, ECHO_PIN2);
  uSoundS.attach(TRIGGER_PIN3, ECHO_PIN3);
  car.setSpeed(40);
}

void park()
{
     /* car.setSpeed(70); //This should be replaced by a distance value when we get cruise control working
      delay(800);
      car.stop(); //initial forward motion*/
      delay(400);
      car.setAngle(75);
      car.setSpeed(-45);//first turn

      if(uSoundS.getDistance()>0 &&
         uSoundS.getDistance()<15)
         {
          car.stop();
          delay(150);
          car.setAngle(45);
          car.setSpeed(40);
          delay(200);
          if(uSoundS.getDistance()>0 &&
             uSoundS.getDistance()<12)
             {
              car.stop();
              car.setAngle(0);
              car.setSpeed(40);
              delay(200);
             }
         }
      /*delay(400);
      car.setAngle(0); //straighten after first turn
      delay(400);
      //car.stop();
      //delay(800);
      car.setAngle(-70); //second turn
      car.setSpeed(-45);
      delay(350);
      car.setAngle(0);
      delay(350);
      car.stop();
      delay(800);
      car.setAngle(35); //adjust
      car.setSpeed(70);
      delay(500);
      car.stop();*/
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(uSoundNW.getDistance());
    Serial.println(uSoundSW.getDistance());
      Serial.println(uSoundS.getDistance());


  if((uSoundNW.getDistance()>0 && uSoundNW.getDistance()<12) &&
     (uSoundSW.getDistance()>0 && uSoundSW.getDistance()<12) &&
     (uSoundNW.getDistance() == uSoundSW.getDistance()) && !parked)
  {
    car.stop();
    parked=true;
    park();
  }
}
