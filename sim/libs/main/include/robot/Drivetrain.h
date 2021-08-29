#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <string.h>

#include "headers.h"
#include "Motor.h"
#include "Encoder.h"
#include "Gearbox.h"


/**
 * Config for drivetrain
 */
struct DrivetrainConfig {

	// Left and right drive
	Gearbox &leftDrive;
	Gearbox &rightDrive;

	// gyro

	// drivetrain config
	double trackWidth;
	
	double trackDepth;

	double wheelRadius;

	double mass;

	bool reversed = false;

	std::string name = "<Drivetrain>";
};


/**
 * Drivetrain (has 2 motors left and right)
 */
class Drivetrain {
 public:
	Drivetrain(DrivetrainConfig config);
	~Drivetrain();

	void set(double left, double right);
	
	Gearbox &getLeft();
	Gearbox &getRight();

 private:
	DrivetrainConfig _config;
};

#endif