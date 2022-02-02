#ifndef SPLINES_H
#define SPLINES_H

#include <vector>
#include <math.h>

#ifdef __linux__ 
  #include <bits/stdc++.h>
#elif _WIN32
  #include <iomanip>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

#ifndef STRINGIFY
#define STRINGIFY(x) #x
#endif

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

static void printProgress(double percentage) {
  int val = (int) (percentage * 100);
  int lpad = (int) (percentage * PBWIDTH);
  int rpad = PBWIDTH - lpad;
  printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
  fflush(stdout);
}

namespace Splines {
  struct Waypoint {
    double x = 0, y = 0; // you'd be surprised how much this breaks if it's not long double...
    double segLength = 0; // length of segment
    double totalLength = 0; // length of everything up to and including this segment
  };

  struct SplinePoint {
    Waypoint waypoint;
    int flag;
  };

  struct Spline {
    std::vector<Waypoint> points;
    double totalLength = 0;
    int segmentNum = 0;
  };

  namespace Util {
    /**
     * Convert Radians to Degrees
     */
    static double r2d(double rad) {
      return (rad * 180 / M_PI);
    }

    /**
     * Convert degrees to radians
     */
    static double d2r(double deg) {
      return (deg * M_PI / 180);
    }
  };

  /**
   * Virtual Spline Base with common functions for splines
   */
  class SplineBase {
   public:
    SplineBase() {
      _stepSize = 0.0001;
    }
    /**
     * Get the spline point from t value and spline
     * Returns waypoint and flag
     */
    virtual SplinePoint getSplinePoint(float t, Spline spline) { return {{0,0},0}; };

    /**
     * Get gradient point from t value and spline
     */
    virtual SplinePoint getSplineGradientPoint(float t, Spline spline) { return {{0,0},0}; };

    /**
     * Get angle in radians based from t value and spline
     * returns waypoint and flag
     */
    virtual double getSplineAngleRad(float t, Spline spline) {
      SplinePoint gradientPoint = getSplineGradientPoint(t, spline);
      if (gradientPoint.flag != -1) {
        return atan2(gradientPoint.waypoint.y, gradientPoint.waypoint.x);
      } else {
        return 0;
      }
    }

    /**
     * Get angle in degrees based from t value and spline
     */
    virtual double getSplineAngleDeg(double t, Spline spline) {
      return Util::r2d(getSplineAngleRad(t, spline));
    }

    /**
     * Calculate the length of a segment, using the node (int) and spline
     */
    virtual double calculateSegLength(int node, Spline spline) {
      double segLength = 0;
      SplinePoint oldPoint, newPoint;
      oldPoint = getSplinePoint((float)node, spline);

      std::cout << "[Node " << node << "-" << node+1 << "]" << std::endl;
      for (double t = 0.0; t < 1.0; t += _stepSize) {
        newPoint = getSplinePoint((float)node + t, spline);

        // 1 means end of spline so return
        if (newPoint.flag != 0 || oldPoint.flag != 0) {
          printProgress(1);
          std::cout << " Complete" << std::endl;
          return segLength;
        }

        double xrt = (newPoint.waypoint.x - oldPoint.waypoint.x)*(newPoint.waypoint.x - oldPoint.waypoint.x);
        double yrt = (newPoint.waypoint.y - oldPoint.waypoint.y)*(newPoint.waypoint.y - oldPoint.waypoint.y);
        double xyrt = (xrt+yrt);
        
        double bufferLength = 0;

        if (xyrt > 0) {
          bufferLength = sqrt(xyrt);
          if (isinf(bufferLength) || isnan(bufferLength)) {
            bufferLength = 0;
            std::cout << " -- Overflow detected, Debug Below -- " << std::endl;
            std::cout << "| New points x,y: (" << (double)newPoint.waypoint.x << "," << (double)newPoint.waypoint.y << ")" << std::endl;
            std::cout << "| Old points x,y: (" << oldPoint.waypoint.x << "," << oldPoint.waypoint.y << ")" << std::endl;
            std::cout << "| t value: " << t << std::endl;
            std::cout << "| XY rt was xrt: (" << xrt << ") & yrt: (" << yrt << ")" << std::endl;
            return -1;
          }
        } else {
          bufferLength = 0;
        }

        segLength += bufferLength;
        oldPoint = newPoint;
        printProgress(t);
      }

      return segLength;
    }

    /**
     * Calculate length of spline,
     * use remove nodes to increase the nodes to remove, (0 being none, 1 being 1 at the start and 1 at the end)
     * Used mostly for control points at the start and end of spline, (CatmullRom)
     * 
     * returns -1 if error
     */
    virtual int calculateSpline(Spline &spline, int removeNodes = 0) {
      int nodeNum = spline.points.size();
      std::cout << "-- Calculating Length of spline --" << std::endl;
      std::cout << "-- Total Nodes: " << nodeNum << std::endl;
      for (size_t node = removeNodes; node < nodeNum - removeNodes; node++) {
        double segLength = calculateSegLength(node, spline);
        if (segLength == -1) {
          std::cout << "Segment Length Error" << std::endl;
          return -1;
        } else {

          spline.points[node].segLength = segLength;
          spline.totalLength += segLength;
          spline.points[node].totalLength = spline.totalLength;
          if (spline.points[node].segLength > 0) {
            spline.segmentNum++;
            std::cout << "Segment " << node << "-" << node+1 << ", Length: " << spline.points[node].segLength << ", Length up to and including: " << spline.points[node].totalLength << std::endl; 
          }
        }
      }

      std::cout << "Number of segments: " << spline.segmentNum << std::endl;

      return 0;
    }

    /**
     * @brief Get the t value through a spline based on distance
     * 
     * @param distanceMeters 
     * @param spline 
     * @return double 
     */
    static double getDist2t(double distanceMeters, Splines::Spline spline) {
      int segmentNum = 0;

      // Determin segment number
      while (distanceMeters > spline.points[segmentNum].totalLength) {
        segmentNum++;
      }

      double distAlongSegment = 0;
      if (segmentNum != 0) {
        distAlongSegment = distanceMeters - spline.points[segmentNum-1].totalLength;
      } else {
        distAlongSegment = distanceMeters;
      }

      // scaledNum = ((x-a)*(d-c)/(b-a))+c
      // Redundant because it's range 0-segLength to 0-1 but it makes sense drawn out.
      double oldRange = (spline.points[segmentNum].segLength - 0);
      double newRange = (1 - 0);
      double t = (((distAlongSegment - 0) * newRange) / oldRange) + 0;

      return t+segmentNum;
    }

    void setStepSize(double step) {
      _stepSize = step;
    }

   private:
    double _stepSize = 0.0001;
  };
}

#endif