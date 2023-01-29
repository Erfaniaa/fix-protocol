#ifndef BOOST_CLIENT_CONNECTION_H
#define BOOST_CLIENT_CONNECTION_H

#include <boost/asio.hpp>
#include "connection.h"
#include "fixedstring.h"
#include "constants.h"
#include "logger.h"


class BoostClientConnection: public Connection {

public:
	BoostClientConnection();
	~BoostClientConnection();
	void open_connection();
	void close_connection();
	void send_message(FixedString message);
	FixedString receive_message();

private:
	const FixedString host = constants::HOST;
	const int port = constants::PORT;
	boost::asio::ip::tcp::socket *new_socket = NULL;
	boost::asio::detail::socket_type client_fd = 0;
};

#endif
