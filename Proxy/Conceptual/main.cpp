/*
* Паттерн Заместитель
*
* Назначение: Позволяет подставлять вместо реальных объектов специальные
* объекты-заменители. Эти объекты перехватывают вызовы к оригинальному объекту,
* позволяя сделать что-то до или после передачи вызова оригиналу.
*/

#include <iostream>

using namespace std;

/// <summary>
/// Интерфейс Субъекта объявляет общие операции как для Реального Субъекта,
/// так и для Заместителя. Пока клиент работает с Реальным Субъектом, используя
/// этот интерфейс, вы сможете передать ему заместителя вместо реального
/// субъекта.
/// </summary>
class Subject {
public:
	virtual void Request() const = 0;
};

/// <summary>
/// Реальный Субъект содержит некоторую базовую бизнес-логику. Как правило,
/// Реальные Субъекты способны выполнять некоторую полезную работу, которая к
/// тому же может быть очень медленной или точной – например, коррекция входных
/// данных. Заместитель может решить эти задачи без каких-либо изменений в коде
/// Реального Субъекта.
/// </summary>
class RealSubject : public Subject {
public:
	void Request() const override {
		cout << "RealSubject: Handling request.\n";
	}
};

/// <summary>
/// <para>
/// Интерфейс Заместителя идентичен интерфейсу Реального Субъекта.
/// </para>
/// <para>
/// Заместитель хранит ссылку на объект класса Реального Субъекта. Клиент
/// может либо лениво загрузить его, либо передать Заместителю.
/// </para>
/// <para>
/// Наиболее распространёнными областями применения паттерна Заместитель
/// являются ленивая загрузка, кэширование, контроль доступа, ведение журнала
/// и т.д. Заместитель может выполнить одну из этих задач, а затем, в
/// зависимости от результата, передать выполнение одноимённому методу в
/// связанном объекте класса Реального Субъект.
/// </para>
/// </summary>
class Proxy : public Subject {
private:
	RealSubject* real_subject_;

	bool CheckAccess() const {
		// Некоторые реальные проверки должны проходить здесь.
		cout << "Proxy: Checking access prior to firing a real request.\n";
		return true;
	}
	void LogAccess() const {
		cout << "Proxy: Logging the time of request.\n";
	}

public:
	Proxy(RealSubject* real_subject) : real_subject_(new RealSubject(*real_subject)) {}

	~Proxy() {
		delete real_subject_;
	}

	void Request() const override {
		if (this->CheckAccess()) {
			this->real_subject_->Request();
			this->LogAccess();
		}
	}
};

/// <summary>
/// Клиентский код должен работать со всеми объектами (как с реальными, так и
/// заместителями) через интерфейс Субъекта, чтобы поддерживать как реальные
/// субъекты, так и заместителей. В реальной жизни, однако, клиенты в основном
/// работают с реальными субъектами напрямую. В этом случае, для более простой
/// реализации паттерна, можно расширить заместителя из класса реального
/// субъекта.
/// </summary>
/// <param name="subject">Субъект, с которым работает клиент. Это может быть 
/// как с реальный субъект, так и заместитель.</param>
void ClientCode(const Subject& subject) {
	// ...
	subject.Request();
	// ...
}

int main() {
	cout << "Client: Executing the client code with a real subject:\n";
	RealSubject* real_subject = new RealSubject;
	ClientCode(*real_subject);
	cout << "\n";
	cout << "Client: Executing the same client code with a proxy:\n";
	Proxy* proxy = new Proxy(real_subject);
	ClientCode(*proxy);

	delete real_subject;
	delete proxy;
	return 0;
}
