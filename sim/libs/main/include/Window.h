#ifndef WINDOW_H
#define WINDOW_H

#include "headers.h"
#include "Draw.h"

class Window : public Draw {
 public:
	Window(double height = 800, double width = 1600, std::string name = "");

	/**
	 * Update image
	 */
	void update();

	/**
	 * Reset image
	 */
	void reset();

	/**
	 * Get Window
	 */
	cv::Mat &getWindow() { return this->_window; }

 private:
	cv::Mat _window; // Main window
	std::string _name;
	double _height, _width;
};

#endif