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
#include "commandPull/commandPull.h"

#ifndef CONNECTION_CLIENT_H_
#define CONNECTION_CLIENT_H_

using namespace boost::asio;
using namespace boost::posix_time;

namespace connectionClient
{
class talk_to_client
{
public:
    talk_to_client();
    ~talk_to_client();

    void answer_to_client();
    ip::tcp::socket &sock();
    bool timed_out() const;

  private:
    void read_request();
    void process_request();
    void stop();
  private:
    ip::tcp::socket sock_;
    enum
    {
        max_msg = 1024
    };
    char buff_[max_msg];
    std::string loginName;
    ptime lastPing;
    typedef boost::shared_ptr<talk_to_client> client_ptr;
    typedef std::vector<client_ptr> array;

    std::shared_ptr<commandPull::CommandPull> commandPull;
};

  static io_service service;
  typedef boost::shared_ptr<talk_to_client> client_ptr;
  typedef std::vector<client_ptr> array;
  static array clients;
  static boost::recursive_mutex cs;
}

#endif