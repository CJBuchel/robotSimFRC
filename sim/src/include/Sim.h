#include "headers.h"
#include "Window.h"
#include "Config.h"

class Sim {
 public:
	Sim() {
		window = new Window(config.window.Height, config.window.Width, config.window.name);
	}

	~Sim() {
		free(window);
	}


	void Init();
	void OnUpdate();

	// DONT TOUCH (MAIN WINDOW)
	Config config;
	Window *window;
};