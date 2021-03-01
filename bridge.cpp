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