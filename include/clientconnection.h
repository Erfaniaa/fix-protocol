#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <string>

class ClientConnection {
private:
	const std::string host = "127.0.0.1";
	const int port = 5555;
	int newSocket = 0, clientFD = 0;
public:
	void openConnection();
	void closeConnection();
	void sendMessage(std::string message);
	std::string receiveMessage();
};

#endif