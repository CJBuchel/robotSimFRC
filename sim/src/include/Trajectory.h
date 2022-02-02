#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "Splines/CatmullRom.h"

template<typename SplineType>
class Trajectory {
 public:

  Trajectory(std::string name = "<Trajectory>") : _name(name) {}
  Trajectory(std::vector<Splines::Waypoint> waypoints, std::string name = "<Trajectory>") : _name(name) {
    _trajectory.points = waypoints;
  }

  void push_back(Splines::Waypoint waypoint) {
    _trajectory.points.push_back(waypoint);
  }

  void push_back(std::vector<Splines::Waypoint> waypoints) {
    for (auto point : waypoints) {
      push_back(point);
    }
  }

  void pop_back() {
    _trajectory.points.pop_back();
  }

  void build(double stepSize = 0.0001) {
    _sType.setStepSize(stepSize);
    if (_sType.calculateSpline(_trajectory) == -1) {
      std::cout << "Error while calculating spline in " << _name << std::endl;
    }
  }

  /**
   * @brief Get the Angle along the spline using distance traveled
   * 
   * @param dist 
   * @param rads 
   * @return double 
   */
  double getAngle(double dist, bool rads = false) {
    double t = _sType.getDist2t(dist, _trajectory);
    if (rads) {
      return _sType.getSplineAngleRad(t, _trajectory);
    } else {
      return _sType.getSplineAngleDeg(t, _trajectory);
    }
  }

  /**
   * @brief Get the Coords along the spline using distance traveled
   * 
   * @param dist 
   * @return Splines::Waypoint 
   */
  Splines::Waypoint getCoords(double dist) {
    double t = _sType.getDist2t(dist, _trajectory);
    return _sType.getSplinePoint(t, _trajectory);
  }

  Splines::Spline &getRawTrajectory() { 
    return _trajectory; 
  }

  SplineType getType() {
    return _sType;
  }

  void print() {
    std::cout << "-- Trajectory: " << _name << " --" << std::endl;
    std::cout << "|  Type: " << typeid(SplineType).name() << std::endl;
    std::cout << "   |  N Points: " << _trajectory.points.size() << std::endl;
    std::cout << "   |  Coords: ";
    for (auto point : _trajectory.points) {
      std::cout << "{" << point.x << "," << point.y << "}, ";
    }
    std::cout << std::endl;

    std::cout << "   |  Segments: " << _trajectory.segmentNum << std::endl;
    std::cout << "   |  Length: " << _trajectory.totalLength << std::endl;
  }


  void simulate(double distanceStepSize = 0.1) {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "-- Simulating Moving Along Trajectory " << _name << " -- " << std::endl;
    for (double step = 0; step < _trajectory.totalLength; step += distanceStepSize) {
      Splines::Waypoint position = getCoords(step);
      double angle = getAngle(step);
      std::cout << "Distance: " << step << " | ";
      std::cout << "Coords: {" << position.x << "," << position.y << "} | ";
      std::cout << "Angle: " << angle << std::endl;
    }
  }

 private:
  Splines::Spline _trajectory;
  SplineType _sType;

  std::string _name;
};

#endif