#ifndef ENCODER_H
#define ENCODER_H

#include "headers.h"

/**
 * Encoder class used for getting input from motors
 */
class Encoder {
 public:
	Encoder(double ticks_p_r, int port) {
		this->_ticksPerRotation = ticks_p_r;
		this->_port = port;
	}

	double getValue() { return this->_value; }
	void setValue(double value) { this->_value = value; } // Set value should only be used in sim where the sim sets the encoder

 private:
	double _ticksPerRotation;
	double _value;
	int _port;
};

#endif