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