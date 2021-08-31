#include "world/World.h"
#include "robot/Encoder.h"

double Encoder::getRawTicks() {
	return World::getEnc(_port);
}

double Encoder::getRotations() {
	return World::getEnc(_port)/_ticksPerRotation;
}