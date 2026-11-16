/* 
    VexCode Competition Fall 2026
    Regina Mundi Catholic School
    London, Ontario    
*/

# pragma region VEXcode Generated Robot Configuration

#include <stdlib.h>
#include <math.h>
#include "vex.h"

using namespace vex;

// Brain should be initialized by default

brain Brain;

controller CONTROLLER = controller(primary);

// Drivetrain motors

motor DRIVETRAIN_LEFT = motor(PORT1, false);
motor DRIVETRAIN_RIGHT = motor(PORT2, true);
motor_group DRIVETRAIN = motor_group(DRIVETRAIN_LEFT, DRIVETRAIN_RIGHT);

// Elevator motors

motor ELEVATOR_1 = motor(PORT3, false);
motor ELEVATOR_2 = motor(PORT4, true);
motor_group ELEVATOR = motor_group(ELEVATOR_1, ELEVATOR_2);

// Arm motor

motor ARM = motor(PORT5, false);

// Claw motor

motor CLAW = motor(PORT6, false);

// Store Joysticks positions

int32_t JOYSTICK[5] = {0,0,0,0,0};

void update_joysticks_position() {
    JOYSTICK[1] = CONTROLLER.Axis1.position();
    JOYSTICK[2] = CONTROLLER.Axis2.position();
    JOYSTICK[3] = CONTROLLER.Axis3.position();
    JOYSTICK[4] = CONTROLLER.Axis4.position();
}

// Update Button Status

bool BUTTON[5] = {0,0,0,0,0};

void update_button_status() {
    BUTTON[1] = CONTROLLER.ButtonL1.pressing();
    BUTTON[2] = CONTROLLER.ButtonL2.pressing();
    BUTTON[3] = CONTROLLER.ButtonR1.pressing();
    BUTTON[4] = CONTROLLER.ButtonR2.pressing();
}

void update_control_status() {
    update_joysticks_position();
    update_button_status();
}

// Determine direction

directionType direction(int32_t position) {
    return (position > 0) ? forward : reverse;
}

directionType not_direction(directionType direction) { // Inverse of direction
    return (direction == forward) ? reverse : forward;
}

// Initialize robot configuration
void vexcodeInit() {
    int systemTime = Brain.Timer.systemHighResolution();
    double batteryCurrent = Brain.Battery.current();
    double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

    // Combine these values into a single integer
    int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

    // Set motors speed
    DRIVETRAIN_LEFT.setVelocity(75, percent);
    DRIVETRAIN_RIGHT.setVelocity(75, percent);

    // Set the seed
    srand(seed);
}



// Remote Control configuration

void remote_control() {
    if (BUTTON[1] && !BUTTON[2]) {  // Left drivetrain motor
        DRIVETRAIN_LEFT.spin(forward);
    } else if (!BUTTON[1] && BUTTON[2]) {
        DRIVETRAIN_LEFT.spin(reverse);
    } else {
        DRIVETRAIN_LEFT.setStopping(hold);
    }

    if (BUTTON[3] && !BUTTON[4]) {  // Rigth drivetrain motor
        DRIVETRAIN_RIGHT.spin(forward);
    } else if (!BUTTON[3] && BUTTON[4]) {
        DRIVETRAIN_RIGHT.spin(reverse);
    } else {
        DRIVETRAIN_RIGHT.setStopping(hold);
    }

    if (abs(JOYSTICK[1]) > 5) {     // Move claw
        CLAW.setVelocity(abs(JOYSTICK[1]), percent);
        CLAW.spin(direction(JOYSTICK[1]));
    }

    if (abs(JOYSTICK[2]) > 5) {     // Precision drivetrain movement (25%)
        DRIVETRAIN.setVelocity(abs(JOYSTICK[2])/4, percent);
        DRIVETRAIN.spin(direction(JOYSTICK[2]));
        DRIVETRAIN.setVelocity(75, percent); // Return to original velocity
    }

    if(abs(JOYSTICK[3]) > 5) {      // Control elevator
        ELEVATOR.setVelocity(abs(JOYSTICK[3]), percent);
        ELEVATOR.spin(direction(JOYSTICK[3]));
    }

    if(abs(JOYSTICK[4] > 5)) {
        ARM.setVelocity(abs(JOYSTICK[4]), percent);
        ARM.spin(direction(JOYSTICK[4]));
    }
}

int check_control() {
    while(true) {
        update_control_status();
        remote_control();
        wait(20, msec);
    }
    return 0;
}

task control_manually(check_control);

#pragma endregion VEXcode Generated Robot Configuration

competition Competition;

void driver_control() {
    vex::task drive0(control_manually);
    while(Competition.isDriverControl() && Competition.isEnabled()) {
        this_thread::sleep_for(10);
    }
    drive0.stop();
    return;
}

int main() {
    vex::competition::bStopTasksBetweenModes = false;
    Competition.drivercontrol(driver_control);

    vexcodeInit();
}