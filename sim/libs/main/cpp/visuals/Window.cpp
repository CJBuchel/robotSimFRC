#include "visuals/Window.h"

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
	if (SimData::Window::field == 0) {
		this->_window = cv::Mat::zeros(this->_height, this->_width, CV_8UC3);
	} else {
		std::string year = std::to_string(SimData::Window::field);
		this->_window = cv::imread(year + ".png", cv::IMREAD_COLOR);
		cv::resize(this->_window, this->_window, cv::Size(this->_width, this->_height));
	}
	resetInfoCounter();
}