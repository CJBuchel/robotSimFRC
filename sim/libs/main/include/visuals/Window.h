#ifndef WINDOW_H
#define WINDOW_H

#include "headers.h"
#include "Draw.h"

/**
 * README
 * 
 * Display results by drawing in between PRE and POST window update and reset afterwards
 * 
 * 
 */
class Window : public Draw {
 public:
	Window(double height = 800, double width = 1600, std::string name = "");

	/**
	 * prep for all functions to draw on top
	 */
	void window_SIM_PRE_Update();

	/**
	 * post update after funcitons have drawn on top. (display results)
	 */
	void window_SIM_POST_Update();

	/**
	 * Get Window
	 */
	cv::Mat &getWindow() { return this->_window; }

	/**
	 * get width
	 */
	double getWidth() {
		return this->_width;
	}

	/**
	 * get height
	 */
	double getHeight() {
		return this->_height;
	}

 private:

	/**
	 * Reset image
	 */
	void reset();

	cv::Mat _background; // Background image
	cv::Mat _window; // Main window displayed after adding background and drawings
	
	std::string _name;
	double _height, _width;
};

#endif