#ifndef CONNECTION_CLIENT_H_
#define CONNECTION_CLIENT_H_

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

using namespace boost::asio;
using namespace boost::posix_time;

namespace connectionClient
{
class talk_to_client
{
public:
    talk_to_client();
    std::string username() const;
    void answer_to_client();
    void set_clients_changed();
    ip::tcp::socket &sock();
    bool timed_out() const;
    void stop();

  private:
    void read_request();
    void process_request();
    void on_login(const std::string &msg);
    void on_ping();
    void on_clients();
    void write(const std::string &msg);
    void update_clients_changed();

  private:
    ip::tcp::socket sock_;
    enum
    {
        max_msg = 1024
    };
    int already_read_;
    char buff_[max_msg];
    bool started_;
    std::string username_;
    bool clients_changed_;
    ptime last_ping;
};

io_service service;
typedef boost::shared_ptr<talk_to_client> client_ptr;
typedef std::vector<client_ptr> array;
array clients;
boost::recursive_mutex cs;
}

#endif