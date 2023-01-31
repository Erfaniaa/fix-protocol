#include <thread>
#include <chrono>
#include "../include/fixedstring.h"
#include "../include/messagefactory.h"
#include "../include/clientconnection.h"
#include "../include/logger.h"


void receive_and_log_message(ClientConnection& client_connection, FixedString& received_fixed_string) {
	received_fixed_string = client_connection.receive_message();
	if (received_fixed_string.size() == 0)
		return;
	Logger().log_info(const_cast<char*>("Message received"));
	Logger().log_info(received_fixed_string.c_str());
}

int main() {
	ClientConnection client_connection;
	FixedString received_fixed_string;
	
	client_connection.open_connection();

	Message message = MessageFactory().create_logon();
	FixedString serialized_message = message.serialize();
	client_connection.send_message(serialized_message);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_message.c_str());

	for (int i = 1; i <= 5000; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		message = MessageFactory().create_heartbeat();
		message.add_field(constants::MSG_SEQ_NUM, FixedString(i));
		message.add_field(constants::CHECKSUM, message.get_checksum());
		serialized_message = message.serialize();
		client_connection.send_message(serialized_message);
		Logger().log_info(const_cast<char*>("Message sent"));
		Logger().log_info(serialized_message.c_str());

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		i++;
		message = MessageFactory().create_resend_request(i, i);
		message.add_field(constants::MSG_SEQ_NUM, FixedString(i));
		message.add_field(constants::CHECKSUM, message.get_checksum());
		serialized_message = message.serialize();
		client_connection.send_message(serialized_message);
		Logger().log_info(const_cast<char*>("Message sent"));
		Logger().log_info(serialized_message.c_str());

		receive_and_log_message(client_connection, received_fixed_string);
	}

	serialized_message = MessageFactory().create_logout().serialize();
	client_connection.send_message(serialized_message);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_message.c_str());

	return 0;
}
