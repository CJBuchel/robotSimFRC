#include "headers.h"
#include "visuals/Window.h"
#include "SimData.h"

class Sim {
 public:
	Sim() {
		window = new Window(simData.window.Height, simData.window.Width, simData.window.name);
	}

	~Sim() {
		free(window);
	}


	void Init();
	void OnUpdate();

	SimData &getSimData() { return simData; }
	Window *getWindow() { return window; }

 private:
	// DONT TOUCH (MAIN WINDOW)
	SimData simData;
	Window *window;
};