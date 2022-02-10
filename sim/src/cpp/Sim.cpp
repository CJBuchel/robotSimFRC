#include "Sim.h"
#include "robot/Drivetrain.h"
#include "TrajectoryUtilities.h"

static constexpr double fieldRotation = 126.3;

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
    {1,4}, {0,0}
    // {0,4}, {1,4}, {8,4}, {9,4}
  });

  myTrajectory.build();
}

PID::PIDGains travelGains{ "Traveling Gains", 0.1, 0, 0 };
PID::PIDGains angleGains{ "Angling Gains", 0.17, 0, 0 };

PID::PIDController travelController{ travelGains };
PID::PIDController anglingController{ angleGains };

/**
 * Periodic Update
 */
void Sim::Periodic() {
  double averageEncoder = (leftEnc.getRotations() + rightEnc.getRotations())/2;
  double distance = covnert2Meters(averageEncoder);
  double robotGyro = World::getGyro(0); // input
  

  double leftPower = 0;
  double rightPower = 0;

  // if (distance < myTrajectory.getRawTrajectory().totalLength) {
  //   leftPower = 0.15;
  //   rightPower = 0.15;
  //   double robotGyro = World::getGyro(0); // input
  //   double goalAngle = myTrajectory.getAngle(distance); // goal

  //   /**
  //    * Used for wrapping around a range. E.g, if current angle is 175 and goal is -180. Both 180 and -180 are the same.
  //    * So don't spin the robot all the way around. instead just go to 180 degrees
  //    */
  //   double angleError = myTrajectory.wrap(goalAngle-robotGyro, 180); // (value = error, range = 180)
  //   angleError /= 180;

  //   leftPower += angleError;
  //   rightPower -= angleError;
  // }


  if (!myTrajectory.atWaypoint(myTrajectory.getRawTrajectory().points.size()-2, distance)) {
    double targetDistance = myTrajectory.getRawTrajectory().totalLength; // total distance to travel/target
    double targetAngle = myTrajectory.getAngle(distance);

    travelController.setSetpoint(targetDistance);
    anglingController.setSetpoint(targetAngle);
    anglingController.setWrap(180);

    double travelOutput = travelController.calculate(distance, Config::Sim::getGlobalDT());
    double angleOutput = anglingController.calculate(robotGyro, Config::Sim::getGlobalDT());
    leftPower = travelOutput + angleOutput;
    rightPower = travelOutput - angleOutput;
    std::cout << "Distance traveled: " << distance << ", Target Angle: " << targetAngle << ", Current Angle: " << robotGyro << std::endl;
  }

  // std::cout << "Distance: " << averageEncoder << std::endl;
  // leftPower = 0.15;
  // rightPower = 0.15;
  left.set(leftPower);
  right.set(rightPower);
}