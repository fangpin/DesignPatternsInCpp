# creational patterns
## Abstract Factory
```cpp
#include <string>
#include <memory>
#include <iostream>
using namespace std;

class AbstractProductA {
public:
    virtual ~AbstractProductA() {};
    virtual string FuncA() const = 0;
};

class ConcreteProductA1 : public AbstractProductA {
public:
    string FuncA() const override {
        return "ProductA 1";
    }
};

class ConcreteProductA2 : public AbstractProductA {
public:
    string FuncA() const override {
        return "ProductA 2";
    }
};

class AbstractProductB {
public:
    virtual ~AbstractProductB() {};
    virtual string FuncB() const = 0;
};

class ConcreteProductB1 : public AbstractProductB {
public:
    string FuncB() const override {
        return "ProductB 1";
    }
};

class ConcreteProductB2 : public AbstractProductB {
public:
    string FuncB() const override {
        return "ProductB 2";
    }
};

class AbstractFactory {
public:
    virtual ~AbstractFactory() {};
    virtual AbstractProductA* CreateProductA() const = 0;
    virtual AbstractProductB* CreateProductB() const = 0;
};

class ConcreteFactoryA : public AbstractFactory {
public:
    virtual AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA1();
    }

    virtual AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB1();
    }
};

class ConcreteFactoryB : public AbstractFactory {
public:
    virtual AbstractProductA* CreateProductA() const override {
        return new ConcreteProductA2();
    }

    virtual AbstractProductB* CreateProductB() const override {
        return new ConcreteProductB2();
    }
};


void testClient(const AbstractFactory& factory) {
    AbstractProductA* productA = factory.CreateProductA();
    AbstractProductB* productB = factory.CreateProductB();
    cout << productA->FuncA() << endl;
    cout << productB->FuncB() << endl;
    delete productB;
    delete productA;
}

int main() {
    ConcreteFactoryA factoryA;
    testClient(factoryA);

    ConcreteFactoryB factoryB;
    testClient(factoryB);
}
```

## Builder
allow you to create objects step by step, and produce different types and represetation of objects by same construction code.

Construct your object by series ordered builder step, you can implement different builder to construct different objects.

Suit for cases that your object is quite complex require extensive configuration.