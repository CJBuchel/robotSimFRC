#include "Sim.h"

#include "robot/Motor.h"
#include "robot/Encoder.h"
#include "robot/Drivetrain.h"

#include "Trajectory.h"

double rotsPerMeter = 7.375;

// Robot
Motor left1{0}, left2{1}, right1{2}, right2{3};
Encoder leftEnc{0}, rightEnc{1};
Gearbox leftGearbox{{&left1, &left2}, &leftEnc};
Gearbox rightGearbox{{&right1, &right2}, &rightEnc};

DrivetrainConfig config{leftGearbox, rightGearbox};
Drivetrain drivetrain{config};

Trajectory<Splines::CatmullRom> trajectory({
  {0,4},{1,4},{6,5},{8,5}, // get to center
  
  {10,4},{12,4},{11,5.5},{8,5}, // curve around pole

  {1,4}, {0,4} // back to start
});

double wrap(double val, double range = 0) {
  if (range > 0) {
    val = std::fmod(val, range);
    if (std::abs(val) > (range/2.0)) {
      return (val > 0) ? val - range : val + range;
    }
  }

  return val;
}

/**
 * Initializer (Updates once)
 */
void Sim::Init() {
  trajectory.build();
}

/**
 * Periodic Update
 */
void Sim::Periodic() {
  double leftPower = 0, rightPower = 0;
  double averageDistance = ((leftEnc.getRotations()/rotsPerMeter) + (rightEnc.getRotations()/rotsPerMeter))/2;
  // std::cout << averageDistance << std::endl;

  if (averageDistance < trajectory.getRawTrajectory().totalLength) {
    leftPower = 0.25;
    rightPower = 0.25;

    double angleError = wrap(trajectory.getAngle(averageDistance) - World::getGyro(0), 180) / 180;
    std::cout << "Distance: " << averageDistance << ", Gyro Goal: " << trajectory.getAngle(averageDistance) << std::endl; 

    leftPower += angleError;
    rightPower -= angleError;
  }

  drivetrain.set(leftPower, rightPower);
}