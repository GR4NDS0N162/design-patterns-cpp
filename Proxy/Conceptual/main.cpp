#include "Subject.h"
#include "RealSubject.h"
#include "Proxy.h"
#include <iostream>

void ClientCode(const Subject& subject) {
	// ...
	subject.Request();
	// ...
}

int main() {
	std::cout << "Client: Executing the client code with a real subject:\n";
	RealSubject* real_subject = new RealSubject;
	ClientCode(*real_subject);
	std::cout << "\n";
	std::cout << "Client: Executing the same client code with a proxy:\n";
	Proxy* proxy = new Proxy(real_subject);
	ClientCode(*proxy);

	delete real_subject;
	delete proxy;
	return 0;
}

