#include "Window.h"

Window::Window(double height, double width, std::string name) : Draw(_window) {
	this->_height = height;
	this->_width = width;
	this->_window = cv::Mat::zeros(this->_height, this->_width, CV_8UC3);
	this->_name = name;
}

void Window::update() {
	cv::imshow(this->_name, this->_window);
}

void Window::reset() {
	this->_window = cv::Mat::zeros(this->_height, this->_width, CV_8UC3);
	resetInfoCounter();
}