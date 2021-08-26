#include "headers.h"
#include "world/World.h"
#include "visuals/Window.h"

class Sim {
 public:
	Sim(Window &window) : _window(window) {}

	void Init();
	void Periodic();

	Window &getWindow() { return _window; }

 private:
	Window &_window;
};