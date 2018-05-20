#include <Smartcar.h>
Car car;
Gyroscope gyro;

enum states{

  _idle,
  _start,
  _firstTurn,
  _firstGo,
  _secondTurn,
  _finish,
  _secondGoPT,
  _checkAngle2,
  _secondGo,
  _adjust,
  _thirdAdjust,
  _jesus,
  _thirdTurn,
  _secondAdjust

};
GP2Y0A21 IR;
SR04 sonicA;
SR04 sonicB;
SR04 sonicC;
int medianreadFront = 0;
int medianreadRight = 0;
int medianreadBack = 0;
int readRight = 0;
int readFront = 0;
int IRread;
unsigned int current;
char state = _idle;



// Front Sensor, fill in with correct pin please

const int TRIGGER_PIN_FR = 45;
const int ECHO_PIN_FR    = 43;
const int TRIGGER_PIN_RR = 44;
const int ECHO_PIN_RR    = 42;
const int TRIGGER_PIN_BACK = 5;
const int ECHO_PIN_BACK = 4;
const int IR_pin = A15;

//bool state = true;
int FirstMeasure;
bool delay1 = true;
int initialDegree;
int firstTurnDegree;
bool kys = true;
int turnSpeed = 50;
int adjustSpeed = 50;
int forwardSpeed = 50;

void inita() {

car.setSpeed(0);
FirstMeasure = gyro.getAngularDisplacement();
initialDegree=gyro.getAngularDisplacement();
changeState(_firstTurn);
}



void firstTurn() {

car.setMotorSpeed(-turnSpeed,turnSpeed);
if (initialDegree >= 90) {
  if (initialDegree==90) {
    if(gyro.getAngularDisplacement()<200) {
      if (gyro.getAngularDisplacement()>0){
          car.setSpeed(0);
          FirstMeasure = FirstMeasure-90;
          changeState(_firstAdjust);}
    }
  }



if (gyro.getAngularDisplacement() <= initialDegree-90)
{car.setSpeed(0);
FirstMeasure = FirstMeasure-90;
changeState(_firstAdjust);}
}


else {

 int negativeread = initialDegree-90;
 if (gyro.getAngularDisplacement() >200) {
 if (gyro.getAngularDisplacement() <= 360-(-negativeread))
 {car.setSpeed(0);
 FirstMeasure = 360-(-negativeread);
  changeState(_firstAdjust);
 }
 }
}
}


void firstAdjust() {
  if (FirstMeasure>gyro.getAngularDisplacement())
  {car.setMotorSpeed(turnSpeed,-turnSpeed);
  }
  if (FirstMeasure<gyro.getAngularDisplacement())
  {car.setMotorSpeed(-turnSpeed,turnSpeed);}
  if ( FirstMeasure == gyro.getAngularDisplacement() || FirstMeasure == gyro.getAngularDisplacement()+1 || FirstMeasure == gyro.getAngularDisplacement()-1 )
  {car.setSpeed(0);
  changeState(_firstGo);
  }

}
void firstGo(){
  car.setSpeed(forwardSpeed);
  if ((readRight >= 30 || readRight == 0)  && (IRread >=10 || IRread == 0 )) {
    car.setSpeed(0);
    changeState(_secondTurn);

  }

}


void secondTurn() {

car.setMotorSpeed(turnSpeed,-turnSpeed);
if (initialDegree<270)
{ FirstMeasure = initialDegree;}
else
{ FirstMeasure = initialDegree;}
/*
if (initialDegree<180)
{ initialDegree = initialDegree+180;}
else
{initialDegree = initialDegree-180;}
*/
if (initialDegree<=90) {
  if(gyro.getAngularDisplacement()<200)
  {
    if (gyro.getAngularDisplacement()>initialDegree) {
      car.setSpeed(0);
      changeState(_secondAdjust);
    }
  }
      }

  else {
  if (gyro.getAngularDisplacement()>FirstMeasure)
    { car.setSpeed(0);
      changeState(_secondAdjust);
      }

}
 }

 void secondAdjust() {

if (initialDegree>gyro.getAngularDisplacement())
  {car.setMotorSpeed(adjustSpeed,-adjustSpeed);
  }
  if (initialDegree<gyro.getAngularDisplacement())
  {car.setMotorSpeed(-adjustSpeed,adjustSpeed);}
  if ( initialDegree == gyro.getAngularDisplacement()||initialDegree == gyro.getAngularDisplacement()+1 || initialDegree == gyro.getAngularDisplacement()-1|| initialDegree == gyro.getAngularDisplacement()-2)
  {car.setSpeed(0);
  changeState(_secondGo);
  }

/*
    if (b>gyro.getAngularDisplacement())
  {car.setMotorSpeed(25,-25);
  }
  if (b<gyro.getAngularDisplacement())
  {car.setMotorSpeed(-25,25);}
  if ( b == gyro.getAngularDisplacement()|| b == gyro.getAngularDisplacement()+1 || b == gyro.getAngularDisplacement()-1)
  {car.setSpeed(0);
  //changeState(_secondGoPT);
  }
*/
 }
