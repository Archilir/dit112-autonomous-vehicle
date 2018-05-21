void loop() {
  // put your main code here, to run repeatedly:
bugster();
}
void bugster() {
medianreadFront = sonicA.getMedianDistance(5);
medianreadRight = sonicB.getMedianDistance(5);
medianreadBack = sonicC.getMedianDistance(5);
  if (medianreadFront >= 20)
{}
else

   {
    moveleft();

}
}


void moveleft() {
  if ( (medianreadRight <=8 ) && ( medianreadFront>0 ))
  {

  car.setAngle(-90);
  car.setSpeed(50);
  }

  else {car.setSpeed(0);
  car.setAngle(0);}
   }

/*
//if(medianreadRight <=10 && medianreadRight>0)
//  { car.setSpeed(50);}

//    else car.setSpeed(0);

    }
   }


  }
void initialbump() {


    if ((medianreadFront<10 && medianreadFront>0) && (medianreadRight<20 && medianreadRight >0) )
    { car.setMotorSpeed(-50,50);}
    else
    car.setSpeed(0);


    /*
    car.setSpeed(30);
    if (medianreadRight<8)
    { car.setMotorSpeed(-50,50);}
    else car.setSpeed(0);

}

void initialadjustment() {
    car.setSpeed(0);
    car.setMotorSpeed(-50,50);
   delay(1000);
    car.setSpeed(0);
}

/*
 if (medianreadFront >= 15)
{}

else

   {
    //maybe if or while

if ( (medianreadRight <=15 && medianreadRight>0 ) && ( medianreadFront>0 ))
  {
    car.setSpeed(0);
    car.setMotorSpeed(-50,50);
  }

  else car.setSpeed(40);

    }
    */
