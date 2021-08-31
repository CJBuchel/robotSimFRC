#include "Sim.h"

#include "robot/Drivetrain.h"
#include "robot/keyboard.h"

Keyboard keyboard;

Motor frontLeft{0}, backLeft{1}, frontRight{2}, backRight{3};

Encoder leftEncoder{0, 2048};
Encoder rightEncoder{1, 2048};

Gearbox leftGearbox{ {&frontLeft, &backLeft}, &leftEncoder };
Gearbox rightGearbox{ {&frontRight, &backRight}, &rightEncoder };

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
	if (Config::Sim::getGlobalTimeStamp() < 5) {
		drivetrain.set(0.3, 0.3);
	} else {
		drivetrain.set(-1, -0.5);
	}

	// std::cout << leftGearbox.encoder->getRotations() << std::endl;

	// if (keyboard.getKey(Keyboard::Key::w)) {
	// 	leftPower += 1;
	// 	rightPower += 1;
	// }

	// if (keyboard.getKey(Keyboard::Key::s)) {
	// 	leftPower -= 1;
	// 	rightPower -= 1;
	// }

	// if (keyboard.getKey(Keyboard::Key::a)) {
	// 	leftPower -= 1;
	// 	rightPower += 1;
	// }

	// if (keyboard.getKey(Keyboard::Key::d)) {
	// 	leftPower += 1;
	// 	rightPower += -1;
	// }

	// drivetrain.set(leftPower, rightPower);
}