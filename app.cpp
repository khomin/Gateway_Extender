#include <iostream>

int main(int argc, char *argv[]) {
    boost::thread_group threads;
    threads.create_thread(accept_thread);
    threads.create_thread(handle_clients_thread);
    threads.join_all();

    return 0;
}

// #include <iostream>
// #include <memory>
// #include "./inc/starter.h"

// int main(int count, char **args){
//     std::cout << "Gateway_Extender - starting...\n";

//     std::thread t(&starter::Starter::run, starter::Starter());

//     t.join();

//     return 0;
// }