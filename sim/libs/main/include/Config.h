/**
 * 
 * Main data for simulation configuration
 * 
 * 
 */


#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>
#define global static constexpr // Constant experssion accessable to all (cannot be modified)

struct Config {

	/**
	 * Sim data, global delta time
	 */
	struct Sim {
		static void setGlobalDT(double dt) { _globalDT = dt; } // Only one setter should be accessed (in main)
		static double getGlobalDT() { return _globalDT; }

		static void setGlobalCPS(double cps) { _cps = cps; }
		static double getGlobalCPS() { return _cps; }

		static void setGlobalTimeStamp(double time) { _time = time; } // based off robot timestamp. Resets when robot resets
		static double getGlobalTimeStamp() { return _time; }

		static double _globalDT;
		static double _cps;
		static double _time;
	};

	/**
	 * Simulator Window
	 */
	struct Window {
		global int Width = 1600, Height = 800; // Size of feild in cm
		global double CPS = 500; // Essentially frames per second, but for the entire program
		static const std::string name; // Defined in main.h
		global int field = 0; // Set to 0 for blank window
	};

	struct Keyboard {
		static void setKey(int key) {
			_key = key;
		}
		static int getKey() { return _key; }
		static int _key; // defined in main.h
	};

	struct World {
		global int motorPorts = 4; // Total motor ports
		global int encoderPorts = 2; // Total encoder ports
		global int gyroPorts = 1; // Total gyro ports
	};

	/**
	 * World Robot Data (Basically the physical version of the robot)
	 */
	struct Robot {
		global double weight = 50; // in KG
		global double start_x = 100, start_y = 400, start_angle = 0; // Starting pos of robot (100,400,0)
		global double maxSpeed = 5, maxAcceleration = 3; // In meters per second
		global double wheelDiameter = 0.1524; // Size in m

		/**
		 * Robot Size (cm)
		 */
		global double length = 75;
		global double width = 65;


		/**
		 * Robot encoders
		 */
		global double ticksPerRotation = 2400;


		/**
		 * Ports
		 */
		global int leftMPort[World::motorPorts/2] = {0,1}; 
		global int rightMPort[World::motorPorts/2] = {2,3};

		global int leftEncPort = 0;
		global int rightEncPort = 1;

		global int gyroPort = 0;
	};
};


#endif