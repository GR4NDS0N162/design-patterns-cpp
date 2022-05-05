#pragma once

#include "Subject.h"
#include "RealSubject.h"
#include <iostream>

/// <summary>
/// <para>
/// Заместитель:
/// </para>
/// <para>
/// - хранит ссылку, которая позволяет заместителю 
/// обратиться к реальному субъекту. Объект класса Proxy 
/// может обращаться к объекту класса Subject, если 
/// интерфейсы классов RealSubject и Subject одинаковы;
/// </para>
/// <para>
/// - предоставляет интерфейс, идентичный 
/// интерфейсу Subject, так что заместитель всегда может 
/// быть подставлен вместо реального субъекта;
/// </para>
/// <para>
/// - контролирует доступ к реальному субъекту 
/// и может отвечать за его создание и удаление.
/// </para>
/// </summary>
class Proxy :
	public Subject {
private:
	RealSubject* real_subject;

	bool CheckAccess() const {
		// Некоторые реальные проверки должны проходить здесь.
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

