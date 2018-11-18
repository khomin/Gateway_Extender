#ifndef COMMAND_RECEIVER_H_
#define COMMAND_RECEIVER_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <memory>
#include <chrono>
#include <utility>
#include <cstdlib>
#include <boost/asio.hpp>
#include "settings.h"

namespace commandReceiver
{
class CommandReceiver
{
public:
  CommandReceiver();
  ~CommandReceiver();

private:
  void do_read();
  void do_write(std::size_t length);
  void do_accept();

  // std::shared_ptr<settings::Settings> settings;
  // boost::asio::io_service io_service;
  // boost::asio::ip::tcp::acceptor acceptor;
  // boost::asio::ip::tcp::socket socket;
};

} // namespace commandReceiver

#endif