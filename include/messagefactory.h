#ifndef MESSAGE_FACTORY_H
#define MESSAGE_FACTORY_H

#include "../include/constants.h"
#include "../include/message.h"


class MessageFactory {
public:
	MessageFactory();
	static Message* create_logon();
	static Message* create_logout();
	static Message* create_heartbeat();
	static Message* create_test_request();
	static Message* create_resend_request(unsigned short begin_seq_num, unsigned short end_seq_num);
	static Message* create_reject(unsigned short ref_seq_num, const FixedString& ref_tag_id, const FixedString& ref_msg_type);
	static Message* create_new_order_single(const FixedString& clordid, const FixedString& symbol, const FixedString& side, int order_qty, 
											const FixedString& ord_type, double price, const FixedString& time_in_force, 
											const FixedString& order_capacity, const FixedString& order_restattribs);
	static Message* create_sequence_reset(unsigned short new_seq_num, bool gap_fill_flag);
	static Message* create_order_cancel_request(unsigned short orig_clord_id, unsigned short order_id, unsigned short symbol, unsigned short side);
	static Message* create_order_cancel_reject(unsigned short ref_seq_num, const FixedString& clord_id, const FixedString& orig_clord_id, const FixedString& text);
	static Message* create_empty_checksum();
	static Message* create_heartbeat_with_test_req_id(const FixedString& test_req_id_value);
};

#endif
