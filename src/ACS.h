#ifndef ACS_h
#define ACS_h
#include <Smartcar.h>

class DriveController
{
  public:
    DriveController();
    void begin(Car&);
    void update();
    void drive();
    void reverse();
    void stop();
  private:
    Car *car;
    const float _MIN_CRUISE_CONTROL_SPEED = 0.2;
    bool debugDriveController = false;
    void init();
    void debug(String);
};

class ParallelParking
{
  public:
    ParallelParking();
    void begin(DriveController&);
    void stop();
  private:
    DriveController *driveController;
};

class RemoteControl
{
  public:
    RemoteControl();
    void listen();
    void begin(DriveController&);
  private:
    void init();
    DriveController *driveController;
};

class SensorBridge
{
  public:
    SensorBridge();
    void begin(Car&);
    void update();
    void debug();
    long getOdometerLeftDistance();
    long getOdometerRightDistance();

  private:
    Car *car;
    const byte _TRIGGER_PIN_FR =  5,
               _TRIGGER_PIN_BR =  6,
               _TRIGGER_PIN_BB = 44,
               _ECHO_PIN_FR    =  4,
               _ECHO_PIN_BR    =  7,
               _ECHO_PIN_BB    = 42,
               _ODOMETER_PIN_L =  2,
               _ODOMETER_PIN_R =  3;
    void init();
};

#endif
