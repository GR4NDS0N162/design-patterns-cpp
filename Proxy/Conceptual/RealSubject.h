#pragma once

#include "Subject.h"
#include <iostream>

/// <summary>
/// <para>
/// �������� �������:
/// </para>
/// <para>
/// - �������� �������� ������-������.
/// </para>
/// <para>
/// - ���������� �������� ������, 
/// �������������� ������������.
/// </para>
/// </summary>
class RealSubject :
	public Subject {
public:
	void Request() const override {
		std::cout << "RealSubject: Handling request.\n";
	}
};

