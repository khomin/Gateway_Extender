#include <iostream>
#include <thread>
#include "starter.h"

int main(int argc, char *argv[]) {
    std::cout << "Gateway_Extender - starting...\n";

    std::thread t(&starter::Starter::run, starter::Starter());
    t.join();

    return 0;
}