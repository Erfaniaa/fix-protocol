#include "../include/session.h"


Session::Session(bool is_server) {
	is_server_ = is_server;
	if constexpr (use_boost_) {
		if (is_server_)
			connection_ = std::make_unique<BoostServerConnection>();
		else
			connection_ = std::make_unique<BoostClientConnection>();
	}
	else {
		if (is_server_)
			connection_ = std::make_unique<ServerConnection>();
		else
			connection_ = std::make_unique<ClientConnection>();
	}
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
		std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - last_received_message_time_;
		if (elapsed_seconds > (std::chrono::duration<double>)(heartbeat_interval_ * 1.2)) {
			Logger().log_info(const_cast<char*>("No messages received for a while"));
			handle_send_test_request(); //Scenario 6
		}
		else if (elapsed_seconds > (std::chrono::duration<double>)heartbeat_interval_) {
			Logger().log_info(const_cast<char*>("No messages received for a while"));
			handle_send_heart_beat_a(msg); //Scenario 4_a
		}
		return;
	}
	received_valid_message_ = true;
	last_received_message_time_ = std::chrono::system_clock::now();
	Logger().log_info(const_cast<char*>("Message received"));
	Logger().log_info(msg.serialize().c_str());
	if (!logon_message_received_) {
		handle_logon(msg); //Scenario 1B, 1S and 2S
		return;
	}
	if (msg.has_tag(constants::CHECKSUM)) {
		handle_checksum(msg); //Scenario 3
	}
	if (received_valid_message_)
		handle_message_standard_header(msg); //Scenario 2_a, 2_b, and 2_c
	if (received_valid_message_) {
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
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::RESEND_REQUEST) {
			handle_resend_request(); //Scenario 8
			return;
		}
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::LOGOUT) {
			handle_logout(); //Scenario 12 and 13
			return;
		}
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::SEQUENCE_RESET_MSG_TYPE) {
			if (msg.get_tag_value(constants::GAP_FILL_FLAG) == FixedString("Y")) {
				handle_sequence_reset_gap_fill(msg); //Scenario 10
				return;
			}
		}
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::SEQUENCE_RESET_MSG_TYPE) {
			if (msg.get_tag_value(constants::GAP_FILL_FLAG) == FixedString("N")) {
				handle_sequence_reset_reset(msg); //Scenario 11
				return;
			}
		}
		Logger().log_warning(const_cast<char *>("Ingoring message because it is invalid or garbled")); //Scenario 2_d
	}
}

void Session::handle_logon(Message& msg) {
	if (msg.get_tag_value(constants::MSG_TYPE) == constants::LOGON) {
		if (msg.get_tag_value(constants::MSG_SEQ_NUM).to_int() > next_msg_seq_num_) {
			FixedString serialized_response = MessageFactory().create_resend_request(next_msg_seq_num_, next_msg_seq_num_).serialize();
			connection_->send_message(serialized_response);
			Logger().log_info(const_cast<char*>("Message sent"));
			Logger().log_info(serialized_response.c_str());
		}
		else {
			logon_message_received_ = true;
			next_msg_seq_num_ = msg.get_tag_value(constants::MSG_SEQ_NUM).to_int() + 1;
			FixedString serialized_response = MessageFactory().create_logon().serialize();
			connection_->send_message(serialized_response);
			Logger().log_info(const_cast<char*>("Message sent"));
			Logger().log_info(serialized_response.c_str());
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
		received_valid_message_ = false;
		return;
	}
	bool msg_checksum_value_has_length_3 = (msg.get_tag_value(constants::CHECKSUM).size() == 3);
	if (!msg_checksum_value_has_length_3) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		received_valid_message_ = false;
		return;
	}
	bool msg_ended_by_checksum_tag =
		(serialized_message[(int)serialized_message.size() - 7] == '1') &&
		(serialized_message[(int)serialized_message.size() - 6] == '0');
	if (!msg_checksum_value_has_length_3) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		received_valid_message_ = false;
		return;
	}
	bool msg_checksum_correct = (msg.get_checksum() == msg.get_tag_value(constants::CHECKSUM));
	if (!msg_checksum_correct) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		received_valid_message_ = false;
		return;
	}
}

void Session::handle_heart_beat(Message& msg) {
	if (msg.has_tag(constants::HEART_BT_INT)) {
		heartbeat_interval_ = std::stod(msg.get_tag_value(constants::HEART_BT_INT).c_str());
	}
	next_msg_seq_num_++;
	//Accept message
}

void Session::handle_send_heart_beat_a(Message& msg) {
	FixedString serialized_response = MessageFactory().create_heartbeat().serialize();
	connection_->send_message(serialized_response);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_response.c_str());
	next_msg_seq_num_++;
	//Accept message
}

void Session::handle_send_heart_beat_b(Message& msg) {
	FixedString test_req_id = msg.get_tag_value(constants::TEST_REQ_ID);
	FixedString serialized_response = MessageFactory().create_heartbeat_with_test_req_id(test_req_id).serialize();
	connection_->send_message(serialized_response);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_response.c_str());
	next_msg_seq_num_++;
	//Accept message
}

