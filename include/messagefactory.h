#include "../include/constants.h"
#include "../include/message.h"


class MessageFactory {
public:
	MessageFactory();
	static Message* MessageFactory::create_logon();
	static Message* MessageFactory::create_logout();
	static Message* MessageFactory::create_heartbeat();
	static Message* MessageFactory::create_test_request();
	static Message* MessageFactory::create_resend_request(unsigned short begin_seq_num, unsigned short end_seq_num);
	static Message* MessageFactory::create_reject(unsigned short ref_seq_num, FixedString ref_tag_id, FixedString ref_msg_type);
	static Message* MessageFactory::create_new_order_single(FixedString clordid, FixedString symbol, FixedString side, int orderQty, 
														 FixedString ordType, double price, FixedString timeInForce, 
														 FixedString orderCapacity, FixedString orderRestattribs);
	static Message* MessageFactory::create_sequence_reset(unsigned short new_seq_num, bool gap_fill_flag);
	static Message* MessageFactory::create_order_cancel_request(unsigned short orig_clord_id, unsigned short order_id, unsigned short symbol, unsigned short side);
	static Message* MessageFactory::create_order_cancel_reject(unsigned short ref_seq_num, FixedString clord_id, FixedString orig_clord_id, FixedString text);
};
