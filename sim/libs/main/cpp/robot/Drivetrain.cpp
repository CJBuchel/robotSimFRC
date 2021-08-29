#include "robot/Drivetrain.h"

Drivetrain::Drivetrain(DrivetrainConfig config) : _config(config) {
	// _left = new Motor(_config.leftPort);
	// _right = new Motor(_config.rightPort);
}

Drivetrain::~Drivetrain() {
	// free(_left);
	// free(_right);
}

void Drivetrain::set(double leftPower, double rightPower) {
	// Left drive
	for (size_t i = 0; i < _config.leftDrive.motors.size(); i++) {
		_config.leftDrive.motors.at(i)->set(leftPower);
	}

	// Right drive
	for (size_t i = 0; i < _config.rightDrive.motors.size(); i++) {
		_config.rightDrive.motors.at(i)->set(rightPower);
	}
}

Gearbox &Drivetrain::getLeft() {
	return !_config.reversed ? _config.leftDrive : _config.rightDrive;
}

Gearbox &Drivetrain::getRight() {
	return !_config.reversed ? _config.rightDrive : _config.leftDrive;
}