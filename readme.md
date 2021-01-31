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
```cpp
#include <vector>
#include <iostream>
#include <vector>

using namespace std;

class Product1 {
public:
    vector<string> parts_;
    void ShowProduct() {
        for (const auto& p : parts_) {
            cout << p << endl;
        }
    }
};

class Builder {
public:
    virtual ~Builder(){}
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
};

class ConcreteBuilder1 : public Builder {
private:
    Product1 product_;
public:
    ~ConcreteBuilder1() {}

    void BuildPartA() override {
        product_.parts_.push_back("Part A");
    }

    void BuildPartB() override {
        product_.parts_.push_back("Part B");
    }

    Product1& GetProduct() {
        return product_;
    }
};

class Director {
private:
    Builder& builder_;
public:
    Director(Builder& builder) : builder_(builder) {}

    void BuildMiniVersion() {
        builder_.BuildPartA();
    }

    void BuildFullVersion() {
        builder_.BuildPartA();
        builder_.BuildPartB();
    }
};

int main() {
    ConcreteBuilder1 builder1, builder2;
    Director director1(builder1);
    director1.BuildMiniVersion();
    cout << "Product build by builder 1 with mini version:" << endl;
    builder1.GetProduct().ShowProduct();
    cout << endl;
    
    Director director2(builder2);
    director2.BuildFullVersion();
    cout << "Product build by builder 2 with full version:" << endl;
    builder2.GetProduct().ShowProduct();
    cout << endl;
}
```