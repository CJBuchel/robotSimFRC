#ifndef MAIN_H
#define MAIN_H

#include "headers.h"
#include "Sim.h"
#include "world/Robot.h"

// Set globals
bool running = false;
const std::string Config::Window::name = "Robot Simulation";
double Config::Sim::_globalDT = 0;
double Config::Sim::_cps = 0;
double Config::Sim::_time = 0;
int Config::Keyboard::_key = -1;

class Controller {
 public:
	Controller() {
		World::init();
		window = new Window(Config::Window::Height, Config::Window::Width, Config::Window::name);
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