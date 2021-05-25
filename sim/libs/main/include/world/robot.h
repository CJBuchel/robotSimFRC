#include "world.h"
#include "visuals/Window.h"

/**
 * Draws robot into world
 */
class Robot {
 public:
	Robot(Window &window) : _window(window) {
		std::cout << "World robot initialized" << std::endl;
		_x = SimData::Robot::start_x;
		_y = SimData::Robot::start_y;
		_angle = SimData::Robot::start_angle;
		update(); // Initial draw
	}

	void update() {
		_window.drawRect({_x, _y}, SimData::Robot::width, SimData::Robot::length, _angle);
	}

 private:
	Window &_window;

	double _x,_y,_angle;
};