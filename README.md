# VEXcode Competition Fall 2026

Proprietary code of Regina Mundi Catholic School, London, Ontario

To run the code, copy the contents of src/main.cpp, then paste them into the VEXcode platform and download them into the processor unit (AKA brain).

## Connection Guide

| Motor | Port |
| ----- | ---- |
| DRIVETRAIN_LEFT | PORT1 |
| DRIVETRAIN_RIGHT | PORT2 |
| ELEVATOR | PORT3 && PORT4 |
| ARM | PORT5 |
| CLAW | PORT6 |

## Control Movement

| Button | Movement |
| ------ | -------- |
| L1 | DRIVETRAIN_LEFT FORWARD |
| L2 | DRIVETRAIN_LEFT REVERSE |
| R1 | DRIVETRAIN_RIGHT FORWARD | 
| R2 | DRIVETRAIN_RIGHT REVERSE |
| J1 | CLAW FORWARD/REVERSE |
| J2 | DRIVETRAIN FORWARD/REVERSE |
| J3 | ELEVATOR UP/DOWN |
| J4 | ARM UP/DOWN | 

Drivetrain speed using buttons is set to 75%, precise control forward/reverse is done with joysticks. This is done to simplify robot control while allowing for precise alignment with towers.

## Additional Notes

The design of the robot is still under development. Although the robot is unstable when the arm is extended, it has full capacity to recover itself. This recovery, as well as the optimal driving position, will be developed for a second delivery of the competition.

It is recommended to add a rubber tip to the claw in order to easily rotate the triangles in the arena, assistance for this rotation will also be programmed for a future delivery.