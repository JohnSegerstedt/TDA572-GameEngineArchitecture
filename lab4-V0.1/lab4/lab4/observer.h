#pragma once

#include "bindings.h"


class Observer {
public:
	virtual ~Observer() {}
	virtual void onNotify(Binding binding) = 0;
};

