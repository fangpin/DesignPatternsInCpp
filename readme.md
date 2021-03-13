- [1. creational patterns](#1-creational-patterns)
  - [1.1. Abstract Factory](#11-abstract-factory)
  - [1.2. Builder](#12-builder)
  - [1.3. prototype](#13-prototype)
  - [1.4. singleton](#14-singleton)
    - [1.4.1. naive singleton](#141-naive-singleton)
    - [1.4.2. thread safe singleton](#142-thread-safe-singleton)
- [2. Structural Patterns](#2-structural-patterns)
  - [2.1. Adapater](#21-adapater)
  - [2.2. Bridge](#22-bridge)
  - [2.3. Composite](#23-composite)
  - [2.4. Decorator](#24-decorator)
  - [2.5. Facade](#25-facade)
  - [2.6. Flyweight](#26-flyweight)
  - [2.7. proxy](#27-proxy)
- [3. Behavioral Patterns](#3-behavioral-patterns)
  - [3.1. chain of responsibiliby](#31-chain-of-responsibiliby)

# 1. creational patterns
## 1.1. Abstract Factory
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

## 1.2. Builder
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

## 1.3. prototype
Prototype is a design pattern that lets you copy existing objects without making your code depend on their classes.

## 1.4. singleton
Singleton is a design pattern, which ensures that only one instance of that kind exists and provides a single point of access to if for other code.
Singleton has same pros and cons as global variables, and never breaking the modularity of your code.
### 1.4.1. naive singleton
```cpp
#include <iostream>
#include <type_traits>

using namespace std;

template<typename T, typename Enable = void>
class Singleton;

template<typename T>
class Singleton<T, enable_if_t<is_default_constructible<T>::value>> {
private:
    static T* instance;
public:
    Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton(const Singleton&&) = delete;

    static T* Instance();
};

template<typename T>
T* Singleton<T, enable_if_t<is_default_constructible<T>::value>>::instance = nullptr;

template<typename T>
T* Singleton<T, enable_if_t<is_default_constructible<T>::value>>::Instance() {
    if (Singleton<T>::instance == nullptr) {
        Singleton<T>::instance = new T();
    }
    return Singleton<T>::instance;
}

struct TestClass1 {
    int a;
    TestClass1(): a(1) { }
};

struct TestClass2 {
    float b;
    TestClass2(): b(2.0) { }
};

int main() {
    cout << Singleton<TestClass1>::Instance()->a << endl;
    cout << Singleton<TestClass2>::Instance()->b << endl;
    return 0;
}
```

### 1.4.2. thread safe singleton
```cpp
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <type_traits>

using namespace std;

template<typename T, typename Enable = void>
class SingleTon;

template<typename T>
class SingleTon<T, enable_if_t<is_default_constructible<T>::value>>
{
private:
    static mutex mtx;
public:
    static T* instance;
    SingleTon() = delete;
    SingleTon(SingleTon&) = delete;
    SingleTon(SingleTon&&) = delete;

    static T* Instance();
};

template<typename T>
T* SingleTon<T, enable_if_t<is_default_constructible<T>::value>>::instance = nullptr;

template<typename T>
mutex SingleTon<T, enable_if_t<is_default_constructible<T>::value>>::mtx;

template<typename T>
T* SingleTon<T, enable_if_t<is_default_constructible<T>::value>>::Instance() {
    if (!instance) {
        unique_lock<mutex> locker(SingleTon<T, enable_if_t<is_default_constructible<T>::value>>::mtx);
        if (!instance) {
            instance = new T();
        }
    }
    return instance;
}

struct TestClass {
    int a;
    TestClass(): a(-1) {}
};

void TestFunc() {
    cout << SingleTon<TestClass>::Instance()->a << endl;
}

int main() {
    vector<thread> vec;
    for (int i=0; i<10; ++i) {
        vec.emplace_back(TestFunc);
    }
    for (auto& thd : vec)
        thd.join();
    return 0;
}
```

# 2. Structural Patterns
## 2.1. Adapater
Adapater is a design pattern that allows objects with incompatible interface to collabrate.
Convert interface of one object so that another interface can understand it.
```cpp
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Target {
public:
    virtual ~Target() = default;
    virtual string Request() const {
        return "ABC";
    }
};

class Adaptee {
public:
    virtual ~Adaptee() = default;
    string SpecificRequest() const {
        return "CBA";
    }
};

class Adapter : public Target, public Adaptee {
public:
    string Request() const override {
        string reverseStr = SpecificRequest();
        reverse(reverseStr.begin(), reverseStr.end());
        return reverseStr;
    }
};

string CompatibleClient(const Target& target) {
    return target.Request();
}

string IncompatibleClient(const Adaptee adaptee) {
    return adaptee.SpecificRequest();
}

int main() {
    Target target;
    Adaptee adaptee;
    Adapter adapter;
    cout << "Target:\t" << CompatibleClient(target) << endl;
    cout << "Adaptee:\t" << IncompatibleClient(adaptee) << endl;
    cout << "Adapter:\t" << CompatibleClient(adapter) << endl;
    return 0;
}
```

## 2.2. Bridge
Bridge is a design pattern that allows you to split a large class or a set of closely related classed into two separated hierarchies and can be developed independently of each other.
```cpp
#include <string>
#include <iostream>

using namespace std;

class Color {
public:
    virtual ~Color() = default;
    virtual string MyColor() const = 0;
};

class Red : public Color {
public:
    string MyColor() const override {
        return "red";
    }
};

class Blue : public Color {
public:
    string MyColor() const override {
        return "blue";
    }
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual string MyShape() const = 0;
};

class Square : public Shape {
public:
    string MyShape() const override {
        return "Square";
    }
};

class Triangle : public Shape {
public:
    string MyShape() const override {
        return "Triangle";
    }
};

class ColorShapeBridge {
private:
    const Color& color_;
    const Shape& shape_;
public:
    ColorShapeBridge(const Color& color, const Shape& shape): color_(color), shape_(shape) {}
    void ShowInfo() const {
        cout << "Color:\t" << color_.MyColor() << "\tShape:\t" << shape_.MyShape() << endl;
    }
};

void Client(const ColorShapeBridge& cs) {
    cs.ShowInfo();
}

int main() {
    Red red;
    Blue blue;
    Square square;
    Triangle triangle;
    ColorShapeBridge b1(red, square);
    ColorShapeBridge b2(blue, triangle);
    Client(b1);
    Client(b2);
    return 0;
}
```
## 2.3. Composite
Is a design pattern that allows you to compose objects into tree structures then work with these structures as if they were individual objects.

## 2.4. Decorator
Is a design pattern that allows you to attach new behaviors to objects by placing objects inside special wrapper objects that contains the behaviors.
```cpp
#include <iostream>

using namespace std;

class Component {
public:
    virtual ~Component() = default;
    virtual void Operation() const = 0;
};

class ConcreteComponent : public Component {
public:
    void Operation() const override {
        cout << " concrete component " << endl;
    }
};

class Decorator : public Component {
private:
    Component& component_;
public:
    Decorator(Component& component): component_(component) {}
    void Operation() const override {
        return component_.Operation();
    }
};

class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component& component): Decorator(component) {}
    void Operation() const override {
        cout << "ConcreateDecoratorA:\t";
        Decorator::Operation();
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component& component): Decorator(component) {}
    void Operation() const override {
        cout << "ConcreateDecoratorB:\t";
        Decorator::Operation();
    }
};

void Client(const Component& component) {
    component.Operation();
}


int main() {
    ConcreteComponent component;
    Client(component);
    ConcreteDecoratorA decoratedComponentA(component);
    ConcreteDecoratorB decoretedComponentB(decoratedComponentA);
    Client(decoratedComponentA);
    Client(decoretedComponentB);
    return 0;
}
```

## 2.5. Facade
is a design pattern that provides a simplified interface to a library, a framework or a set of complex classes.

## 2.6. Flyweight
also know as *Cache*
is a design pattern that fits more objects into availabe amount of memory by sharing common parts between multiple objects instead of keeping all of the data in each objects.

## 2.7. proxy
is a design pattern that lets you provide a placeholder or substiute for another object. The proxy controls the access to the original objects, allowing you perform something either before or after accessing the original object.
Proxy allows you do something before or after accessing some object without changing the original code.
Applicability:
- lazy initialization (virtual proxy)
- access control (protection proxy)
- local execution of a remote service (remote proxy)
- logging request (logging proxy)
- caching request results (cache proxy)
```cpp
#include <iostream>

using namespace std;

class Subject {
public:
    virtual void Request() const = 0;
};

class RealSubject: public Subject {
public:
    void Request() const override {
        cout << "A real quest" << endl;
    }
};

class Proxy: public Subject {
private:
    Subject const& subjct_;
public:
    Proxy(Subject const& sub): subjct_(sub) {}
    bool check() const {
        return true;
    }
    void log() const {
        cout << "log" << endl;
    }
    void Request() const override {
        if (check()) {
            subjct_.Request();
            log();
        }
    }
};

void Client(const Proxy& proxy) {
    proxy.Request();
}

int main() {
    RealSubject sub;
    Proxy proxy(sub);
    Client(proxy);
    return 0;
}
```
# 3. Behavioral Patterns
## 3.1. chain of responsibiliby
is a design pattern that allow you passing request along the chain of protential handlers until one of them handles request.
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Handler {
private:
    Handler* next_ = nullptr;
public:
    Handler& SetNext(Handler* next) {
        next_ = next;
        return *next_;
    }

    virtual void Handle(string request) const {
        if (next_) {
            next_->Handle(request);
        }
    }
};

class HandlerA: public Handler {
public:
    void Handle(string request) const override {
        if (request == "A") {
            cout << "Handle by Handler A" << endl;
            return;
        }
        Handler::Handle(request);
    }
};

class HandlerB: public Handler {
public:
    void Handle(string request) const override {
        if (request == "B") {
            cout << "Handle by Handler B" << endl;
            return;
        }
        Handler::Handle(request);
    }
};

class HandlerC: public Handler {
public:
    void Handle(string request) const override {
        if (request == "C") {
            cout << "Handle by Handler C" << endl;
            return;
        }
        Handler::Handle(request);
    }
};

void Client(const Handler& handler) {
    vector<string> data = {"C", "B", "A", "D"};
    for (const auto& x: data) {
        handler.Handle(x);
    }
}

int main() {
    HandlerA A;
    HandlerB B;
    HandlerC C;
    A.SetNext(&B).SetNext(&C);
    Client(A);
    return 0;
}
```