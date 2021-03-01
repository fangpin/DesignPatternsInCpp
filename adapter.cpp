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