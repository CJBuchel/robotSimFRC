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

	void drawRect(dw_point centerCoord, int width, int height, double angle, RGB rgb = {255,255,255}) {
		cv::RotatedRect rect = cv::RotatedRect(cv::Point2f(centerCoord.x, centerCoord.y), cv::Size2f(width, height), angle);
		cv::Point2f vertices[4];
		rect.points(vertices);
		for (int i = 0; i < 4; i++) {
			drawLine(
				{vertices[i].x, vertices[i].y},
				{vertices[(i+1)%4].x, vertices[(i+1)%4].y},
				rgb
			);
		}
	}

	void drawText(std::string info, dw_point pos, int size = 1, RGB rgb = {255,255,255}, bool background = false, RGB backRGB = {0,0,0}) {
		cv::putText(
			this->_img,
			info,
			cv::Point(pos.x, pos.y),
			cv::FONT_HERSHEY_PLAIN,
			size,
			cv::Scalar(rgb.B, rgb.G, rgb.R),
			1
		);
	}

	void drawInfoLabel(std::string info) {
		cv::Point loc(10,15*infoCount);

		int fontface = cv::FONT_HERSHEY_SIMPLEX;
		double scale = 0.5;
		int thickness = 1;
		int baseline = 0;

		cv::Size text = cv::getTextSize(info, fontface, scale, thickness, &baseline);
		cv::rectangle(this->_img, loc + cv::Point(0, baseline), loc + cv::Point(text.width, -text.height), CV_RGB(0,0,0), -1, cv::LINE_8);
		cv::putText(this->_img, info, loc, fontface, scale, CV_RGB(255,255,255), thickness, 8);

		infoCount++;
	}

	void drawInfoText(std::string info) {

		cv::putText(
			this->_img,
			info,
			cv::Point(10,15*infoCount),
			cv::FONT_HERSHEY_PLAIN,
			1,
			cv::Scalar(50,50,255),
			1
		);

		infoCount++;
	}

	void resetInfoCounter() { infoCount = 1; }

 private:
	cv::Mat &_img;
	int infoCount = 1; // Number of text drawn in top left
};