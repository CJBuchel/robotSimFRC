#include "Sim.h"
#include "robot/Drivetrain.h"
#include "TrajectoryUtilities.h"

// static constexpr double fieldRotation = 126.3;
static constexpr double fieldRotation = 72;

static double covnert2Meters(double rotations) {
  double rots2Meter = (fieldRotation/16);
  return (rotations/rots2Meter);
}

Motor left{0}, right{2};
Encoder leftEnc{0}, rightEnc{1};

// Using trajectory util to generate trajectory
Trajectory<Splines::CatmullRom> myTrajectory;
ControlTheory mp_movement{ 0.5, 0.04 };

/**
 * Initializer (Updates once)
 */
void Sim::Init() {
  myTrajectory.push_back({
    // {0,4}, {1,4}, {4,6}, {8,6}, {10,6}, {9,5},
    // {1,4}, {0,0}
    {0,4}, {1,4}, {8,4}, {9,4}
  });

  myTrajectory.build();

  mp_movement.createTarget(ControlTheory::Target("Linear Target", myTrajectory.getRawTrajectory().totalLength, {"Linear Gains", 0.1, 0, 0}));
  // mp_movement.createTarget(); // turning

  mp_movement.start();
}

/**
 * Periodic Update
 */
void Sim::Periodic() {
  double averageEncoder = (leftEnc.getRotations() + rightEnc.getRotations())/2;
  double distance = covnert2Meters(averageEncoder);
  double robotGyro = World::getGyro(0);

  double leftPower = 0;
  double rightPower = 0;

  mp_movement.getTarget(0).setCurrentPosition(distance);
  mp_movement.update(Config::Sim::getGlobalDT());
  double linearOutput = mp_movement.getTarget(0).getOutput();
  
  std::cout << "Distance: " << distance << std::endl;
  std::cout << "Goal: " << myTrajectory.getRawTrajectory().totalLength << std::endl;


  leftPower += linearOutput;
  rightPower += linearOutput;

  // std::cout << "Distance: " << distance << std::endl;
  left.set(leftPower);
  right.set(rightPower);
}