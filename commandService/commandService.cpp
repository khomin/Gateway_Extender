
#include <iostream>
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
#include "commandService.h"
#include "connectionClient.h"

using namespace boost::asio;
using namespace boost::posix_time;

namespace commandService {

void accept_thread() {
    ip::tcp::acceptor acceptor(connectionClient::service, ip::tcp::endpoint(ip::tcp::v4(), 8001));
    while (true) {
        connectionClient::client_ptr new_(new connectionClient::talk_to_client);
        acceptor.accept(new_->sock());
        boost::recursive_mutex::scoped_lock lk(connectionClient::cs);
        connectionClient::clients.push_back(new_);
    }
}

void handle_clients_thread() {
    while (true) {
        boost::this_thread::sleep(millisec(1));
        boost::recursive_mutex::scoped_lock lk(connectionClient::cs);
        for (connectionClient::array::iterator b = connectionClient::clients.begin(), e = connectionClient::clients.end(); b != e; ++b)
            (*b)->answer_to_client();
        // erase clients that timed out
        connectionClient::clients.erase(std::remove_if(connectionClient::clients.begin(), connectionClient::clients.end(),
                                     boost::bind(&connectionClient::talk_to_client::timed_out, _1)),
                      connectionClient::clients.end());
    }
}
}