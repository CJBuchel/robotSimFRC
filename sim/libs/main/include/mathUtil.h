#ifndef MATHUTIL_H
#define MATHUTIL_H

#define PREC_PI 3.14159265358979323846264338327

namespace mathUtil {

	static double r2d(double radians) {
		return (radians*180/PREC_PI);
	}

	static double d2r(double degrees) {
		return (degrees*PREC_PI/180);
	}
};

#endif