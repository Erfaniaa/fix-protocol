#ifndef BOOST_CLIENT_CONNECTION_H
#define BOOST_CLIENT_CONNECTION_H

#include <iostream>
#include <boost/asio.hpp>
#include <string>

class BoostClientConnection {

public:
	void open_connection();
	void close_connection();
	void send_message(std::string message);
	std::string receive_message();

private:
	const std::string host = "127.0.0.1";
	const int port = 5555;
	boost::asio::ip::tcp::socket new_socket;
	boost::asio::detail::socket_type client_fd = 0;
};

#endif
