#include "commandHandler.h"
#include "interfaces/interfaceSerial.h"

namespace commandHandler
{
    static std::mutex lock;

    CommandHandler::CommandHandler(const InterfaceAbstract::sInterfaceProperty & interface)
     : flagDataIsSended(false)
    {
        ioHandler.reset();
        ioHandler = std::dynamic_pointer_cast<InterfaceAbstract>(std::make_shared<InterfaceSerial>(interface));
        this->statistics = std::make_shared<sStatistics>();
        this->statistics->packetSended = 0;
        this->statistics->packetSendError = 0;
        this->statistics->sendAttemptCounter = 0;
        this->statistics->lastSendedByteCount = 0;
        this->data = std::make_shared<std::vector<sData>>();
        this->handlerThread = std::make_shared<std::thread> (std::thread(handlerFunction, 
            std::ref(ioHandler), std::ref(data), std::ref(statistics), std::ref(flagDataIsSended)));
        this->handlerThread->detach();
    }
    
    CommandHandler::~CommandHandler() {
        ioHandler.reset();
        handlerThread.reset();
    }

    std::future<int> CommandHandler::addTranssmitedBytes(std::vector<uint8_t> & dataPacket) {
        sData tpackData;
        std::lock_guard<std::mutex> tlock(lock);
        tpackData.dataPacket = dataPacket;
        tpackData.header = std::string("header packet");
        flagDataIsSended = false;
        statistics->lastSendedByteCount = 0;
        data->push_back(std::move(tpackData));
        auto replyHandle = [&]() {
            while(!flagDataIsSended) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            return statistics->lastSendedByteCount;
        };
        std::packaged_task<int()> task(replyHandle);
        auto future = task.get_future();
        std::thread thread(std::move(task));
        thread.detach();
        return std::move(future);
    }

    void CommandHandler::handlerFunction(std::shared_ptr<InterfaceAbstract> & handler, 
        std::shared_ptr<std::vector<sData>> & sendData,
        std::shared_ptr<sStatistics> & stats,
        bool & flagDataIsSended)
    {
        while(1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            if(lock.try_lock()) {
                if(!sendData->empty()) {
                    auto packet = sendData->front();
                    bool sendResult = handler->writeData(packet.dataPacket.data(), packet.dataPacket.size());
                    if(sendResult) {
                        std::shared_ptr<uint8_t> replyBuf = std::make_shared<uint8_t>(512);
                        int replyLen = handler->readData(replyBuf.get());
                        if(replyLen) {

                        }
                        stats->packetSended++;
                        stats->lastSendedByteCount = sendData->begin()->dataPacket.size();
                        flagDataIsSended = true;
                        if(!sendData->empty()) {
                            sendData->erase(sendData->begin());
                        }
                    } else {
                        // if connection lost
                        handler->openConnection();
                        // second attemp and remove it command
                        if(stats->sendAttemptCounter > 1) {
                            stats->sendAttemptCounter = 0;
                            stats->lastSendedByteCount = 0;
                            sendData->erase(sendData->begin());
                            flagDataIsSended = true;
                        } else {
                            stats->sendAttemptCounter++;
                        }
                        stats->packetSendError++;
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
        stats = "packet losed-" + std::to_string(statistics->packetSendError) + ", packet sended-" + std::to_string(statistics->packetSended);
        return stats;
    }
}