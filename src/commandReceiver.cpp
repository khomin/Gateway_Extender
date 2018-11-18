#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "../inc/commandReceiver.h"

namespace commandReceiver
{

CommandReceiver::CommandReceiver() {
    // do_accept();
}

CommandReceiver::~CommandReceiver() {
}

  void CommandReceiver::do_accept() {
    //   acceptor.async_accept(socket,
    //                          [this] (boost::system::error_code ec) {
    //                              if (!ec) {
    //                                 do_read(); //  std::make_shared<session>(std::move(socket_))->start();
    //                              }
    //                              do_accept();
    //                          });
  }

  void CommandReceiver::do_read() {
//     auto self(shared_from_this());
//     socket_.async_read_some(boost::asio::buffer(data_, max_length),
//         [this, self](boost::system::error_code ec, std::size_t length)
//         {
//           if (!ec)
//           {
//             do_write(length);
//           }
//         });
  }
  void CommandReceiver::do_write(std::size_t length) {
    //   auto self(shared_from_this());
//     boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
//         [this, self](boost::system::error_code ec, std::size_t /*length*/)
//         {
//           if (!ec)
//           {
//             do_read();
//           }
//         });
  }

} // namespace commandReceiver
