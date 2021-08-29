#include "Sim.h"

#include "robot/Drivetrain.h"

Motor frontLeft{0}, backLeft{1}, frontRight{2}, backRight{3};



Gearbox leftGearbox{ {&frontLeft, &backLeft} };
Gearbox rightGearbox{ {&frontRight, &backRight} };

DrivetrainConfig config{ leftGearbox, rightGearbox };
Drivetrain drivetrain{ config };

/**
 * Initializer (Happens once)
 */
void Sim::Init() {
	
}

/**
 * Periodic Update
 */
void Sim::Periodic() {
	drivetrain.set(1, 1);
}