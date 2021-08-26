#include "Sim.h"

/**
 * Initializer (Happens once)
 */
void Sim::Init() {

}

/**
 * Periodic Update
 */
void Sim::OnUpdate() {
	World::setMotor(0, 0.5);
}