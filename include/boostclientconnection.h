#ifndef BOOST_CLIENT_CONNECTION_H
#define BOOST_CLIENT_CONNECTION_H

#include <boost/asio.hpp>
#include "../include/fixedstring.h"
#include "../include/constants.h"

class BoostClientConnection {

public:
	void open_connection();
	void close_connection();
	void send_message(FixedString message);
	FixedString receive_message();

private:
	const FixedString host = constants::HOST;
	const int port = constants::PORT;
	boost::asio::ip::tcp::socket new_socket;
	boost::asio::detail::socket_type client_fd = 0;
};

#endif
