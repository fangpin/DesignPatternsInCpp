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