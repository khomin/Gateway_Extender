#include "connectionClient.h"

using namespace boost::asio;
using namespace boost::posix_time;

namespace connectionClient {

    talk_to_client::talk_to_client() : sock_(service) {
        this->lastPing = microsec_clock::local_time();
        this->commandPull = std::make_shared<commandPull::CommandPull>();
        memset(this->buff_, 0, sizeof(buff_));
    }

    talk_to_client::~talk_to_client() {}

    void talk_to_client::answer_to_client() {
        try {
            read_request();
            process_request();
        }
        catch (boost::system::system_error &) {
            stop();
        }
        if (timed_out()) {
            stop();
            std::cout << "stopping " << loginName << " - close connection no active" << std::endl;
        }
    }
    
    ip::tcp::socket& talk_to_client::sock() { 
         return sock_;
    }
    
    bool talk_to_client::timed_out() const {
        ptime now = microsec_clock::local_time();
        long long ms = (now - lastPing).total_milliseconds();
        return ms > 500000;
    }

    void talk_to_client::stop() {
        // close client connection
        boost::system::error_code err;
        sock_.close(err);
    }

    void talk_to_client::read_request() {
        if (sock_.available()) {
            // set client name if it empty
            if(sock_.is_open() && loginName.empty()) {
                ip::tcp::endpoint remote_ep = sock_.remote_endpoint();
                ip::address remote_ad = remote_ep.address();
                loginName = remote_ad.to_string();
                std::cout << " get ip -ok " << loginName << std::endl;
            }
            sock_.read_some(buffer(buff_, max_msg));
        }
    }

    void talk_to_client::process_request() {
        if(strlen(buff_) != 0) {
            lastPing = microsec_clock::local_time();
            std::string data(buff_);
            auto msg = commandPull->setData(data);
            if(msg.first) {
                sock_.write_some(buffer(msg.second));
                std::cout << "write msg " << msg.second << std::endl;
            } else {
                sock_.write_some(buffer(msg.second));
                std::cerr << "invalid msg " << msg.second << std::endl;
                stop();                
            }
            memset(buff_, 0, sizeof(buff_));
        }
    }
}