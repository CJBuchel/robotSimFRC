#include "Sim.h"

double angle; // angle of rectangle
int count;

/**
 * Initializer (Happens once)
 */
void Sim::Init() {
	angle = 0;
}

/**
 * Periodic Update
 */
void Sim::OnUpdate() {
	getWindow().drawRect({400,800}, 100, 100, angle);
	angle++;
}