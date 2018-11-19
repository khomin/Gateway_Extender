#ifndef COMMAND_PULL_H_
#define COMMAND_PULL_H_

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <utility>
#include "commandHandler.h"

namespace commandPull
{
class CommandPull
{
  public:
    CommandPull();
    ~CommandPull();
    std::pair<bool,std::string> setData(std::string & data);
  private:
    bool updateConfig(std::string & config);
    std::string getStatus() const;
    std::string getStatisctics() const;
  private:
    std::shared_ptr<commandHandler::CommandHandler> commandHandler;
};

}

#endif