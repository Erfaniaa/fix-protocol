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
	static Message* create_reject(unsigned short ref_seq_num, FixedString ref_tag_id, FixedString ref_msg_type);
	static Message* create_new_order_single(FixedString clordid, FixedString symbol, FixedString side, int orderQty, 
														 FixedString ordType, double price, FixedString timeInForce, 
														 FixedString orderCapacity, FixedString orderRestattribs);
	static Message* create_sequence_reset(unsigned short new_seq_num, bool gap_fill_flag);
	static Message* create_order_cancel_request(unsigned short orig_clord_id, unsigned short order_id, unsigned short symbol, unsigned short side);
	static Message* create_order_cancel_reject(unsigned short ref_seq_num, FixedString clord_id, FixedString orig_clord_id, FixedString text);
};

#endif
