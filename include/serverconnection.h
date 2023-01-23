#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

namespace FIX {
	class ServerConnection {
	private:
		const int port = 5555;
		int newSocket = 0, serverFD = 0;
	public:
		void openConnection();
		void closeConnection();
		void sendMessage(std::string message);
		std::string receiveMessage();
	};
}

#endif