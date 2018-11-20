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

  private:
    static void handlerFunction(std::shared_ptr<InterfaceAbstract> & handler);
    std::shared_ptr<InterfaceAbstract> ioHandler;
    std::shared_ptr<std::thread> handlerThread;
};
}

#endif