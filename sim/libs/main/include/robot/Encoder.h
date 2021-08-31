#ifndef ENCODER_H
#define ENCODER_H

#include "headers.h"

/**
 * Encoder class used for getting input from motors
 */
class Encoder {
 public:
	Encoder(int port, double ticks_p_r = 2048) {
		this->_ticksPerRotation = ticks_p_r;
		this->_port = port;
	}

	double getRawTicks();
	double getRotations();

 private:
	double _ticksPerRotation;
	int _port;
};

#endif