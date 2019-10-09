#include "main.h"
using namespace okapi;
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  // sets up chassis for easy drivetrain control in autonomous
  auto drive = ChassisControllerFactory::create(
      boolToSign(DLF_REV) * DLF_PORT, boolToSign(DRF_REV) * DRF_PORT,
      boolToSign(DRB_REV) * DRB_PORT, boolToSign(DLB_REV) * DLB_PORT,
      IterativePosPIDController::Gains{0.001, 0, 0.0001},
      IterativePosPIDController::Gains{0.001, 0, 0.0001},
      IterativePosPIDController::Gains{0.001, 0, 0.0001}, BLUE,
      {0.00028222206, 2}); //{motor deg to m, motor deg to bot deg}

  // FOR TESTING ONLY
  Controller con;
  while (true) {
    drive.arcade(con.getAnalog(ControllerAnalog::leftY),
                 con.getAnalog(ControllerAnalog::rightX));
    pros::lcd::clear_line(1);
    pros::lcd::print();
  }
}
