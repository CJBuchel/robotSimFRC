#include "Sim.h"

#include "robot/Drivetrain.h"
#include "robot/keyboard.h"

Keyboard keyboard;

Motor frontLeft{0}, backLeft{1}, frontRight{2}, backRight{3};

Gearbox leftGearbox{ {&frontLeft, &backLeft} };
Gearbox rightGearbox{ {&frontRight, &backRight} };

DrivetrainConfig config{ leftGearbox, rightGearbox };
Drivetrain drivetrain{ config };

double leftPower = 0, rightPower = 0;

/**
 * Initializer (Happens once)
 */
void Sim::Init() {
	
}

/**
 * Periodic Update
 */
void Sim::Periodic() {
	// if (Config::Sim::getGlobalTimeStamp() < 5) {
	// 	drivetrain.set(0.3, 0.3);
	// } else {
	// 	drivetrain.set(-1, -0.5);
	// }

	// if (keyboard.getKey(Keyboard::Key::w)) {
	// 	leftPower = 0.5;
	// 	rightPower = 0.5;
	// } else {
	// 	leftPower = 0;
	// 	rightPower = 0;
	// }

	if (keyboard.getKey(Keyboard::Key::w)) {
		leftPower += 1;
		rightPower += 1;
	}

	if (keyboard.getKey(Keyboard::Key::s)) {
		leftPower -= 1;
		rightPower -= 1;
	}

	if (keyboard.getKey(Keyboard::Key::a)) {
		leftPower -= 1;
		rightPower += 1;
	}

	if (keyboard.getKey(Keyboard::Key::d)) {
		leftPower += 1;
		rightPower += -1;
	}

	std::cout << "Key: " << keyboard.getRawKey() << std::endl;

	drivetrain.set(leftPower, rightPower);
}