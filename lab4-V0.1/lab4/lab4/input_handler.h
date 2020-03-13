#pragma once

#include "bindings.h"
#include "subject.h"

/*
inputHandler:
- Listens for key presses and checks vs. bindings
- Is a Subject for systems listening for bindings
*/

class InputHandler : public Subject {

private:
	InputHandler();
	void initialize();

public:
	static InputHandler* getInstance();
	void update();
	bool getPressed(Binding binding);
	bool handleInput();
};

