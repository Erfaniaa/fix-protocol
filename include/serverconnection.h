#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include "connection.h"
#include "fixedstring.h"
#include "logger.h"


class ServerConnection: public Connection {
public:
	void open_connection();
	void close_connection();
	void send_message(FixedString message);
	FixedString receive_message();
	bool is_connected();

private:
	const int port = constants::PORT;
	int new_socket = 0, server_fd = 0;
};

#endif