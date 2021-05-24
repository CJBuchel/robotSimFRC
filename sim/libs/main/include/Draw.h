#include "headers.h"

class Draw {
 public:
	struct dw_point {
		double x,y;
	};

	struct RGB {
		int R,G,B; // Should be between 0-255
	};

	Draw(cv::Mat &img) : _img(img) {
		std::cout << "Drawing controller built" << std::endl;
	}

	void drawLine(dw_point start, dw_point end, RGB rgb = {255,255,255}, int thickness = 2, int lineType = cv::LINE_8) {
		cv::line(this->_img, cv::Point(start.x, start.y), cv::Point(end.x, end.y), cv::Scalar(rgb.B, rgb.G, rgb.R), thickness, lineType);
	}

	void drawRect(dw_point centerCoord, int width, int height, double angle) {
		cv::RotatedRect rect = cv::RotatedRect(cv::Point2f(centerCoord.x, centerCoord.y), cv::Size2f(width, height), angle);
		cv::Point2f vertices[4];
		rect.points(vertices);
		for (int i = 0; i < 4; i++) {
			drawLine(
				{vertices[i].x, vertices[i].y}, 
				{vertices[(i+1)%4].x, vertices[(i+1)%4].y}
			);
		}
		// cv::rectangle(this->_img, cv::Point(tl.x, tl.y), cv::Point(br.x, br.y), cv::Scalar(255,255,255));
	}

 private:
	cv::Mat &_img;
};