void secondGo() {
  if ((readRight >= 30 || readRight == 0)  && (IRread >=10 || IRread == 0 )) {
  car.setSpeed(forwardSpeed);
  }
else {changeState(_secondGoPT);}
}
void secondGoPT(){
        car.setSpeed(forwardSpeed);

  if ((readRight >= 30 || readRight == 0)  && (IRread >=10 || IRread == 0 )) {
    car.setSpeed(0);
    changeState(_thirdTurn);

}

  }




void thirdTurn() {

car.setMotorSpeed(turnSpeed,-turnSpeed);
if (initialDegree<270)
{ FirstMeasure = initialDegree+90;}
else
{ FirstMeasure = initialDegree+90-360;}
/*
if (initialDegree<180)
{ initialDegree = initialDegree+180;}
else
{initialDegree = initialDegree-180;}
*/
if (initialDegree<=90) {
  if(gyro.getAngularDisplacement()<200)
  {
    if (gyro.getAngularDisplacement()>FirstMeasure) {
      car.setSpeed(0);
      changeState(_thirdAdjust);
    }
  }
      }

  else {
  if (gyro.getAngularDisplacement()>FirstMeasure)
    { car.setSpeed(0);
      changeState(_thirdAdjust);
      }

}
}





 void thirdAdjust() {
  if (FirstMeasure>gyro.getAngularDisplacement())
  {car.setMotorSpeed(adjustSpeed,-adjustSpeed);
  }
  if (FirstMeasure<gyro.getAngularDisplacement())
  {car.setMotorSpeed(-adjustSpeed,adjustSpeed);}
  if ( FirstMeasure == gyro.getAngularDisplacement()||FirstMeasure == gyro.getAngularDisplacement()+1 || FirstMeasure == gyro.getAngularDisplacement()-1|| FirstMeasure == gyro.getAngularDisplacement()-2)
  {car.setSpeed(0);
  changeState(_jesus);
  }
 }




void changeState(char newState) {
  state = newState;

}

void christ() {
  car.setSpeed(forwardSpeed);
  if(readFront <= 10)
  {car.setSpeed(0);
  changeState(_finish);
  }
}


void finish() {
  car.setMotorSpeed(-turnSpeed,turnSpeed);
  if (FirstMeasure==90) {
    if(gyro.getAngularDisplacement()>200) {
    if (gyro.getAngularDisplacement()>initialDegree){
      car.setSpeed(0);
      FirstMeasure = FirstMeasure-90;
      changeState(_idle);}

    }
  }



if (gyro.getAngularDisplacement() <= initialDegree)
{car.setSpeed(0);

changeState(_idle);}
}


void debug() {
  Serial.println(IRread);
  Serial.println(initialDegree);
}


void takeRead() {
     FirstMeasure = gyro.getAngularDisplacement();
}





void setup() {
  // put your setup code here, to run once:

  // put your setup code here, to run once:
  gyro.attach();
  pinMode(A0, OUTPUT);
  Serial.begin(9600);
  Serial3.begin(9600);
  car.begin(); //initialize the car using the encoders and the gyro
  sonicA.attach(45, 43);
  sonicB.attach(44, 42);
  sonicC.attach(5, 4);
  IR.attach(A15);
  gyro.begin(16);
}

void loop() {
  gyro.update();
  IRread = IR.getMedianDistance(5);
  IRread = (IRread == 0) ? 70:IRread;
  IRread = (IRread >= 12) ? IRread-12:IRread;
  readRight = sonicB.getDistance();
  readFront = sonicA.getDistance();
  medianreadFront = sonicA.getMedianDistance(5);
  medianreadRight = sonicB.getMedianDistance(5);

  debug();

  if (kys && state==_idle && (medianreadFront<=20 && medianreadFront >0) && (medianreadRight<= 8 && medianreadRight > 0)) {
     kys=false;
   changeState(_start);



  }
    switch (state) {
  case _start: inita(); break;

  case _firstTurn: firstTurn(); break;

  case _thirdTurn: thirdTurn(); break;

  case _firstGo: firstGo(); break;

  case _firstAdjust: firstAdjust(); break;

  case _secondGoPT: secondGoPT(); break;

  case _secondGo: secondGo(); break;

  case _secondTurn:secondTurn(); break;

  case _thirdAdjust:thirdAdjust();break;

  case _finish:finish(); break;

  case _jesus:christ(); break;
  case _secondAdjust:secondAdjust(); break;
    }

}
