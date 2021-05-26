#ifndef ROBOT_H
#define ROBOT_H

#include "world.h"
#include "visuals/Window.h"

static cv::Scalar rightColour{0, 0, 255};
static cv::Scalar leftColour{255, 0, 0};
static cv::Scalar frontColour{0, 255, 0};

/**
 * Draws robot into world
 */
class Robot {
 public:
	Robot(Window &window) : _window(window) {
		std::cout << "World robot initialized" << std::endl;
		_x = SimData::Robot::start_x;
		_x = 0; // temp
		_y = SimData::Robot::start_y;
		_y = 0; // temp
		_angle = SimData::Robot::start_angle;
		update(); // Initial draw
	}

	void update() {

		double left = 0.5;
		double right = 0;

		double ang = angular(left, right);
		double lin = linear(left, right);

		_heading += ang * SimData::Sim::getGlobalDT();
		_x += lin * SimData::Sim::getGlobalDT() * cos(_heading);
		_y += lin * SimData::Sim::getGlobalDT() * sin(_heading);

		drawRobot(_window.getWindow(), left, right);

		// Draw main robot body
		// _window.drawRect({_x, _y}, SimData::Robot::width, SimData::Robot::length, _angle);
		// _window.drawText("x: " + std::to_string((int)_x) + ", y: " + std::to_string((int)_y), {_x-50, _y+70});


		// Draw robot left track
		// _window.drawRect({_x, _y}, 10, SimData::Robot::length, _angle, {255, 0, 0});
	}

	void drawRobot(cv::Mat &img, double l, double r) {
		cv::circle(img, toWorld(0,0), 2, cv::Scalar(255,255,255), -1);
		_window.drawText("_x: " + std::to_string(_x) + ", _y: " + std::to_string(_y), {500, 500});
		_window.drawText("x: " + std::to_string(_x) + ", y: " + std::to_string(_y), {500, 550});

		// Base
		drawBoxToWorld(img, cv::Scalar{255,255,255}, 2, -1, -1, 2, 2);
		drawBoxToWorld(img, frontColour, 2, 1, -1, 0.05, 2); // front

		drawBoxToWorld(img, leftColour * std::abs(l), 4, -1, -1, 2, 0.1);        // Left fill
		drawBoxToWorld(img, rightColour * std::abs(r), 4, -1, 1 - 0.2, 2, 0.1);  // Right fill

		drawBoxToWorld(img, leftColour, 1, -1, -1, 2, 0.2);        // Left Outline
		drawBoxToWorld(img, rightColour, 1, -1, 1 - 0.2, 2, 0.2);  // Right Outline
	}

	void drawBoxToWorld(cv::Mat &img, cv::Scalar col, int thick, double x1, double y1, double w, double h) {
		cv::line(img, toWorld(x1, y1), toWorld(x1 + w, y1), col, thick);
		cv::line(img, toWorld(x1 + w, y1), toWorld(x1 + w, y1 + h), col, thick);
		cv::line(img, toWorld(x1 + w, y1 + h), toWorld(x1, y1 + h), col, thick);
		cv::line(img, toWorld(x1, y1 + h), toWorld(x1, y1), col, thick);
	}

	double linear(double left, double right) {
		return (right + left);
	}

	double angular(double left, double right) {
		return -(right - left);
	}

	cv::Point toWorld(double x, double y) {
		// cv::Point origin{ SimData::Window::Width / 2, SimData::Window::Height / 2 };
		cv::Point origin{ (int)SimData::Robot::start_x, (int)SimData::Robot::start_y };
		cv::Point robot{ static_cast<int>(50 * (_x + x * cos(_heading) - y * sin(_heading))),
										 static_cast<int>(50 * (_y + x * sin(_heading) + y * cos(_heading))) };

		return origin + robot;
	}


 private:
	Window &_window;
	double _x, _y, _angle, _heading = -3.14/2; // Positional data
};

#endif