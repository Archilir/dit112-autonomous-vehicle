#ifndef AutonomousCarSystem_h
#define AutonomousCarSystem_h
#include <Smartcar.h>

class Driver
{
  public:
    Driver();
    bool isMoving();
    bool isAuto();
    bool isManual();

    void setAutoControl();
    void setManualControl();

    void begin(Car*);
    void update();
    void setSpeed(int);
    void setAngle(int);
    int getAngle();
    int getSpeed();

    void drive(float);
    // Drive functions
    void driveSlow();
    void driveAverage();
    void driveFast();
    // Reverse functions
    void reverseSlow();
    void reverseAverage();
    void reverseFast();

    void go(int);
    // Stop
    void stop();
  private:
    Car *car;
    const float _MIN_CRUISE_SPEED = 0.3,
                _AVG_CRUISE_SPEED = 1.0,
                _MAX_CRUISE_SPEED = 2.5;
};

class Sensors
{
  public:
    Sensors();
    void begin(Car*);
    void update();
    void debug();
    long getOdometerLeftDistance();
    long getOdometerRightDistance();
    void startObstacleMonitor();
    void stopObstacleMonitor();
    void obstacleMonitor();
    bool obstacleMonitorEnabled();

    int  getObstacleMinDepth();
    int  getObstacleDistance();
    bool isObstacleUpdated();

    bool obstacleDataUpdated = false;


    int getFRDistance();
    int getBRDistance();
    int getBBDistance();

  private:
    Car *car;

    const char _OBSTACLE_SENSITIVITY_THRESHOLD = 3;
    bool obstacleMonitorState = false;

    int startPos = -1,
        lastEndPos,
        lastDepth,
        endPos,
        minDepth;

    int obstacleDistance,
        obstacleMinDepth;

    int sonicFRDistance,
        sonicBRDistance,
        sonicBBDistance;

    void updateUltrasonic();

    void enableObstacleMonitor();
    void disableObstacleMonitor();
    const char _TRIGGER_PIN_FR =  5,
               _TRIGGER_PIN_BR =  6,
               _TRIGGER_PIN_BB = 44,
               _ECHO_PIN_FR    =  4,
               _ECHO_PIN_BR    =  7,
               _ECHO_PIN_BB    = 42,
               _ODOMETER_PIN_L =  2,
               _ODOMETER_PIN_R =  3;
};


class Parking
{
  public:
    Parking();
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
    char parkingState = _OFF;
    void parallel();
};

class RemoteControl
{
  public:
    RemoteControl();
    void listen();
    void begin(Driver*, Parking*);
  private:
    Driver  *driver;
    Parking *parking;
    unsigned long timeoutCounter;
    bool timeoutLock;
    enum {
      _PARKING = 'p',
      _MANUAL  = 'm',
      _FORWARD = 'w',
      _REVERSE = 's',
      _LEFT    = 'a',
      _RIGHT   = 'd'
    };
    void manualControl(char);
};

#endif
