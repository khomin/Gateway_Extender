#include "starter.h"

namespace starter {

    Starter::Starter() {
        this->settings = std::make_shared<settings::Settings>();
    }
    
    Starter::~Starter() {
    }
    void Starter::run() {
        boost::thread_group threads;
        threads.create_thread(commandService::accept_thread);
        threads.create_thread(commandService::handle_clients_thread);
        threads.join_all();
    }
}