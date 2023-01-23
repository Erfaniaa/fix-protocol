#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include "../include/clientconnection.h"


void ClientConnection::openConnection() {
	struct sockaddr_in serverAddress;

	if ((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "Socket creation error" << std::endl;
		return;
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);

	if (inet_pton(AF_INET, host.c_str(), &serverAddress.sin_addr) <= 0) {
		std::cout << "Invalid address/Address not supported error" << std::endl;
		return;
	}

	if ((clientFD = connect(newSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) < 0) {
		std::cout << "Connection failed error" << std::endl;
		return;
	}
}

void ClientConnection::closeConnection() {
	close(clientFD);
}

void ClientConnection::sendMessage(std::string message) {
	send(newSocket, message.c_str(), strlen(message.c_str()), 0);
}

std::string ClientConnection::receiveMessage() {
	char buffer[1024] = { 0 };
	read(newSocket, buffer, 1024);
	return buffer;
}
