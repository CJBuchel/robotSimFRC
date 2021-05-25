/**
 * 
 * World for the robot to interface with
 * 
 * Consists of a bunch of ports (Motors and encoders)
 * that either modified by the world or vise versa
 * 
 */


#ifndef WORLD_H
#define WORLD_H

#include "headers.h"
#include "SimData.h"


class World {
 public:

	/**
	 * Motor controllers
	 */
	static void setMotor(int port, double value) {
		motors.at(port) = value;
	}

	static double getMotor(int port) {
		return motors.at(port);
	}

	/**
	 * Encoder controllers
	 */
	static void setEnc(int port, double value) {
		encoders.at(port);
	}

	static double getEnc(int port) {
		return encoders.at(port);
	}

	static void setGyro(int port, double value) {
		gyros.at(port) = value;
	}

	static double getGyro(int port) {
		return gyros.at(port);
	}

 private:
	static std::vector<double>motors; // Motor vals
	static std::vector<double>encoders; // Enc vals
	static std::vector<double>gyros; // Gyro vals
};

#endif