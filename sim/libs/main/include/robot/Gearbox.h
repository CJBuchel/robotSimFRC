#ifndef GEARBOX_H
#define GEARBOX_H

#include "Motor.h"
#include "Encoder.h"

/**
 * Gearbox
 * 
 * Holds motors in an array with a single encoder
 * and reduction (if the robot actually has reduction)
 */
struct Gearbox {
	std::vector<Motor*> motors;
	Encoder *encoder = nullptr; // optional

	double reduction = 1; // set as reduction ratio (eg input 2 = 2:1)
};

#endif