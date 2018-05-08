#include <Smartcar.h>

Odometer encoderLeft, encoderRight;
Gyroscope gyro(22);
Car car;

const int encoderLeftPin  = 2,
          encoderRightPin = 3;
char input;

int carSpeed = 0;




void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  encoderLeft.attach(encoderLeftPin);
  encoderRight.attach(encoderRightPin);
  gyro.attach();
  delay(1500);
  gyro.begin(60);
  encoderLeft.begin();
  encoderRight.begin();
  car.begin(encoderLeft, encoderRight, gyro); //initialize the car using the encoders
}

void loop() {
  handleInput();
}

void handleInput() {
  if (Serial3.available()) {
    input = Serial3.read();
    Serial.print(millis());
    Serial.print('\t');
    
    Serial.println(input);
  }
}
