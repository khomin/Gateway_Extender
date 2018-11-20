#include "commandHandler.h"
#include "interfaces/interfaceSerial.h"

namespace commandHandler
{
    static std::mutex lock;

    CommandHandler::CommandHandler(const InterfaceAbstract::sInterfaceProperty & interface) {
        ioHandler.reset();
        // ioHandler = std::dynamic_pointer_cast<InterfaceAbstract>(std::make_shared<InterfaceSerial>(interface));
        // this->handlerThread = std::make_shared<std::thread> (std::thread(handlerFunction, std::ref(ioHandler)));
        this->handlerThread->detach();
    }
    
    CommandHandler::~CommandHandler() {

    }

    void CommandHandler::handlerFunction(std::shared_ptr<InterfaceAbstract> & handler) {
        while(1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            if(lock.try_lock()) {
                if(handler->getIsConnected()) {
                    uint16_t len = 0;
                    uint8_t* data = new uint8_t(len);
                    handler->writeData(data, len);
                }
                lock.unlock();
            }
        }
    }

}