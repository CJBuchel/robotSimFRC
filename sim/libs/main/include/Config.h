#include <string.h>

struct Config {

	/**
	 * Simulator Window
	 */
	struct Window {
		int Width = 1600, Height = 800; // Size of feild in cm
		double FPS = 60; // Frames per second for simulator
		std::string name = "Robot Simulation";
	}; Window window;


	// Window &getWindow() { return window; }


	struct Robot {
		double weight = 50; // in KG
		double start_x, start_y, start_angle; // Starting pos of robot
		double maxSpeed, maxAcceleration; // In meters per second
	}; Robot robot;
};