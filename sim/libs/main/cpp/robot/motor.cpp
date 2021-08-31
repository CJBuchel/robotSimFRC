#include "world/World.h"
#include "robot/Motor.h"

void Motor::set(double power) {
	this->_power = power > 1 ? 1 : power < -1 ? -1 : power; // can only be between -1:1
	World::setMotor(_port, _power);
}

double Motor::get() {
	return this->_power;
}

int Motor::getPort() {
	return this->_port;
}