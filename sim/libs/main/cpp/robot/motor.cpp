#include "world/World.h"
#include "robot/Motor.h"

void Motor::set(double power) {
	this->_power = power;
	World::setMotor(_port, _power);
}

double Motor::get() {
	return this->_power;
}

int Motor::getPort() {
	return this->_port;
}