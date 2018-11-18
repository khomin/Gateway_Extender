#ifndef STARTER_H_
#define STARTER_H_

#include <iostream>
#include <string>
#include "settings.h"
#include "commandReceiver.h"
#include "commandPull.h"

namespace starter
{

class Starter
{
  public:
    Starter();
    ~Starter();

    void run();

    private:
        std::shared_ptr<settings::Settings> settings;
        std::shared_ptr<commandReceiver::CommandReceiver> commandReceiver;
        std::shared_ptr<commandPull::CommandPull> commandPull;
    };
} // namespace starter

#endif