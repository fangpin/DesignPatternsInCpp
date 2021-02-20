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