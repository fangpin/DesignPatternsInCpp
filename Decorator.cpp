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