#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "../include/fixedstring.h"

class ClientConnection {
public:
	void open_connection();
	void close_connection();
	void send_message(FixedString message);
	FixedString receive_message();
private:
	const FixedString host = "127.0.0.1";
	const int port = 5555;
	int new_socket = 0, client_fd = 0;
};

#endif