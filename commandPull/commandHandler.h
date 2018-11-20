#ifndef COMMAND_HANDLER_H_
#define COMMAND_HANDLER_H_

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>
#include "interfaces/interfaceAbstract.h"

namespace commandHandler
{
class CommandHandler
{
  public:
    CommandHandler(const InterfaceAbstract::sInterfaceProperty & interface);
    ~CommandHandler();    

    void addTranssmitedBytes(std::vector<uint8_t> & dataPacket);
    std::string getStatusIo() const;
    std::string getStatistics() const;

  private:
    typedef struct {
      std::string header;
      std::vector<uint8_t> dataPacket;
    }sData;
    
    typedef struct {
      int packetSended;
      int packetSendError; 
      int sendAttemptCounter;
    }sStatistics;

    static void handlerFunction(std::shared_ptr<InterfaceAbstract> & handler, 
        std::shared_ptr<std::vector<sData>> & sendData, 
        std::shared_ptr<sStatistics> & stats
    );
    std::shared_ptr<std::vector<sData>> data;
    std::shared_ptr<InterfaceAbstract> ioHandler;
    std::shared_ptr<std::thread> handlerThread;
    std::shared_ptr<sStatistics> statistics;
};
}

#endif