#include "Sim.h"
#include "robot/Drivetrain.h"
#include "Trajectory.h"

static constexpr double fieldRotation = 35.6;

static double covnert2Meters(double rotations) {
  double rots2Meter = (fieldRotation/16);
  return rotations/rots2Meter;
}

Motor left{0}, right{2};
Encoder leftEnc{0}, rightEnc{1};

// Using trajectory util to generate trajectory
Trajectory<Splines::CatmullRom> myTrajectory;

/**
 * Initializer (Updates once)
 */
void Sim::Init() {
  myTrajectory.push_back({
    {0,4}, {1,4}, {4,6}, {8,6}, {10,6}, {9,5},
    {1,5}, {0,0}
    // {0,4}, {1,4}, {2,4}, {3,4}
  });

  myTrajectory.build();
}

/**
 * Periodic Update
 */
void Sim::Periodic() {
  double averageEncoder = (leftEnc.getRotations() + rightEnc.getRotations())/2;
  double distance = covnert2Meters(averageEncoder);

  double leftPower = 0;
  double rightPower = 0;

  if (distance < myTrajectory.getRawTrajectory().totalLength) {
    leftPower = 0.15;
    rightPower = 0.15;
    double robotGyro = World::getGyro(0); // input
    double goalAngle = myTrajectory.getAngle(distance); // goal

    if (myTrajectory.atWaypoint(1, distance)) {
      std::cout << "At waypoint: " << 1 << std::endl;
    }

    /**
     * Used for wrapping around a range. E.g, if current angle is 175 and goal is -180. Both 180 and -180 are the same.
     * So don't spin the robot all the way around. instead just go to 180 degrees
     */
    double angleError = myTrajectory.wrap(goalAngle-robotGyro, 180); // (value = error, range = 180)
    angleError /= 180;

    leftPower += angleError;
    rightPower -= angleError;
  }




  left.set(leftPower);
  right.set(rightPower);

  std::cout << distance << std::endl;
}