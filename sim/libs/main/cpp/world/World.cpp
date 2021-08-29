// Compile all world headers

#include "world/World.h"
#include "world/Robot.h"


// Initialize the static world members
std::vector<double> World::motors;
std::vector<double> World::encoders;
std::vector<double> World::gyros;