#ifndef BOOST_SERVER_CONNECTION_H
#define BOOST_SERVER_CONNECTION_H

#include <boost/asio.hpp>
#include "../include/fixedstring.h"
#include "../include/constants.h"

class BoostServerConnection {
public:
	void open_connection();
	void close_connection();
	void send_message(FixedString message);
	FixedString receive_message();
private:
	const unsigned short port = constants::PORT;
	boost::asio::ip::tcp::socket new_socket;
};

#endif