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
  _checkAngle2

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


void inita() {

car.setSpeed(0);
fa = gyro.getAngularDisplacement();
changeState(_checkAngle);
Serial.println("f");
}



void check() {
  Serial.println("u");
car.setMotorSpeed(-50,50);
if (fa >= 90) {
if (gyro.getAngularDisplacement() <= fa-90)
{car.setSpeed(0);
changeState(_spin);}
}

else {
 int negativeread = fa-90;
 if (gyro.getAngularDisplacement() >200) {
 if (gyro.getAngularDisplacement() <= 360-(-negativeread))
 {car.setSpeed(0);
changeState(_spin);}
 }
}
}

void spin(){
  car.setSpeed(40);
  if ((readRight >= 30 || readRight == 0)  && (IRread >=10 || IRread == 0 )) {
    car.setSpeed(0);

 changeState(_forward);
  }
}


void forward() {
  car.setMotorSpeed(70,-70);
if (fa<269) {
if (gyro.getAngularDisplacement() <= fa+90)
{car.setSpeed(0);}
changeState(_spin2); }

  else {
    int negativeread = fa - 360;
    if (gyro.getAngularDisplacement()<200) {
   if (gyro.getAngularDisplacement() >= -(-negativeread))
      {car.setSpeed(0);
      changeState(_spin2);}
    }
  }
}
void spin2(){
  car.setSpeed(50);
  if ((readRight >= 30 || readRight == 0)  && (IRread >=5 || IRread == 0 )) {
    car.setSpeed(0);
  }
  changeState(_checkAngle2);
}


void check2() {
  Serial.println("u");
car.setMotorSpeed(-70,70);
if (fa >= 90) {
if (gyro.getAngularDisplacement() <= fa-90)
{car.setSpeed(0);
changeState(_spin);}
}

else {
 int negativeread = fa-90;
 if (gyro.getAngularDisplacement() >200) {
 if (gyro.getAngularDisplacement() <= 360-(-negativeread))
 {car.setSpeed(0);
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
  gyro.begin(22);
}

void loop() {
  IRread = IR.getMedianDistance(5);
  IRread = (IRread == 0) ? 70:IRread;
  IRread = (IRread >= 12) ? IRread-12:IRread;
  readRight = sonicB.getDistance();
  medianreadFront = sonicA.getMedianDistance(5);
  medianreadRight = sonicB.getMedianDistance(5);
  gyro.update();
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


  case _spin2: spin2(); break;

  case _forward:forward(); break;

  case _finish:finish(); break;
    }

}
