#include "../include/session.h"


Session::Session() {}

Session::~Session() {}

void Session::start() {
	connection_.open_connection();
	is_session_running_ = true;
}

void Session::end() {
	connection_.close_connection();
	is_session_running_ = false;
}

void Session::handle_logon(Message& msg) {
	if (msg.get_tag_value(constants::MSG_TYPE) == constants::LOGON) {
		if (msg.get_tag_value(constants::MSG_SEQ_NUM).to_int() > next_msg_seq_num_) {
			FixedString fixed_string = MessageFactory().create_resend_request(next_msg_seq_num_, next_msg_seq_num_)->serialize();
			connection_.send_message(fixed_string);
		}
		else {
			next_msg_seq_num_ = msg.get_tag_value(constants::MSG_SEQ_NUM).to_int() + 1;
			connection_.send_message(MessageFactory().create_logon()->serialize());
		}
	} else if (is_user_duplicated_or_unauthenticated(msg)) {
		Logger().log_error("duplicated/unauthenticated/non-configured identity");
		end();
	} else {
		Logger().log_error("invalid Logon message");
		connection_.send_message(MessageFactory().create_logout()->serialize());
		end();
	}
}

bool Session::is_session_running() {
	return is_session_running_;
}

bool Session::is_user_duplicated_or_unauthenticated(Message& msg) const {
	return msg.get_tag_value(constants::SENDER_COMP_ID) == constants::SENDER_COMP_ID_VALUE &&
		   msg.get_tag_value(constants::TARGET_COMP_ID) == constants::TARGET_COMP_ID_VALUE &&
		   msg.get_tag_value(constants::SENDER_SUB_ID) == constants::SENDER_SUB_ID_VALUE &&
		   msg.get_tag_value(constants::SENDER_LOC_ID) == constants::SENDER_LOC_ID_VALUE &&
		   msg.get_tag_value(constants::TARGET_SUB_ID) == constants::TARGET_SUB_ID_VALUE &&
		   msg.get_tag_value(constants::TARGET_LOC_ID) == constants::TARGET_LOC_ID_VALUE;
}
