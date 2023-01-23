#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include "../include/serverconnection.h"


void ServerConnection::openConnection() {
	struct sockaddr_in address;
	int opt = 1;
	int addressLen = sizeof(address);

	if ((serverFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "socket failed error" << std::endl;
		return;
	}

	if (setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		std::cout << "setsockopt error" << std::endl;
		return;
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(serverFD, (struct sockaddr*)&address, sizeof(address)) < 0) {
		std::cout << "bind failed" << std::endl;
		return;
	}

	if (listen(serverFD, 3) < 0) {
		std::cout << "listen error" << std::endl;
		return;
	}

	if ((newSocket = accept(serverFD, (struct sockaddr*)&address, (socklen_t*)&addressLen)) < 0) {
		std::cout << "accept connection error" << std::endl;
		return;
	}
}

void ServerConnection::closeConnection() {
	close(newSocket);
	shutdown(serverFD, SHUT_RDWR);
}

void ServerConnection::sendMessage(std::string message) {
	send(newSocket, message.c_str(), strlen(message.c_str()), 0);
}

std::string ServerConnection::receiveMessage() {
	char buffer[1024] = { 0 };
	read(newSocket, buffer, 1024);
	return buffer;
}
