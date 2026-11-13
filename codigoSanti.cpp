#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor LeftDriveSmart = motor(PORT2, ratio6_1, true);
motor RightDriveSmart = motor(PORT1, ratio6_1, false);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 421.89399999999995, 290, mm, 1);

motor ClawMotor = motor(PORT3, ratio36_1, false);

controller Controller1 = controller(primary);
motor elevatorMotor4MotorA = motor(PORT4, ratio36_1, true);
motor elevatorMotor4MotorB = motor(PORT5, ratio36_1, false);
motor_group elevatorMotor4 = motor_group(elevatorMotor4MotorA, elevatorMotor4MotorB);



// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1RightShoulderControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;
bool DrivetrainNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis4
      // right = Axis3 - Axis4
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis4.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis4.position();
      
      // check if the values are inside of the deadband range
      if (abs(drivetrainLeftSideSpeed) < 5 && abs(drivetrainRightSideSpeed) < 5) {
        // check if the motors have already been stopped
        if (DrivetrainNeedsToBeStopped_Controller1) {
          // stop the drive motors
          LeftDriveSmart.stop();
          RightDriveSmart.stop();
          // tell the code that the motors have been stopped
          DrivetrainNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the motors next time the input is in the deadband range
        DrivetrainNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
      // check the ButtonR1/ButtonR2 status to control ClawMotor
      if (Controller1.ButtonR1.pressing()) {
        ClawMotor.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        ClawMotor.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        ClawMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
      // check the ButtonX/ButtonB status to control elevatorMotor4
      if (Controller1.ButtonX.pressing()) {
        elevatorMotor4.spin(forward);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonB.pressing()) {
        elevatorMotor4.spin(reverse);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (!Controller1XBButtonsControlMotorsStopped) {
        elevatorMotor4.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1XBButtonsControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);

#pragma endregion VEXcode Generated Robot Configuration

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

competition Competition;

int Screen_precision = 0, Console_precision = 0, Controller1_precision = 0;

float myVariable;

// "when started" hat block
int whenStarted1() {
  while (true) {
    if (Drivetrain.power() > 55.0) {
      Drivetrain.setDriveVelocity(Drivetrain.power(), percent);
      Drivetrain.setDriveVelocity(55.0, percent);
    }
    if (Drivetrain.velocity(percent) == 100.0) {
      Drivetrain.setDriveVelocity(50.0, percent);
      wait(0.5, seconds);
      Drivetrain.setDriveVelocity(75.0, percent);
      wait(0.75, seconds);
      Drivetrain.setDriveVelocity(100.0, percent);
      waitUntil((Drivetrain.velocity(percent) == 0.0));
    }
    if (Drivetrain.velocity(percent) == 100.0) {
      Drivetrain.setTurnVelocity(50.0, percent);
      wait(0.25, seconds);
      Drivetrain.setTurnVelocity(75.0, percent);
      wait(0.25, seconds);
      Drivetrain.setTurnVelocity(100.0, percent);
      waitUntil((Drivetrain.velocity(percent) == 0.0));
    }
    if (elevatorMotor4.temperature(percent) == 80.0) {
      Controller1.Screen.print("elevatormotor on 80% temperature");
    }
    if (elevatorMotor4.temperature(percent) == 100.0) {
      Controller1.Screen.print("elevatormotor on 100% temperature");
    }
    if (Drivetrain.temperature(percent) == 80.0) {
      Controller1.Screen.print("drivetrain on 80% temperature");
    }
    if (Drivetrain.temperature(percent) == 100.0) {
      Controller1.Screen.print("drivetrain on 100% temperature");
    }
    ClawMotor.setStopping(hold);
    elevatorMotor4.setStopping(hold);
  wait(5, msec);
  }
  return 0;
}

// "when autonomous" hat block
int onauton_autonomous_0() {
  elevatorMotor4.spinFor(forward, 0.15, turns, true);
  waitUntil(elevatorMotor4.isDone());
  Drivetrain.driveFor(forward, 20.0, inches, true);
  wait(0.5, seconds);
  Drivetrain.turnFor(right, 90.0, degrees, true);
  wait(0.5, seconds);
  Drivetrain.driveFor(forward, 19.5, inches, true);
  waitUntil(Drivetrain.isDone());
  elevatorMotor4.spinFor(reverse, 0.048, turns, true);
  waitUntil(elevatorMotor4.isDone());
  Drivetrain.driveFor(forward, 0.5, inches, true);
  waitUntil(Drivetrain.isDone());
  elevatorMotor4.spinFor(reverse, 0.048, turns, true);
  waitUntil(elevatorMotor4.isDone());
  ClawMotor.spinFor(reverse, 1.0, turns, true);
  waitUntil(ClawMotor.isDone());
  Drivetrain.driveFor(reverse, 20.0, inches, true);
  waitUntil(Drivetrain.isDone());
  Drivetrain.turnFor(left, 90.0, degrees, true);
  waitUntil(Drivetrain.isDone());
  Drivetrain.driveFor(forward, 20.0, inches, true);
  elevatorMotor4.spinFor(forward, 0.048, turns, true);
  waitUntil((Drivetrain.isDone() && elevatorMotor4.isDone()));
  ClawMotor.spinFor(forward, 1.25, turns, true);
  waitUntil(ClawMotor.isDone());
  Drivetrain.driveFor(reverse, 20.0, inches, true);
  waitUntil(Drivetrain.isDone());
  Drivetrain.turnFor(left, 90.0, degrees, true);
  waitUntil(Drivetrain.isDone());
  Drivetrain.driveFor(forward, 20.0, inches, true);
  elevatorMotor4.spinFor(forward, 0.45, turns, true);
  waitUntil((Drivetrain.isDone() && elevatorMotor4.isDone()));
  elevatorMotor4.spinFor(forward, 0.05, turns, true);
  ClawMotor.spinFor(reverse, 1.0, turns, true);
  return 0;
}

// "when driver control" hat block
int ondriver_drivercontrol_0() {
  return 0;
}

void VEXcode_driver_task() {
  // Start the driver control tasks....
  vex::task drive0(ondriver_drivercontrol_0);
  while(Competition.isDriverControl() && Competition.isEnabled()) {this_thread::sleep_for(10);}
  drive0.stop();
  return;
}

void VEXcode_auton_task() {
  // Start the auton control tasks....
  vex::task auto0(onauton_autonomous_0);
  while(Competition.isAutonomous() && Competition.isEnabled()) {this_thread::sleep_for(10);}
  auto0.stop();
  return;
}



int main() {
  vex::competition::bStopTasksBetweenModes = false;
  Competition.autonomous(VEXcode_auton_task);
  Competition.drivercontrol(VEXcode_driver_task);

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  whenStarted1();
}