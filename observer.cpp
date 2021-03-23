#include <iostream>
#include <string>
#include <list>

using namespace std;

class ISubject;
class IObserver;

class ISubject {
public:
    virtual ~ISubject() {}
    virtual void Notify(string const& msg) = 0;
    virtual void AddSubscriber(IObserver* observer) = 0;
    virtual void RemoveSubscriber(IObserver* observer) = 0;
};

class IObserver {
public:
    virtual ~IObserver() {}
    virtual void Subscribe(ISubject* subject) = 0;
    virtual void Unsubscribe(ISubject* subject) = 0;
    virtual void OnNotify(string const& msg) = 0;
};

class Subject : public ISubject {
public:
    Subject() = default;
    void AddSubscriber(IObserver* observer) override {
        observers.push_back(observer);
    }
    void RemoveSubscriber(IObserver* observer) override {
        observers.remove(observer);
    }
    void Notify(const string& msg) {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            (*it)->OnNotify(msg);
        }
    }

private:
    list<IObserver*> observers;
};

class Observer : public IObserver {
public:
    void Subscribe(ISubject* subject) override {
        subject->AddSubscriber(this);
    }
    void Unsubscribe(ISubject* subject) override {
        subject->RemoveSubscriber(this);
    }
    void OnNotify(string const& msg) override {
        cout << msg << endl;
    }
};

int main() {
    Subject subject;
    Observer observer1;
    Observer observer2;

    observer1.Subscribe(&subject);
    observer2.Subscribe(&subject);
    subject.Notify("msg1");

    observer1.Unsubscribe(&subject);
    subject.Notify("msg2");
    
    return 0;
}