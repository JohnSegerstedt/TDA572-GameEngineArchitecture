#pragma once

#include "subject.h"

void Subject::addObserver(Observer* observer) {
	observers[numObservers++] = observer;
}
void Subject::removeObserver(Observer* observer) {
	int indexToRemove = -1;
	for (int i = 0; i < numObservers - 1; ++i) if (observers[i] == observer) indexToRemove = i;
	if (indexToRemove == -1) std::cout << "ERROR - Trying to remove non-existing Observer";
	for (int i = indexToRemove; i < numObservers; ++i) observers[i] = observers[i + 1];
}

void Subject::notify(Binding binding) {
	for (int i = 0; i < numObservers; i++) {
		observers[i]->onNotify(binding);
	}
}
