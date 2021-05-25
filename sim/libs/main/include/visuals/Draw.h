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
		cv::RotatedRect rect = cv::RotatedRect(cv::Point2f(centerCoord.y, centerCoord.x), cv::Size2f(width, height), angle);
		cv::Point2f vertices[4];
		rect.points(vertices);
		for (int i = 0; i < 4; i++) {
			drawLine(
				{vertices[i].x, vertices[i].y},
				{vertices[(i+1)%4].x, vertices[(i+1)%4].y}
			);
		}
	}

	void drawInfoText(std::string info) {

		cv::putText(
			this->_img,
			info,
			cv::Point(10,15*infoCount),
			cv::FONT_HERSHEY_PLAIN,
			1,
			cv::Scalar(255,255,255),
			1
		);

		infoCount++;
	}

	void resetInfoCounter() { infoCount = 1; }

 private:
	cv::Mat &_img;
	int infoCount = 1; // Number of text drawn in top left
};