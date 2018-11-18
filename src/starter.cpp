#include "../inc/starter.h"

namespace starter {

    Starter::Starter() {
        this->settings = std::make_shared<settings::Settings>();
        this->commandReceiver = std::make_shared<commandReceiver::CommandReceiver>();
        this->commandPull = std::make_shared<commandPull::CommandPull>();

        std::thread t(&starter::Starter::run, starter::Starter());
    }
    
    Starter::~Starter() {

    }

    void Starter::run() {

    }
}
