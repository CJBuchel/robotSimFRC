/**
 * 
 * Main data for simulation configuration
 * 
 * 
 */


#ifndef SIMDATA_H
#define SIMDATA_H

#include <string.h>
#define global static constexpr // Constant experssion accessable to all (cannot be modified)

struct SimData {


	struct Sim {
		static void setGlobalDT(double dt) { _globalDT = dt; } // Only one setter should be accessed (in main)
		static double getGlobalDT() { return _globalDT; }
		static double _globalDT;
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

	/**
	 * World Robot Data (Basically the physical version of the robot)
	 */
	struct Robot {
		global double weight = 50; // in KG
		global double start_x = 100, start_y = 400, start_angle = 0; // Starting pos of robot
		global double maxSpeed = 1, maxAcceleration = 0.2; // In meters per second

		/**
		 * Robot Size (cm)
		 */
		global double length = 75;
		global double width = 65;


		/**
		 * Ports
		 */
		global int leftMPort = 0; 
		global int rightMPort = 1;

		global int leftEncPort = 0;
		global int rightEncPort = 1;
	};
};


#endif