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
void Sim::OnUpdate() {
	// World::setMotor(0, 0.5);
	// std::cout << "Motor 0: " << World::getMotor(0) << std::endl;
	drivetrain->set(1, 1);
}