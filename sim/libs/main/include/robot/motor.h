#ifndef MOTOR_H
#define MOTOR_H

#include "headers.h"

class Motor {
 public:
	Motor(int port) {
		this->_port = port;
	}

	void set(double power);

	/**
	 * Return the current power for the motor
	 */
	double get();

	/**
	 * Return the current port number for the motor
	 */
	int getPort();

 private:
	int _port; // Internal port
	double _power; // internal power
};

#endif