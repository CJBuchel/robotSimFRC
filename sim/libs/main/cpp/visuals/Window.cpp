#include "visuals/Window.h"

Window::Window(double height, double width, std::string name) : Draw(_window) {
	this->_height = height;
	this->_width = width;
	this->_window = cv::Mat::zeros(this->_height, this->_width, CV_8UC3);
	
	if (SimData::Window::field == 0) {
		this->_background = cv::Mat::zeros(this->_height, this->_width, CV_8UC3);
	} else {
		std::string year = std::to_string(SimData::Window::field);
		this->_background = cv::imread(year + ".png", cv::IMREAD_COLOR);
		cv::resize(this->_background, this->_background, cv::Size(this->_width, this->_height));
	}


	this->_name = name;
}

void Window::update() {
	cv::addWeighted(this->_background, 1, this->_window, 1, 0.0, _output);
	cv::imshow(this->_name, this->_output);
}

void Window::reset() {
	this->_window = cv::Mat::zeros(this->_height, this->_width, CV_8UC3);
	resetInfoCounter();
}