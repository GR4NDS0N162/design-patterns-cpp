/*
* Паттерн Строитель
*
* Назначение: Позволяет создавать сложные объекты пошагово. Строитель даёт
* возможность использовать один и тот же код строительства для получения разных
* представлений объектов.
*
* Имеет смысл использовать паттерн Строитель только тогда, когда ваши
* продукты достаточно сложны и требуют обширной конфигурации.
*
* В отличие от других порождающих паттернов, различные конкретные строители
* могут производить несвязанные продукты. Другими словами, результаты различных
* строителей могут не всегда следовать одному и тому же интерфейсу.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Product1 {
public:
	vector<string> parts_;
	void ListParts()const {
		cout << "Product parts: ";
		for (size_t i = 0; i < parts_.size(); i++) {
			if (parts_[i] == parts_.back()) {
				cout << parts_[i];
			}
			else {
				cout << parts_[i] << ", ";
			}
		}
		cout << "\n\n";
	}
};

/// <summary>
/// Интерфейс Строителя объявляет создающие методы для различных частей
/// объектов Продуктов.
/// </summary>
class Builder {
public:
	virtual ~Builder() {}
	virtual void ProducePartA() const = 0;
	virtual void ProducePartB() const = 0;
	virtual void ProducePartC() const = 0;
};

/// <summary>
/// Классы Конкретного Строителя следуют интерфейсу Строителя и предоставляют
/// конкретные реализации шагов построения. Ваша программа может иметь несколько
/// вариантов Строителей, реализованных по-разному.
/// </summary>
class ConcreteBuilder1 : public Builder {
private:
	/// <summary>
	/// Новый экземпляр строителя должен содержать пустой объект продукта,
	/// который используется в дальнейшей сборке.
	/// </summary>
	Product1* product;

public:

	ConcreteBuilder1() {
		this->Reset();
	}

	~ConcreteBuilder1() {
		delete product;
	}

	void Reset() {
		this->product = new Product1();
	}

	// Все этапы производства работают с одним и тем же экземпляром продукта.

	void ProducePartA()const override {
		this->product->parts_.push_back("PartA1");
	}

	void ProducePartB()const override {
		this->product->parts_.push_back("PartB1");
	}

	void ProducePartC()const override {
		this->product->parts_.push_back("PartC1");
	}

	/*
	* Конкретные Строители должны предоставить свои собственные методы
	* получения результатов. Это связано с тем, что различные типы строителей
	* могут создавать совершенно разные продукты с разными интерфейсами.
	* Поэтому такие методы не могут быть объявлены в базовом интерфейсе
	* Строителя (по крайней мере, в статически типизированном языке
	* программирования). Обратите внимание, что PHP является динамически
	* типизированным языком, и этот метод может быть в базовом интерфейсе.
	* Однако мы не будем объявлять его здесь для ясности.
	*
	* Как правило, после возвращения конечного результата клиенту, экземпляр
	* строителя должен быть готов к началу производства следующего продукта.
	* Поэтому обычной практикой является вызов метода сброса в конце тела
	* метода getProduct. Однако такое поведение не является обязательным, вы
	* можете заставить своих строителей ждать явного запроса на сброс из кода
	* клиента, прежде чем избавиться от предыдущего результата.
	*/

	/// <summary>
	/// <para>
	/// Пожалуйста, будьте осторожны здесь с владением памятью. Как только вы 
	/// вызываете GetProduct, пользователь этой функции несет ответственность 
	/// за освобождение этой памяти.
	/// </para>
	/// <para>
	/// Здесь может быть лучшим вариантом использовать умные указатели, 
	/// чтобы избежать утечек памяти.
	/// </para>
	/// </summary>
	/// <returns>Указатель на сконструированный продукт.</returns>
	Product1* GetProduct() {
		Product1* result = this->product;
		this->Reset();
		return result;
	}
};

/// <summary>
/// Директор отвечает только за выполнение шагов построения в определённой
/// последовательности. Это полезно при производстве продуктов в определённом
/// порядке или особой конфигурации. Строго говоря, класс Директор необязателен,
/// так как клиент может напрямую управлять строителями.
/// </summary>
class Director {
private:
	Builder* builder;

public:

	/*
	* Директор работает с любым экземпляром строителя, который передаётся
	* ему клиентским кодом. Таким образом, клиентский код может изменить
	* конечный тип вновь собираемого продукта.
	*/

	void set_builder(Builder* builder) {
		this->builder = builder;
	}

	/*
	* Директор может строить несколько вариаций продукта, используя
	* одинаковые шаги построения.
	*/

	void BuildMinimalViableProduct() {
		this->builder->ProducePartA();
	}

	void BuildFullFeaturedProduct() {
		this->builder->ProducePartA();
		this->builder->ProducePartB();
		this->builder->ProducePartC();
	}
};

/// <summary>
/// Клиентский код создаёт объект-строитель, передаёт его директору, а затем
/// инициирует процесс построения. Конечный результат извлекается из
/// объекта-строителя.
/// </summary>
/// <param name="director">Директор, используемый клиентом.</param>
void ClientCode(Director& director) {
	ConcreteBuilder1* builder = new ConcreteBuilder1();
	director.set_builder(builder);
	cout << "Standard basic product:\n";
	director.BuildMinimalViableProduct();

	Product1* p = builder->GetProduct();
	p->ListParts();
	delete p;

	cout << "Standard full featured product:\n";
	director.BuildFullFeaturedProduct();

	p = builder->GetProduct();
	p->ListParts();
	delete p;

	// Помните, что паттерн Строитель можно использовать без класса Директора.

	cout << "Custom product:\n";
	builder->ProducePartA();
	builder->ProducePartC();
	p = builder->GetProduct();
	p->ListParts();
	delete p;

	delete builder;
}

int main() {
	Director* director = new Director();
	ClientCode(*director);
	delete director;
	return 0;
}
