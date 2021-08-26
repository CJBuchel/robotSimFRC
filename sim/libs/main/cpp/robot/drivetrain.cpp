#include "robot/drivetrain.h"

Drivetrain::Drivetrain(DrivetrainConfig config) {
	_config = config;
	_left = new Motor(_config.leftPort);
	_right = new Motor(_config.rightPort);
}

Drivetrain::~Drivetrain() {
	free(_left);
	free(_right);
}

void Drivetrain::set(double left, double right) {
	_left->set(left);
	_right->set(-right);
}

Motor *Drivetrain::getLeft() {
	return _left;
}

Motor *Drivetrain::getRight() {
	return _right;
}