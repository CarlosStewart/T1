#include "main.h"
using namespace okapi; // eliminates the need to say okapi:: a hundred times

Controller masterController(ControllerId::master);

/////////////////////////////////////////
//          Drivetrain Control         //
/////////////////////////////////////////
namespace drivetrain {
// motor definitions
Motor drive_left_front(DLF_PORT, DLF_REV, BLUE, DEGREES);
Motor drive_right_front(DRF_PORT, DRF_REV, BLUE, DEGREES);
Motor drive_left_back(DLB_PORT, DLB_REV, BLUE, DEGREES);
Motor drive_right_back(DRB_PORT, DRB_REV, BLUE, DEGREES);

// control function that is run in a separate thread to prevent interruptions
void controlDrive(void *) {
  while (true) {
    double ly = masterController.getAnalog(ControllerAnalog::leftY) * 600;
    double lx = masterController.getAnalog(ControllerAnalog::leftX) * 600;
    double rx = masterController.getAnalog(ControllerAnalog::rightX) * 600;

    drive_right_front.moveVelocity(ly - rx - lx);
    drive_right_back.moveVelocity(ly - rx + lx);
    drive_left_front.moveVelocity(ly + rx + lx);
    drive_left_back.moveVelocity(ly + rx - lx);
    pros::delay(10);
  }
}
} // namespace drivetrain

/////////////////////////////////////
//          Tilter Control         //
/////////////////////////////////////
namespace tilt {
// Preset heights
const int TILT_UP = 200;   // height to relese stack
const int TILT_DOWN = 100; // normal resting height
const int TILT_LOW = 20;   // height for low towers
const int TILT_MED = 40;   // height for medium towers
const int TILT_HIGH = 60;  // height for tallest tower
// definition of buttons
ControllerButton btnUp(BTN_TILT_UP);
ControllerButton btnDown(BTN_TILT_DOWN);
ControllerButton btnLow(BTN_TILT_LOW);
ControllerButton btnMed(BTN_TILT_MID);
ControllerButton btnHigh(BTN_TILT_HIGH);
Potentiometer pot(TP_PORT);
auto controller = AsyncControllerFactory::posPID(
    boolToSign(TILT_REV) * TILT_PORT, pot, 0.001, 0.0, 0.0001);

// funtion to be run in opcontrol() to control the tilter
void controlTilt() {
  if (btnUp.changedToPressed()) { // tilt up if button is pressed
    controller.setTarget(TILT_UP);
    controller.flipDisable(false);
  } else if (btnUp.changedToReleased()) { // stop
    controller.flipDisable(true);
  } else if (btnDown.changedToPressed()) { // tilt down if button is pressed
    controller.setTarget(TILT_DOWN);
    controller.flipDisable(false);
  } else if (btnDown.changedToReleased()) { // stop
    controller.flipDisable(true);
  } else if (btnLow.changedToPressed()) { // tilt to low tower height when
                                          // button is pressed
    controller.setTarget(TILT_LOW);
    controller.flipDisable(false);
  } else if (btnLow.changedToReleased()) { // stop
    controller.flipDisable(true);
  } else if (btnMed.changedToPressed()) { // tilt to medium tower height
                                          // when button is pressed
    controller.setTarget(TILT_MED);
    controller.flipDisable(false);
  } else if (btnMed.changedToReleased()) { // stop
    controller.flipDisable(true);
  } else if (btnHigh.changedToPressed()) { // tilt to high tower height when
                                           // button is pressed
    controller.setTarget(TILT_HIGH);
    controller.flipDisable(false);
  } else if (btnHigh.changedToReleased()) { // stop
    controller.flipDisable(true);
  } else {
    controller.setTarget(pot.get());
    controller.flipDisable(false);
  }
}
} // namespace tilt

/////////////////////////////////////
//          Roller Control         //
/////////////////////////////////////
namespace roll {
const int speed = 100;
ControllerButton roll(BTN_ROLL_TOGGLE);
MotorGroup roll_group({boolToSign(ROLLL_REV) * ROLLL_PORT,
                       boolToSign(ROLLR_REV) * ROLLR_PORT});

// funtion to be run in opcontrol() to control the roller
void controlRoll() {
  // toggles the speed of the motor between (int) speed and 0
  if (roll.changedToPressed()) {
    roll_group.moveVelocity(abs(roll_group.getTargetVelocity() - speed));
  }
}
} // namespace roll

void opcontrol() {
  pros::Task taskDrive(drivetrain::controlDrive);
  while (true) {
    tilt::controlTilt();
    roll::controlRoll();
    pros::delay(20);
  }
}
