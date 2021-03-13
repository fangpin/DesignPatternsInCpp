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