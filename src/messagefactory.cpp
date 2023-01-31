#include "../include/messagefactory.h"


MessageFactory::MessageFactory() {}

Message MessageFactory::create_logon() {
	Message msg;
	msg.add_field(constants::MSG_TYPE, constants::LOGON);
	msg.add_field(constants::ENCRYPT_METHOD, "0");
	msg.add_field(constants::HEART_BT_INT, "30");
	msg.add_field(constants::SEQUENCE_RESET, "Y");
	msg.add_field(constants::SENDER_COMP_ID, constants::SENDER_COMP_ID_VALUE);
	msg.add_field(constants::TARGET_COMP_ID, constants::TARGET_COMP_ID_VALUE);
	return msg;
}

Message MessageFactory::create_logout() {
	Message msg;
	msg.add_field(constants::MSG_TYPE, constants::LOGOUT);
	msg.add_field(constants::TEXT, "Closing connection");
	return msg;
}

Message MessageFactory::create_heartbeat() {
	Message msg;
	msg.add_field(constants::MSG_TYPE, constants::HEART_BEAT);
	return msg;
}

Message MessageFactory::create_test_request() {
	Message msg;
	msg.add_field(constants::MSG_TYPE, constants::TEST_REQUEST);
	msg.add_field(constants::TEST_REQ_ID, "Test Request ID");
	return msg;
}

Message MessageFactory::create_resend_request(unsigned short begin_seq_num, unsigned short end_seq_num) {
	Message msg;
	msg.add_field(constants::MSG_TYPE, constants::RESEND_REQUEST);
	msg.add_field(constants::GAP_FILL_FLAG, "Y");
	msg.add_field(constants::BEGIN_SEQ_NUM, std::to_string(begin_seq_num));
	msg.add_field(constants::END_SEQ_NUM, std::to_string(end_seq_num));
	return msg;
}

Message MessageFactory::create_reject(unsigned short ref_seq_num, const FixedString& ref_tag_id, const FixedString& ref_msg_type) {
	Message msg;
	msg.add_field(constants::MSG_TYPE, constants::REJECT);
	msg.add_field(constants::REF_SEQ_NUM, std::to_string(ref_seq_num));
	msg.add_field(constants::REF_TAG_ID, ref_tag_id);
	msg.add_field(constants::REF_MSG_TYPE, ref_msg_type);
	return msg;
}

Message MessageFactory::create_new_order_single(const FixedString& clordid, const FixedString& symbol, const FixedString& side, int order_qty, 
												 const FixedString& ord_type, double price, const FixedString& time_in_force, 
										    	 const FixedString& order_capacity, const FixedString& order_restattribs) {
    Message msg;
	msg.add_field(constants::MSG_TYPE, constants::NEW_ORDER_SINGLE);
	msg.add_field(constants::CLORDID, clordid);
	msg.add_field(constants::SYMBOL, symbol);
	msg.add_field(constants::SIDE, side);
	msg.add_field(constants::ORDER_QTY, std::to_string(order_qty));
	msg.add_field(constants::ORDER_TYPE, ord_type);
	msg.add_field(constants::PRICE, std::to_string(price));
	msg.add_field(constants::TIME_IN_FORCE, time_in_force);
	msg.add_field(constants::ORDER_CAPACITY, order_capacity);
	msg.add_field(constants::ORDER_RESTATTRIBS, order_restattribs);
    return msg;
}

Message MessageFactory::create_sequence_reset(unsigned short new_seq_num, bool gap_fill_flag) {
	Message msg;
	msg.add_field(constants::MSG_TYPE, constants::SEQUENCE_RESET);
	msg.add_field(constants::NEW_SEQ_NUM, std::to_string(new_seq_num));
	if (gap_fill_flag) {
		msg.add_field(constants::GAP_FILL_FLAG, "Y");
	}
	return msg;
}

Message MessageFactory::create_order_cancel_request(unsigned short orig_clord_id, unsigned short order_id, unsigned short symbol, unsigned short side) {
	Message msg;
	msg.add_field(constants::MSG_TYPE, constants::ORDER_CANCEL_REQUEST);
	msg.add_field(constants::ORIG_CLORD_ID, std::to_string(orig_clord_id));
	msg.add_field(constants::ORDER_ID, std::to_string(order_id));
	msg.add_field(constants::SYMBOL, std::to_string(symbol));
	msg.add_field(constants::SIDE, std::to_string(side));
	return msg;
}

Message MessageFactory::create_order_cancel_reject(unsigned short ref_seq_num, const FixedString& clord_id, const FixedString& orig_clord_id, const FixedString& text) {
	Message msg;
	msg.add_field(constants::MSG_TYPE, constants::ORDER_CANCEL_REJECT);
	msg.add_field(constants::REF_SEQ_NUM, std::to_string(ref_seq_num));
	msg.add_field(constants::CLORDID, clord_id);
	msg.add_field(constants::ORIG_CLORD_ID, orig_clord_id);
	msg.add_field(constants::TEXT, text);
	return msg;
}

Message MessageFactory::create_empty_checksum() {
	Message msg;
	msg.add_field(constants::CHECKSUM, "000");
	return msg;
}

Message MessageFactory::create_heartbeat_with_test_req_id(const FixedString& test_req_id_value) {
	Message msg;
	msg.add_field(constants::MSG_TYPE, constants::HEART_BEAT);
	msg.add_field(constants::TEST_REQ_ID, test_req_id_value);
	return msg;
}
