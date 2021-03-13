#include <iostream>
#include <string>
// c++17
#include <string_view>

using namespace std;

class Command {
protected:
    string name_;
public:
    Command(string_view name): name_(name) {}
    virtual ~Command() = default;
    virtual void Execute() const = 0;
};

class CommandA: public Command {
public:
    CommandA(string_view name): Command(name) {}
    void Execute() const override {
        cout << "command A " << name_ << endl;
    }
};

class CommandB: public Command {
public:
    CommandB(string_view name): Command(name) {}
    void Execute() const override {
        cout << "Command B " << name_ << endl;
    }
};

class Invoker {
private:
    Command const& start_;
    Command const& end_;
public:
    Invoker(Command const& start, Command const& end): start_(start), end_(end) {
    }

    void Execute() const {
        start_.Execute();
        cout << "invoking" << endl;
        end_.Execute();
    }
};

void Client(Invoker const& invoker) {
    invoker.Execute();
}

int main() {
    CommandA startCommand("start");
    CommandB endCommand("end");
    Invoker invoker(startCommand, endCommand);
    Client(invoker);
    return 0;
}