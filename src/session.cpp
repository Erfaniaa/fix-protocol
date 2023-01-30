#include "../include/session.h"


Session::Session(bool is_server) {
	is_server_ = is_server;
	if (use_boost_) {
		if (is_server_)
			connection_ = new BoostServerConnection();
		else
			connection_ = new BoostClientConnection();
	}
	else {
		if (is_server_)
			connection_ = new ServerConnection();
		else
			connection_ = new ClientConnection();
	}
}

Session::~Session() {
	if (connection_ != NULL)
		delete connection_;
}

void Session::start() {
	connection_->open_connection();
	is_session_running_ = true;
}

void Session::end() {
	connection_->close_connection();
	is_session_running_ = false;
}

void Session::receive_and_handle_message() {
	Message msg = connection_->receive_message();
	if (msg.serialize().size() == 0) {
		std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - last_received_message_time;
		if (elapsed_seconds > (std::chrono::duration<double>)(heartbeat_interval * 1.2)) {
			Logger().log_info(const_cast<char*>("No messages received for a while"));
			handle_send_test_request(); //Scenario 6
		}
		else if (elapsed_seconds > (std::chrono::duration<double>)heartbeat_interval) {
			Logger().log_info(const_cast<char*>("No messages received for a while"));
			handle_send_heart_beat_a(msg); //Scenario 4_a
		}
		return;
	}
	last_received_message_time = std::chrono::system_clock::now();
	Logger().log_info(const_cast<char*>("Message received"));
	Logger().log_info(msg.serialize().c_str());
	if (!logon_message_received_) {
		handle_logon(msg); //Scenario 1B, 1S and 2S
		return;
	}
	if (msg.has_tag(constants::CHECKSUM)) {
		handle_checksum(msg); //Scenario 3
		return;
	}
	if (msg.get_tag_value(constants::MSG_TYPE) == constants::TEST_REQUEST) {
		handle_send_heart_beat_b(msg); //Scenario 4_b
		return;
	}
	if (msg.get_tag_value(constants::MSG_TYPE) == constants::HEART_BEAT) {
		handle_heart_beat(msg); //Scenario 5
		return;
	}
	if (msg.get_tag_value(constants::MSG_TYPE) == constants::REJECT) {
		handle_reject(); //Scenario 7
		return;
	}
	Logger().log_warning(const_cast<char *>("Ingoring message because it is invalid or garbled"));
}

void Session::handle_logon(Message& msg) {
	if (msg.get_tag_value(constants::MSG_TYPE) == constants::LOGON) {
		if (msg.get_tag_value(constants::MSG_SEQ_NUM).to_int() > next_msg_seq_num_) {
			FixedString fixed_string = MessageFactory().create_resend_request(next_msg_seq_num_, next_msg_seq_num_).serialize();
			connection_->send_message(fixed_string);
		}
		else {
			logon_message_received_ = true;
			next_msg_seq_num_ = msg.get_tag_value(constants::MSG_SEQ_NUM).to_int() + 1;
			connection_->send_message(MessageFactory().create_logon().serialize());
		}
	} else if (is_server_ && is_user_duplicated_or_unauthenticated(msg)) {
		Logger().log_error(const_cast<char*>("duplicated/unauthenticated/non-configured identity"));
		end();
	} else {
		Logger().log_error(const_cast<char*>("invalid Logon message (the first message must be Logon)"));
		connection_->send_message(MessageFactory().create_logout().serialize());
		end();
	}
}

void Session::handle_checksum(Message& msg) {
	FixedString serialized_message = msg.serialize();
	bool msg_ended_by_soh = (serialized_message[(int)serialized_message.size() - 1] == constants::SOH[0]);
	if (!msg_ended_by_soh) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		return;
	}
	bool msg_has_checksum_tag = msg.has_tag(constants::CHECKSUM);
	if (!msg_has_checksum_tag) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		return;
	}
	bool msg_checksum_value_has_length_3 = (msg.get_tag_value(constants::CHECKSUM).size() == 3);
	if (!msg_checksum_value_has_length_3) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		return;
	}
	bool msg_ended_by_checksum_tag =
		(serialized_message[(int)serialized_message.size() - 7] == '1') &&
		(serialized_message[(int)serialized_message.size() - 6] == '0');
	if (!msg_checksum_value_has_length_3) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		return;
	}
	bool msg_checksum_correct = (serialized_message.get_checksum() == msg.get_tag_value(constants::CHECKSUM));
	if (!msg_checksum_correct) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		return;
	}
	else {
		next_msg_seq_num_++;
		//Accept message
	}
}

void Session::handle_heart_beat(Message& msg) {
	if (msg.has_tag(constants::HEART_BT_INT)) {
		heartbeat_interval = std::stod(msg.get_tag_value(constants::HEART_BT_INT).c_str());
	}
	next_msg_seq_num_++;
	//Accept message
}

void Session::handle_send_heart_beat_a(Message& msg) {
	connection_->send_message(MessageFactory().create_heartbeat().serialize());
	next_msg_seq_num_++;
	//Accept message
}

void Session::handle_send_heart_beat_b(Message& msg) {
	FixedString test_req_id = msg.get_tag_value(constants::TEST_REQ_ID);
	connection_->send_message(MessageFactory().create_heartbeat_with_test_req_id(test_req_id).serialize());
	next_msg_seq_num_++;
	//Accept message
}

void Session::handle_send_test_request() {
	connection_->send_message(MessageFactory().create_heartbeat_with_test_req_id(constants::TEST_REQ_ID_VALUE).serialize());
	next_msg_seq_num_++;
	//Accept message
}

void Session::handle_reject() {
	next_msg_seq_num_++;
	//Accept message
}

bool Session::is_session_running() {
	return is_session_running_;
}

bool Session::is_user_duplicated_or_unauthenticated(Message& msg) const {
	return false; // Assuming that we have only one user and one active connection
}
