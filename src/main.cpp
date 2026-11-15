/* 
    VexCode Competition Fall 2026
    Regina Mundi Catholic School
    London, Ontario
*/

#pragma region VEXcode Generated Robot Configuration

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;

// Controller 
controller CONTROLLER = controller(primary);

// Drivetrain motors
motor DRIVETRAIN_LEFT = motor(PORT2, ratio6_1, true);
motor DRIVETRAIN_RIGHT = motor(PORT1, ratio6_1, false);
motor_group DRIVETRAIN = motor_group(DRIVETRAIN_LEFT, DRIVETRAIN_RIGHT);

// Elevator motors
motor ELEVATOR_LEFT = motor(PORT4, ratio36_1, true);
motor ELEVATOR_RIGHT = motor(PORT5, ratio36_1, false);
motor_group ELEVATOR = motor_group(ELEVATOR_LEFT, ELEVATOR_RIGHT);

// Claw motor
motor CLAW = motor(PORT3, ratio36_1, false);

// Initialize robot configuration
void vexcodeInit() {
    int systemTime = Brain.Timer.systemHighResolution();
    double batteryCurrent = Brain.Battery.current();
    double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

    // Combine these values into a single integer
    int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

    // Set the seed
    srand(seed);
}

// Define inputs from controller
int axis() {
    if (abs(CONTROLLER.Axis1.position()) > 25) {return 1;}
    if (abs(CONTROLLER.Axis2.position()) > 25) {return 2;}
    if (abs(CONTROLLER.Axis3.position()) > 5) {return 3;}
    if (abs(CONTROLLER.Axis4.position()) > 5) {return 4;}
    else {return 0;}
}

directionType direction(int position) {
    return (position > 0) ? forward : reverse;
}

directionType opposite(directionType direction) {
    if (direction == forward) {return reverse;}
    else if (direction == reverse) {return forward;}
    else {return forward;}
}

void remote_control() {
    // --- 1. Control Claw (Axis 1) ---
    int axis1Val = CONTROLLER.Axis1.position();
    if (abs(axis1Val) > 15) {
        CLAW.setVelocity(abs(axis1Val), percent);
        CLAW.spin((axis1Val > 0) ? forward : reverse);
    } else {
        CLAW.stop();
        CLAW.setStopping(hold);
    }

    // --- 2. Control Elevator (Axis 2) ---
    int axis2Val = CONTROLLER.Axis2.position();
    if (abs(axis2Val) > 15) {
        ELEVATOR.setVelocity(abs(axis2Val), percent);
        ELEVATOR.spin((axis2Val > 0) ? forward : reverse);
    } else {
        ELEVATOR.stop();
        ELEVATOR.setStopping(hold);
    }

    // --- 3. Control Drivetrain Forward/Backward (Axis 3) ---
    int axis3Val = CONTROLLER.Axis3.position();
    int axis4Val = CONTROLLER.Axis4.position();

    if (abs(axis3Val) > 5) {
        DRIVETRAIN.setVelocity(abs(axis3Val), percent);
        DRIVETRAIN.spin((axis3Val > 0) ? forward : reverse);
    } 
    // --- 4. Control Drivetrain Turning (Axis 4) ---
    else if (abs(axis4Val) > 5) {
        DRIVETRAIN_LEFT.setVelocity(abs(axis4Val), percent);
        DRIVETRAIN_RIGHT.setVelocity(abs(axis4Val), percent);
        if (axis4Val > 0) { 
            // Turn Right
            DRIVETRAIN_LEFT.spin(forward);
            DRIVETRAIN_RIGHT.spin(reverse);
        } else { 
            // Turn Left
            DRIVETRAIN_LEFT.spin(reverse);
            DRIVETRAIN_RIGHT.spin(forward);
        }
    } 
    // --- Otherwise Stop Drivetrain ---
    else {
        DRIVETRAIN.stop();
    }
}

int check_control() {
    while (true) {
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