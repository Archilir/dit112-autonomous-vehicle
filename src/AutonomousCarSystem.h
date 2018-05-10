#ifndef AutonomousCarSystem_h
#define AutonomousCarSystem_h
#include <Smartcar.h>

class Sensors
{
  public:
    void begin(Car*);
    void update();
    void updateSensors();

    unsigned int  getDistanceFR();
    unsigned int  getDistanceBR();
    unsigned int  getDistanceBB();
    unsigned int  getAngularDisplacement();
    unsigned int  getUnsyncAngularDisplacement();
    unsigned long getOdometerLeftDistance();
    unsigned long getOdometerRightDistance();
    unsigned long getOdometerAvgDistance();

    void enableMonitor();
    void disableMonitor();
    void resetMonitor();
    bool isMonitoring();
    bool isSectorViable();
    bool isClearSector();
    void monitor();
    void debug();

  private:
    Car *car;
    SR04 sonicFR, sonicBR, sonicBB;
    Odometer  odometerLeft  = Odometer(188),
              odometerRight = Odometer(188);
    Gyroscope gyro          = Gyroscope(22);

    unsigned int   distanceFR,
                   distanceBR,
                   distanceBB,
                   gyroAngle;

    unsigned long  distanceL,
                   distanceR,
                   updateTimer,
                   sectorStart,
                   sectorEnd;

    const char     _TRIGGER_PIN_FR = 44,
                   _TRIGGER_PIN_BR =  6,
                   _TRIGGER_PIN_BB =  5,
                   _ECHO_PIN_FR    = 42,
                   _ECHO_PIN_BR    =  7,
                   _ECHO_PIN_BB    =  4,
                   _ODOMETER_PIN_L =  2,
                   _ODOMETER_PIN_R =  3;

    bool monitoring = false;
};


class Driver
{
  public:
    void begin(Car*, Sensors*);
    void update();
    void stop();

    void enableAutonomy();
    void disableAutonomy();
    bool isAutonomous();

    void setSpeed(int);
    void setAngle(int);
    int  getSpeed();
    int  getAngle();

    void drive(int, int);
    void steer(int);
    void drive(int);

    void driveForward();
    void driveBackward();
    void driveLeft();
    void driveRight();
    void driveForwardLeft();
    void driveBackwardLeft();
    void driveForwardRight();
    void driveBackwardRight();

    void enableTrackingCourse();
    void disableTrackingCourse();
    bool isTrackingCourse();
    void trackCourse();
    void setCourse(int);

    void enableDriftCorrection();
    void disableDriftCorrection();
    bool isDriftCorrecting();
    void driftCorrection(int, int);

  private:
    Car *car;
    Sensors *sensors;

    int speedValue  = 0,
        courseValue = 0,
        angleValue  = 0;

    bool autonomous      = false,
         correctingDrift = false,
         trackingCourse  = false;

    void steer();
    void drive();
    void boost();
};


class Parking
{
  public:
    void begin(Driver*, Sensors*);
    void start();
    void stop();
    void monitor();
    int  getShortestDisplacement();
    void reverseParking();
  private:
    Driver *driver;
    Sensors *sensors;

    unsigned int previousFront,
                 previousBack;

    bool parking     = false,
         seeking     = false,
         maneuvering = false,
         positioning = false,
         isReverseParking = false;

    bool isViable(int);
    unsigned int parkingAlignment;
    bool isPositioned();
    int getNewDisplacement(int);
  /*  Parking();
    enum States { _OFF, _PARALLEL };
    void begin(Driver*, Sensors*);
    bool start(char);
    void stop();
    void monitor();
    bool isParking();
  private:
    bool targetFound = false;
    Driver *driver;
    Sensors *sensors;
    byte parkingState = _OFF;
    bool isReverseParking;
    int initialDisplacement;
    int previousFront;
    int previousBack;
    void parallel();
    int getShortestDisplacement();
    void reverseParking();*/
};

class RemoteControl
{
  public:
    void begin(Driver*, Parking*);
    void listen();
  private:
    Driver  *driver;
    Parking *parking;
    char input;
    enum {
      _FORWARD   = 'F',
      _BACK      = 'B',
      _LEFT      = 'L',
      _RIGHT     = 'R',
      _STOP      = 'S',
      _F_LEFT    = 'G',
      _F_RIGHT   = 'I',
      _B_LEFT    = 'H',
      _B_RIGHT   = 'J',
      _SPEED_0   = '0',
      _SPEED_10  = '1',
      _SPEED_20  = '2',
      _SPEED_30  = '3',
      _SPEED_40  = '4',
      _SPEED_50  = '5',
      _SPEED_60  = '6',
      _SPEED_70  = '7',
      _SPEED_80  = '8',
      _SPEED_90  = '9',
      _SPEED_100 = 'q',
      _AUX_1_ON  = 'W',
      _AUX_1_OFF = 'w',
      _AUX_2_ON  = 'U',
      _AUX_2_OFF = 'u',
      _AUX_3_ON  = 'V',
      _AUX_3_OFF = 'v',
      _AUX_4_ON  = 'X',
      _AUX_4_OFF = 'x'
    };
    void manualControl(char);
};

#endif
