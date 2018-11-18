#ifndef COMMAND_SERVICE_H_
#define COMMAND_SERVICE_H_

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

namespace commandService
{
  void accept_thread();
  void handle_clients_thread();
}

#endif