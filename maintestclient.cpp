#include <thread>
#include "../include/fixedstring.h"
#include "../include/messagefactory.h"
#include "../include/clientconnection.h"
#include "../include/logger.h"


void receive_and_log_message(ClientConnection* client_connection) {
	while (client_connection->is_connected()) {
		FixedString received_fixed_string = client_connection->receive_message();
		if (received_fixed_string.size() == 0)
			continue;
		Logger().log_info(const_cast<char*>("Message received"));
		Logger().log_info(received_fixed_string.c_str());
	}
}

int main() {
	ClientConnection client_connection;
	client_connection.open_connection();

	std::thread t(receive_and_log_message, &client_connection);
	t.join();

	FixedString serialized_message = MessageFactory().create_logon().serialize();
	client_connection.send_message(serialized_message);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_message.c_str());
	return 0;
}
