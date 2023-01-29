#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "connection.h"
#include "fixedstring.h"
#include "constants.h"
#include "logger.h"


class ClientConnection: public Connection {
public:
	ClientConnection();
	~ClientConnection();
	void open_connection();
	void close_connection();
	void send_message(FixedString message);
	FixedString receive_message();
private:
	const FixedString host = constants::HOST;
	const int port = constants::PORT;
	int new_socket = 0, client_fd = 0;
};

#endif