#ifndef CATMULLROM_H
#define CATMULLROM_H

#include "Splines.h"

namespace Splines {
  class CatmullRom : public SplineBase {
   public:
    SplinePoint getSplinePoint(float t, Spline spline) override {
      int flag = 0;

      int p0, p1, p2, p3;

      p1 = (int)t + 1;
      p2 = p1 + 1;
      p3 = p2 + 1;
      p0 = p1 - 1;

      if (p3 >= spline.points.size()) {
        return {{0,0}, 1};
      }

      t = t - (int)t;

      float tt = t * t;
      float ttt = tt * t;

      float q1 = -ttt + 2.0f*tt - t;
      float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
      float q3 = -3.0f*ttt + 4.0f*tt + t;
      float q4 = ttt - tt;

      float tx = 0.5f * (spline.points[p0].x * q1 + spline.points[p1].x * q2 + spline.points[p2].x * q3 + spline.points[p3].x * q4);
      float ty = 0.5f * (spline.points[p0].y * q1 + spline.points[p1].y * q2 + spline.points[p2].y * q3 + spline.points[p3].y * q4);

      return{ {tx,ty}, flag };
    }

    SplinePoint getSplineGradientPoint(float t, Spline spline) override {
      int flag = 0;

      int p0, p1, p2, p3;
      p1 = (int)t + 1;
      p2 = p1 + 1;
      p3 = p2 + 1;
      p0 = p1 - 1;

      t = t - (int)t;

      float tt = t * t;

      float q1 = -3.0f * tt + 4.0f*t - 1;
      float q2 = 9.0f*tt - 10.0f*t;
      float q3 = -9.0f*tt + 8.0f*t + 1.0f;
      float q4 = 3.0f*tt - 2.0f*t;

      float tx = 0.5f * (spline.points[p0].x * q1 + spline.points[p1].x * q2 + spline.points[p2].x * q3 + spline.points[p3].x * q4);
      float ty = 0.5f * (spline.points[p0].y * q1 + spline.points[p1].y * q2 + spline.points[p2].y * q3 + spline.points[p3].y * q4);

      return { {tx,ty}, flag };
    }
  };
};

#endif