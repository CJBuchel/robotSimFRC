#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "headers.h"
#include "motor.h"
#include "encoder.h"


/**
 * Config for drivetrain
 */
struct DrivetrainConfig {
	int leftPort, rightPort;
	double encTicks; // Ticks per rotation
};


/**
 * Drivetrain (has 2 motors left and right)
 */
class Drivetrain {
 public:
	Drivetrain(DrivetrainConfig config);
	~Drivetrain();

	void set(double left, double right);
	
	Motor *getLeft();
	Motor *getRight();

 private:
	DrivetrainConfig _config;
	Motor *_left;
	Motor *_right;
};

#endif