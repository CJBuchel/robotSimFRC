#ifndef ROBOT_H
#define ROBOT_H

#include "World.h"
#include "visuals/Window.h"
#include <iomanip>

// Colour values
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
		_x = 0; // temp
		_y = 0; // temp
		_heading = mathUtil::d2r(Config::Robot::start_angle);
		update(); // Initial draw
	}

	void reset() {
		_x = 0;
		_y = 0;
		_heading = mathUtil::d2r(Config::Robot::start_angle);
		_currentLeftSpeed = 0;
		_currentRightSpeed = 0;
		_time = 0;
		_leftRotations = 0;
		_rightRotations = 0;
	}

	void collisionCheck() {

		// x reset
		if (_worldX < 0 || _worldX > _window.getWidth()) {
			reset();
		}

		// y reset
		if (_worldY < 0 || _worldY > _window.getHeight()) {
			reset();
		}
	}

	// Return speed + value for certain acceleration (0.2m/s)
	double acceleratedPower(double speed, double targetSpeed) {
		if (fabs(speed) >= fabs(targetSpeed)) {
			return targetSpeed;
		} else {
			if (targetSpeed < 0) {
				return (speed-(Config::Robot::maxAcceleration/_cps));
			} else if (targetSpeed > 0) {
				return (speed+(Config::Robot::maxAcceleration/_cps));
			} else {
				return 0;
			}
		}
	}

	double maxSpeedPowerCheck(double speed) {
		if (fabs(speed) >= Config::Robot::maxSpeed) {
			return speed > 0 ? Config::Robot::maxSpeed : -Config::Robot::maxSpeed;
		} else {
			return speed;
		}
	}

	void update() {
		if (Config::Keyboard::getKey() == 114) { // r
			reset();
		}

		double left = 0;
		double right = 0;

		_time += Config::Sim::getGlobalDT();
		Config::Sim::setGlobalTimeStamp(_time);
		_window.drawInfoLabel("Time Stamp: " + std::to_string(_time));

		collisionCheck(); // reset if collide

		// Update cps
		if (Config::Sim::getGlobalCPS() > 0) {
			_cps = Config::Sim::getGlobalCPS();
		}

		// get motors and average the power
		left += World::getMotor(Config::Robot::leftMPort[0]);
		left += World::getMotor(Config::Robot::leftMPort[1]);

		right += World::getMotor(Config::Robot::rightMPort[0]);
		right += World::getMotor(Config::Robot::rightMPort[1]);

		// average out speed based on how many motors are used
		left /= Config::World::motorPorts/2;
		right /= Config::World::motorPorts/2;

		// target speed in meters per second
		double targetLeftSpeed = left * Config::Robot::maxSpeed;
		double targetRightSpeed = right * Config::Robot::maxSpeed;

		// Add acceleration into equation
		_currentLeftSpeed = acceleratedPower(_currentLeftSpeed, targetLeftSpeed);
		_currentRightSpeed = acceleratedPower(_currentRightSpeed, targetRightSpeed);

		// check if it's going over maximum speed
		_currentLeftSpeed = maxSpeedPowerCheck(_currentLeftSpeed);
		_currentRightSpeed = maxSpeedPowerCheck(_currentRightSpeed);

		// Encoder feedback
		_leftRotations += (_currentLeftSpeed/0.1524)/_cps;
		_rightRotations += (_currentRightSpeed/0.1524)/_cps;

		// Set encoders
		World::setEnc(Config::Robot::leftEncPort, (_leftRotations*Config::Robot::ticksPerRotation));
		World::setEnc(Config::Robot::rightEncPort, (_rightRotations*Config::Robot::ticksPerRotation));

		// Speed in pixels per cycle
		double currentLeftSpeedP = (_currentLeftSpeed*250)/_cps;
		double currentRightSpeedP = (_currentRightSpeed*250)/_cps;

		// Angle/linear movement
		double ang = angular(currentLeftSpeedP, currentRightSpeedP);
		double lin = linear(currentLeftSpeedP, currentRightSpeedP);

		_heading += ang * Config::Sim::getGlobalDT();
		_angle = mathUtil::r2d(_heading);
		World::setGyro(Config::Robot::gyroPort, _angle);

		_x += lin * Config::Sim::getGlobalDT() * cos(_heading);
		_y += lin * Config::Sim::getGlobalDT() * sin(_heading);

		// Actual x and y of robot in the world
		_worldX = toWorld(0,0).x;
		_worldY = toWorld(0,0).y;

		drawRobot(_window.getWindow(), currentLeftSpeedP, currentRightSpeedP);
	}

	void drawRobot(cv::Mat &img, double l, double r) {
		cv::circle(img, toWorld(0,0), 2, cv::Scalar(255,255,255), -1);
		_window.drawText("rel x: " + std::to_string(_x) + ", rel y: " + std::to_string(_y), {500, 525});
		_window.drawText("rel x: " + std::to_string(_worldX) + ", rel y: " + std::to_string(_worldY), {500, 550});
		_window.drawText("LeftEncoder: " + std::to_string(_leftRotations) + ", RightEncoder: " + std::to_string(_rightRotations), {500, 575});
		_window.drawText("Gyro: " + std::to_string(_angle), {500, 600});

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
		cv::Point origin{ (int)Config::Robot::start_x, (int)Config::Robot::start_y };
		cv::Point robot{ static_cast<int>(50 * (_x + x * cos(_heading) - y * sin(_heading))),
										 static_cast<int>(50 * (_y + x * sin(_heading) + y * cos(_heading))) };

		return origin + robot;
	}


 private:
	Window &_window;
	double _x, _y, _angle, _heading = -3.14/2; // Positional data
	double _worldX, _worldY;
	double _leftRotations = 0, _rightRotations = 0;

	double _currentLeftSpeed = 0, _currentRightSpeed = 0; // speed in meters per second
	int _cps = 250;
	double _time = 0;
};

#endif