#include "Sim.h"

#include "robot/drivetrain.h"

Drivetrain *drivetrain;
DrivetrainConfig config;

/**
 * Initializer (Happens once)
 */
void Sim::Init() {
	config.leftPort = 0;
	config.rightPort = 1;
	drivetrain = new Drivetrain(config);
}

/**
 * Periodic Update
 */
void Sim::Periodic() {
	// drivetrain->set(1, 1);
}