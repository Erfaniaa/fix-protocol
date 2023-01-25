#include "../include/serverconnection.h"


void ServerConnection::open_connection() {
	struct sockaddr_in address;
	int opt = 1;
	int address_len = sizeof(address);

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "socket failed error" << std::endl;
		return;
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cout << "setsockopt error" << std::endl;
		return;
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		std::cout << "bind failed" << std::endl;
		return;
	}

	if (listen(server_fd, 3) < 0) {
		std::cout << "listen error" << std::endl;
		return;
	}

	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&address_len)) < 0) {
		std::cout << "accept connection error" << std::endl;
		return;
	}
}

void ServerConnection::close_connection() {
	close(new_socket);
	shutdown(server_fd, SHUT_RDWR);
}

void ServerConnection::send_message(FixedString message) {
	send(new_socket, message.c_str(), message.size(), 0);
}

FixedString ServerConnection::receive_message() {
	char buffer[1024] = { 0 };
	read(new_socket, buffer, 1024);
	return buffer;
}
