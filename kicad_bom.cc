#include <iostream>
#include <thread>
#include "Component.h"

auto test = Component("Hello!", "5");

void print_from_thread(int j){
    test.printReferenceID();
}

int main() {

    auto foo = std::thread(print_from_thread,6);

    test = Component("Hi", "5");
    test.printReferenceID();

    foo.join();
    return 0;
}