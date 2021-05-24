#include "Sim.h"

double angle; // angle of rectangle
int count;

/**
 * Initializer (Happens once)
 */
void Sim::Init() {
	simData.window.FPS = 500; // Unlockes FPS
	angle = 0;
}

/**
 * Periodic Update
 */
void Sim::OnUpdate() {
	window->drawRect({400,800}, 100, 100, angle);
	angle++;
}