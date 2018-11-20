#include "commandHandler.h"
#include "interfaces/interfaceSerial.h"

namespace commandHandler
{
    static std::mutex lock;

    CommandHandler::CommandHandler(const InterfaceAbstract::sInterfaceProperty & interface) {
        statistics.packetSended = 0;
        statistics.packetLosed = 0;
        ioHandler.reset();
        ioHandler = std::dynamic_pointer_cast<InterfaceAbstract>(std::make_shared<InterfaceSerial>(interface));
        this->data = std::make_shared<std::vector<sData>>();
        this->handlerThread = std::make_shared<std::thread> (std::thread(handlerFunction, std::ref(ioHandler), std::ref(data)));
        this->handlerThread->detach();
    }
    
    CommandHandler::~CommandHandler() {
        ioHandler.reset();
        handlerThread.reset();
    }

    void CommandHandler::addTranssmitedBytes(std::vector<uint8_t> & dataPacket) {
        sData tpackData;
        std::lock_guard<std::mutex> tlock(lock);
        tpackData.dataPacket = dataPacket;
        tpackData.header = std::string("header packet");
        data->push_back(std::move(tpackData));
    }

    void CommandHandler::handlerFunction(std::shared_ptr<InterfaceAbstract> & handler, std::shared_ptr<std::vector<sData>> sendData) {
        while(1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            if(lock.try_lock()) {
                if(!sendData->empty()) {
                    auto packet = sendData->front();
                    bool sendResult = handler->writeData(packet.dataPacket.data(), packet.dataPacket.size());
                    if(sendResult) {
                        sendData->erase(sendData->begin());
                    } else {
                        // if connection lost
                        handler->openConnection();
                    }
                }
                lock.unlock();
            }
        }
    }

    std::string CommandHandler::getStatusIo() const {
        return ioHandler->getIsConnected() ? "io connected" : "io closed";
    }

    std::string CommandHandler::getStatistics() const {
        std::string stats;
        stats = "packet losed-" + std::to_string(statistics.packetLosed) + ", packet sended-" + std::to_string(statistics.packetSended);
        return stats;
    }
}