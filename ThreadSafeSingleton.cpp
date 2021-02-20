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