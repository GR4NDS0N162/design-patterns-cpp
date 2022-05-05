#pragma once

#include "Subject.h"
#include "RealSubject.h"
#include <iostream>

/// <summary>
/// <para>
/// �����������:
/// </para>
/// <para>
/// - ������ ������, ������� ��������� ����������� 
/// ���������� � ��������� ��������. ������ ������ Proxy 
/// ����� ���������� � ������� ������ Subject, ���� 
/// ���������� ������� RealSubject � Subject ���������;
/// </para>
/// <para>
/// - ������������� ���������, ���������� 
/// ���������� Subject, ��� ��� ����������� ������ ����� 
/// ���� ���������� ������ ��������� ��������;
/// </para>
/// <para>
/// - ������������ ������ � ��������� �������� 
/// � ����� �������� �� ��� �������� � ��������.
/// </para>
/// </summary>
class Proxy :
	public Subject {
private:
	RealSubject* real_subject;

	bool CheckAccess() const {
		// ��������� �������� �������� ������ ��������� �����.
		std::cout << "Proxy: Checking access prior to firing a real request.\n";
		return true;
	}

	void LogAccess() const {
		std::cout << "Proxy: Logging the time of request.\n";
	}

public:
	Proxy(RealSubject* real_subject)
		: real_subject(new RealSubject(*real_subject)) {}

	~Proxy() {
		delete real_subject;
	}

	void Request() const override {
		if (this->CheckAccess()) {
			this->real_subject->Request();
			this->LogAccess();
		}
	}
};

