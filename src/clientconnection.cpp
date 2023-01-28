#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include "../include/clientconnection.h"


void ClientConnection::open_connection() {
	struct sockaddr_in server_address;

	if ((new_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		logger_.log_error("Socket creation error");
		return;
	}

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);

	if (inet_pton(AF_INET, host.c_str(), &server_address.sin_addr) <= 0) {
		logger_.log_error("Invalid address/Address not supported error");
		return;
	}

	if ((client_fd = connect(new_socket, (struct sockaddr*)&server_address, sizeof(server_address))) < 0) {
		logger_.log_error("Connection failed error");
		return;
	}
}

void ClientConnection::close_connection() {
	close(client_fd);
}

void ClientConnection::send_message(FixedString message) {
	send(new_socket, message.c_str(), message.size(), 0);
}

FixedString ClientConnection::receive_message() {
	char buffer[constants::MAX_MESSAGE_LENGTH] = { 0 };
	read(new_socket, buffer, constants::MAX_MESSAGE_LENGTH);
	return buffer;
}
