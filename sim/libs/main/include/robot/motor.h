#ifndef MOTOR_H
#define MOTOR_H

#include "headers.h"

class Motor {
 public:
	Motor(int port) {
		this->_port = port;
	}

	void set(double power) {
		this->_power = power;
	}

 private:
	int _port; // Internal port
	double _power; // internal power
};

#endif