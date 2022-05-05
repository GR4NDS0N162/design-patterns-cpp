#pragma once

#include "Subject.h"
#include <iostream>

/// <summary>
/// <para>
/// Реальный субъект:
/// </para>
/// <para>
/// - содержит полезную бизнес-логику.
/// </para>
/// <para>
/// - определяет реальный объект, 
/// представленный заместителем.
/// </para>
/// </summary>
class RealSubject :
	public Subject {
public:
	void Request() const override {
		std::cout << "RealSubject: Handling request.\n";
	}
};

