#include "../include/messagefactory.h"


MessageFactory::MessageFactory() {}

Message* MessageFactory::CreateLogon() {
	Message* msg = new Message();
	msg->add_field(constants::ENCRYPT_METHOD, "0");
	msg->add_field(constants::HEART_BT_INT, "30");
	msg->add_field(constants::RESET_SEQ_NUM_FLAG, "Y");
	msg->add_field(constants::SENDER_COMP_ID, constants::SENDER_COMP_ID_VALUE);
	msg->add_field(constants::TARGET_COMP_ID, constants::TARGET_COMP_ID_VALUE);
	return msg;
}

Message* MessageFactory::CreateLogout() {
	Message* msg = new Message();
	msg->add_field(constants::TEXT, "Closing connection");
	return msg;
}

Message* MessageFactory::CreateHeartbeat() {
	Message* msg = new Message();
	return msg;
}

Message* MessageFactory::CreateTestRequest() {
	Message* msg = new Message();
	msg->add_field(constants::TEST_REQ_ID, "Test Request ID");
	return msg;
}

Message* MessageFactory::CreateResendRequest(unsigned short begin_seq_num, unsigned short end_seq_num) {
	Message* msg = new Message();
	msg->add_field(constants::BEGIN_SEQ_NUM, std::to_string(begin_seq_num));
	msg->add_field(constants::END_SEQ_NUM, std::to_string(end_seq_num));
	return msg;
}

Message* MessageFactory::CreateReject(unsigned short ref_seq_num, FixedString ref_tag_id, FixedString ref_msg_type) {
	Message* msg = new Message();
	msg->add_field(constants::REF_SEQ_NUM, std::to_string(ref_seq_num));
	msg->add_field(constants::REF_TAG_ID, ref_tag_id);
	msg->add_field(constants::REF_MSG_TYPE, ref_msg_type);
	return msg;
}
