#include "../include/session.h"


Session::Session(bool is_server, bool use_boost) {
	is_server_ = is_server;
	use_boost_ = use_boost;
	if (use_boost) {
		if (is_server)
			connection_ = new BoostServerConnection();
		else
			connection_ = new BoostClientConnection();
	}
	else {
		if (is_server)
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
	Logger().log_info("Message received");
	Logger().log_info(msg.serialize().c_str());
	if (!logon_message_received_) {
		handle_logon(msg);
	}
}

void Session::handle_logon(Message& msg) {
	if (msg.get_tag_value(constants::MSG_TYPE) == constants::LOGON) {
		if (msg.get_tag_value(constants::MSG_SEQ_NUM).to_int() > next_msg_seq_num_) {
			FixedString fixed_string = MessageFactory().create_resend_request(next_msg_seq_num_, next_msg_seq_num_)->serialize();
			connection_->send_message(fixed_string);
		}
		else {
			logon_message_received_ = true;
			next_msg_seq_num_ = msg.get_tag_value(constants::MSG_SEQ_NUM).to_int() + 1;
			connection_->send_message(MessageFactory().create_logon()->serialize());
		}
	} else if (is_server_ && is_user_duplicated_or_unauthenticated(msg)) {
		Logger().log_error("duplicated/unauthenticated/non-configured identity");
		end();
	} else {
		Logger().log_error("invalid Logon message");
		connection_->send_message(MessageFactory().create_logout()->serialize());
		end();
	}
}

bool Session::is_session_running() {
	return is_session_running_;
}

bool Session::is_user_duplicated_or_unauthenticated(Message& msg) const {
	return false; // Assuming that we have only one user and one active connection
}
