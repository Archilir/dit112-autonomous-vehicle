#include <Smartcar.h>
Car car;
Gyroscope gyro;

enum states{

  _idle,
  _start,
  _checkAngle,
  _spin,
  _forward,
  _finish,
  _spin2,
  _checkAngle2,
  _adjust,
  _measure,
  _adjust2
};
GP2Y0A21 IR;
SR04 sonicA;
SR04 sonicB;
SR04 sonicC;
int medianreadFront = 0;
int medianreadRight = 0;
int medianreadBack = 0;
int readRight = 0;
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
int fa;
int fb;
int initialDegree;
int b;

void inita() {

car.setSpeed(0);
fa = gyro.getAngularDisplacement();
changeState(_checkAngle);
Serial.println("f");
}



void check() {
  Serial.println("u");
  initialDegree= gyro.getAngularDisplacement();
car.setMotorSpeed(-30,30);
if (fa >= 90) {
/*
  if (fa==90) {
    if(gyro.getAngularDisplacement()>200) {
    if (gyro.getAngularDisplacement()>fa-90){
      car.setSpeed(0);
      fa = fa-90;
      changeState(_adjust);}

    }
  }
  */


if (gyro.getAngularDisplacement() <= fa-90)
{car.setSpeed(0);
fa = fa-90;
changeState(_adjust);}
}


else {
 int negativeread = fa-90;
 if (gyro.getAngularDisplacement() >200) {
 if (gyro.getAngularDisplacement() <= 360-(-negativeread))
 {car.setSpeed(0);
 fa = 360-(-negativeread);
  changeState(_adjust);
 }
 }
}
}
}

void adjust() {
  if (fa>gyro.getAngularDisplacement())
  {car.setMotorSpeed(20,-20);
  }
  if (fa<gyro.getAngularDisplacement())
  {car.setMotorSpeed(-20,20);}
  if ( fa == gyro.getAngularDisplacement()||fa == gyro.getAngularDisplacement()+1 || fa == gyro.getAngularDisplacement()-1||fa == gyro.getAngularDisplacement()+2 || fa == gyro.getAngularDisplacement()-2)
  {car.setSpeed(0);
  changeState(_spin);
  }

}
void spin(){
  car.setSpeed(40);
  if ((readRight >= 30 || readRight == 0)  && (IRread >=10 || IRread == 0 )) {
    car.setSpeed(0);
    changeState(_measure);

  }

}

void takeMeasure2(){
    fb = gyro.getAngularDisplacement();
    changeState(_forward);

}

void forward() {
car.setMotorSpeed(20,-20);

if (initialDegree<=90) {
  if(gyro.getAngularDisplacement()<200)
  {
    if (gyro.getAngularDisplacement()>initialDegree) {
      car.setSpeed(0);
      changeState(_adjust2);
    }
  }
      }

  else if {
  if (gyro.getAngularDisplacement()<initialDegree)
    { car.setSpeed(0);
      changeState(_adjust2);}

}
 }

 void adjust2() {

    if (b>gyro.getAngularDisplacement())
  {car.setMotorSpeed(20,-20);
  }
  if (b<gyro.getAngularDisplacement())
  {car.setMotorSpeed(-20,20);}
  if ( b == gyro.getAngularDisplacement()||b == gyro.getAngularDisplacement()+1 || b == gyro.getAngularDisplacement()-1)
  {car.setSpeed(0);
  changeState(_spin2);
  }

 }

void spin2(){
        car.setSpeed(0);

  bool dood = false;
  if (dood == false && (readRight >= 30 || readRight == 0)  && (IRread >=5 || IRread == 0 )) {
  car.setSpeed(50);
  dood = true;}
  if (dood= true) {
  if ((readRight >= 30 || readRight == 0)  && (IRread >=5 || IRread == 0 )) {
    car.setSpeed(0);
    fa = getAngularDisplacement();
    changeState(_checkAngle2);

  }
  }

}


void check2() {
    Serial.println("u");
    initialDegree2= gyro.getAngularDisplacement();
  car.setMotorSpeed(-30,30);
  if (fa >= 90) {
  /*
    if (fa==90) {
      if(gyro.getAngularDisplacement()>200) {
      if (gyro.getAngularDisplacement()>fa-90){
        car.setSpeed(0);
        fa = fa-90;
        changeState(_adjust);}

      }
    }
    */


  if (gyro.getAngularDisplacement() <= fa-90)
  {car.setSpeed(0);
  fa = fa-90;
}
  }


  else {
   int negativeread = fa-90;
   if (gyro.getAngularDisplacement() >200) {
   if (gyro.getAngularDisplacement() <= 360-(-negativeread))
   {car.setSpeed(0);
   fa = 360-(-negativeread);

   }
   }
  }
  }
  }
}



void changeState(char newState) {
  state = newState;

}

void finish() {
  changeState(_idle);
}


void debug() {
  Serial.println(IRread);
  Serial.println(initialDegree);
}


void takeRead() {
     fa = gyro.getAngularDisplacement();
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
  medianreadFront = sonicA.getMedianDistance(5);
  medianreadRight = sonicB.getMedianDistance(5);

    Serial.println("d");
  debug();

  if ( state==_idle && (medianreadFront<=15 && medianreadFront >0) && (medianreadRight<= 8 && medianreadRight > 0)) {
     Serial.println("y");
   changeState(_start);

  }
    switch (state) {
  case _start: inita(); break;

  case _checkAngle: check(); break;

  case _checkAngle2: check2(); break;

  case _spin: spin(); break;

  case _adjust: adjust(); break;

  case _spin2: spin2(); break;

  case _forward:forward(); break;

  case _finish:finish(); break;

  case _measure:takeMeasure2(); break;
  case _adjust2:adjust2(); break;
    }

}
