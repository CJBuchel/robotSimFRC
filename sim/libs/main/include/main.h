#ifndef MAIN_H
#define MAIN_H

#include "headers.h"
#include "Sim.h"
#include "world/robot.h"

bool running = false;
const std::string SimData::Window::name = "Robot Simulation";

class Controller {
 public:
	Controller() {
		window = new Window(SimData::Window::Height, SimData::Window::Width, SimData::Window::name);
		sim = new Sim(*window);
		robot = new Robot(*window);
	}

	~Controller() {
		free(robot);
		free(sim);
		free(window);
	}

	Window *window;
	Sim *sim;
	Robot *robot;
}; Controller controller;

#endif