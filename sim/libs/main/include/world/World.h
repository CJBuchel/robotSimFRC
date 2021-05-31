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


class World {
 public:

	/**
	 * Initialize the world members
	 */
	static void init() {
		std::cout << "World Values Initialized" << std::endl;

		// Motor init
		for (int i = 0; i < Config::World::motorPorts; i++) {
			motors.push_back(0);
		}

		// Encoder init
		for (int i = 0; i < Config::World::encoderPorts; i++) {
			encoders.push_back(0);
		}

		// Gyro init
		for (int i = 0; i < Config::World::gyroPorts; i++) {
			gyros.push_back(0);
		}
	}

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
		encoders.at(port) = value;
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
	static std::vector<double> motors; // Motor vals
	static std::vector<double> encoders; // Enc vals
	static std::vector<double> gyros; // Gyro vals
};

#endif