void Session::handle_send_test_request() {
	FixedString serialized_response = MessageFactory().create_heartbeat_with_test_req_id(constants::TEST_REQ_ID_VALUE).serialize();
	connection_->send_message(serialized_response);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_response.c_str());
	next_msg_seq_num_++;
	//Accept message
}

void Session::handle_reject() {
	next_msg_seq_num_++;
	//Accept message
}

void Session::handle_resend_request() {
	FixedString serialized_response = MessageFactory().create_resend_request(next_msg_seq_num_, next_msg_seq_num_).serialize();
	connection_->send_message(serialized_response);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_response.c_str());
	next_msg_seq_num_++;
	//Accept message
}

void Session::handle_message_standard_header(Message& msg) {
	unsigned int msg_seq_num = msg.get_tag_value(constants::MSG_SEQ_NUM).to_int();
	if (msg_seq_num == next_msg_seq_num_) {
		//Accept msg_seq_num
	}
	else if (msg_seq_num > next_msg_seq_num_) {
		FixedString serialized_response = MessageFactory().create_resend_request(next_msg_seq_num_, next_msg_seq_num_).serialize();
		connection_->send_message(serialized_response);
		Logger().log_info(const_cast<char*>("Message sent"));
		Logger().log_info(serialized_response.c_str());
		received_valid_message_ = false;
	} else if (msg_seq_num < next_msg_seq_num_) {
		if (!(msg.get_tag_value(constants::POSS_DUP_FLAG) == FixedString("Y")))
			if (!(msg.get_tag_value(constants::MSG_TYPE) == constants::SEQUENCE_RESET_MSG_TYPE)) {
				FixedString serialized_response = MessageFactory().create_logout().serialize();
				connection_->send_message(serialized_response);
				Logger().log_info(const_cast<char*>("Message sent"));
				Logger().log_info(serialized_response.c_str());
				Logger().log_error(const_cast<char*>("MsgSeqNum too low"));
				end();
			}
	}
}

void Session::handle_sequence_reset_gap_fill(Message& msg) {
	if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() > msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()) {
		if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() > next_msg_seq_num_) {
			FixedString serialized_response = MessageFactory().create_resend_request(next_msg_seq_num_, msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()).serialize();
			connection_->send_message(serialized_response);
			Logger().log_info(const_cast<char*>("Message sent"));
			Logger().log_info(serialized_response.c_str());
			return;
		}
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() > msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()) {
		if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() == next_msg_seq_num_) {
			next_msg_seq_num_ = msg.get_tag_value(constants::NEW_SEQ_NUM).to_int();
			return;
		}
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() > msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()) {
		if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() < next_msg_seq_num_) {
			if (msg.get_tag_value(constants::POSS_DUP_FLAG) == FixedString("Y")) {
				// ignore message
				return;
			}
		}
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() > msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()) {
		if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() < next_msg_seq_num_) {
			if (!(msg.get_tag_value(constants::POSS_DUP_FLAG) == FixedString("Y"))) {
				FixedString serialized_response = MessageFactory().create_logout().serialize();
				connection_->send_message(serialized_response);
				Logger().log_info(const_cast<char*>("Message sent"));
				Logger().log_info(serialized_response.c_str());
				Logger().log_error(const_cast<char*>("MsgSeqNum too low"));
				end();
				return;			
			}
		}
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() <= msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()) {
		if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() == next_msg_seq_num_) {
			FixedString serialized_response = MessageFactory().create_reject(next_msg_seq_num_,
																			 FixedString(constants::MSG_SEQ_NUM),
																			 FixedString("attempt to lower sequence number, invalid value NewSeqNo(36)")).serialize();
			connection_->send_message(serialized_response);
			Logger().log_info(const_cast<char*>("Message sent"));
			Logger().log_info(serialized_response.c_str());
			Logger().log_info(const_cast<char*>("MsgSeqNum too low"));
		}
	}
}

void Session::handle_sequence_reset_reset(Message& msg) {
	if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() > next_msg_seq_num_) {
		next_msg_seq_num_ = msg.get_tag_value(constants::NEW_SEQ_NUM).to_int();
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() == next_msg_seq_num_) {
		next_msg_seq_num_ = msg.get_tag_value(constants::NEW_SEQ_NUM).to_int();
		Logger().log_warning(const_cast<char*>("NewSeqNo(36) = NextNumIn"));
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() < next_msg_seq_num_) {
		Message response = MessageFactory().create_reject(next_msg_seq_num_,
														  FixedString(constants::MSG_SEQ_NUM),
														  FixedString(""));
		response.add_field(constants::SESSION_REJECT_REASON, "5");
		FixedString serialized_response = response.serialize();
		connection_->send_message(serialized_response);
		Logger().log_info(const_cast<char*>("Message sent"));
		Logger().log_info(serialized_response.c_str());
	}
}

void Session::handle_logout() {
	end();
	//Accept message and end session
}

bool Session::is_session_running() {
	return is_session_running_;
}

bool Session::is_user_duplicated_or_unauthenticated(Message& msg) const {
	return false; // Assuming that we have only one user and one active connection
}
