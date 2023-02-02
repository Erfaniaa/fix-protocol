#ifndef BOOST_SERVER_CONNECTION_H
#define BOOST_SERVER_CONNECTION_H

#include <boost/asio.hpp>
#include "connection.h"
#include "fixedstring.h"
#include "constants.h"


class BoostServerConnection: public Connection {
public:
	BoostServerConnection() = default;
	~BoostServerConnection() = default;
	void open_connection();
	void close_connection();
	void send_message(FixedString message);
	FixedString receive_message();
	bool is_connected();

private:
	const unsigned short port = constants::PORT;
	std::unique_ptr<boost::asio::ip::tcp::socket> new_socket;
};

#endif