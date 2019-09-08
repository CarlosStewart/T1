// MACROS
#define GREEN AbstractMotor::gearset::green
#define BLUE AbstractMotor::gearset::blue
#define DEGREES AbstractMotor::encoderUnits::degrees

// MOTORS
const int DLF_PORT = 1;
const bool DLF_REV = true;

const int DRF_PORT = 2;
const bool DRF_REV = false;

const int DLB_PORT = 3;
const bool DLB_REV = true;

const int DRB_PORT = 4;
const bool DRB_REV = false;

const int TILT_PORT = 5;
const bool TILT_REV = false;

// CONTROLS
#define BTN_TILT_UP ControllerDigital::L1
#define BTN_TILT_DOWN ControllerDigital::L2
#define BTN_TILT_T1 ControllerDigital::A

// VALUES
const int TILT_UP = 200;
const int TILT_DOWN = 100;
