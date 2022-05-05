#pragma once

#include "Subject.h"
#include <iostream>

class RealSubject :
	public Subject {
public:
	void Request() const override {
		std::cout << "RealSubject: Handling request.\n";
	}
};

