#include "main.h"
using namespace okapi; // eliminates the need to say okapi:: a hundred times

Controller masterController(ControllerId::master);

/////////////////////////////////////////
//          Drivetrain Control         //
/////////////////////////////////////////
namespace drivetrain {
Motor drive_left_front(DLF_PORT, DLF_REV, BLUE, DEGREES);
Motor drive_right_front(DRF_PORT, DRF_REV, BLUE, DEGREES);
Motor drive_left_back(DLB_PORT, DLB_REV, BLUE, DEGREES);
Motor drive_right_back(DRB_PORT, DRB_REV, BLUE, DEGREES);

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
ControllerButton tiltUpBTN(BTN_TILT_UP);
ControllerButton tiltDownBTN(BTN_TILT_DOWN);
ControllerButton tiltT1BTN(BTN_TILT_T1);
auto controller = AsyncControllerFactory::posPID(
    boolToSign(TILT_REV) * TILT_PORT, Potentiometer('G'), 0.001, 0.0, 0.0001);

void controlTilt() {
  if (tiltUpBTN.changedToPressed()) {
    controller.setTarget(TILT_UP);
    controller.flipDisable(false);
  } else if (tiltUpBTN.changedToReleased()) {
    controller.flipDisable(true);
  } else if (tiltDownBTN.changedToPressed()) {
    controller.setTarget(TILT_DOWN);
    controller.flipDisable(false);
  } else if (tiltDownBTN.changedToReleased()) {
    controller.flipDisable(true);
  }
}
} // namespace tilt

void opcontrol() {
  pros::Task taskDrive(drivetrain::controlDrive);
  while (true) {
    tilt::controlTilt();
    pros::delay(20);
  }
}
