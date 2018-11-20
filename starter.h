#ifndef STARTER_H_
#define STARTER_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <memory>
#include <chrono>
#include <memory>
#include <utility>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "settings.h"
#include "commandService.h"

using namespace boost::asio;
using namespace boost::posix_time;

namespace starter {

class Starter
{
public:
Starter();
~Starter();

void run();

private:
    std::shared_ptr<settings::Settings> settings;
    // std::shared_ptr<commandService::CommandService> commandService;
    // std::shared_ptr<commandPull::CommandPull> commandPull;
};

}

#endif