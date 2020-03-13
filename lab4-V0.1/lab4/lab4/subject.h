#pragma once

#include "observer.h"
#include "bindings.h"
#include <iostream>


#define MAX_OBSERVERS 10

class Subject {

private:
	Observer* observers[MAX_OBSERVERS];
	int numObservers = 0;

public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

protected:
	void notify(Binding binding);

};


