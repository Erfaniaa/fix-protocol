#include "../include/constants.h"
#include "../include/message.h"


class MessageFactory {
public:
	MessageFactory();
	static Message* MessageFactory::CreateLogon();
	static Message* MessageFactory::CreateLogout();
	static Message* MessageFactory::CreateHeartbeat();
	static Message* MessageFactory::CreateTestRequest();
	static Message* MessageFactory::CreateResendRequest(unsigned short begin_seq_num, unsigned short end_seq_num);
	static Message* MessageFactory::CreateReject(unsigned short ref_seq_num, FixedString ref_tag_id, FixedString ref_msg_type);
	static Message* MessageFactory::CreateNewOrderSingle(FixedString clordid, FixedString symbol, FixedString side, int orderQty, 
														 FixedString ordType, double price, FixedString timeInForce, 
										    			 FixedString orderCapacity, FixedString orderRestattribs);
	static Message* MessageFactory::CreateSequenceReset(unsigned short new_seq_num, bool gap_fill_flag);
	static Message* MessageFactory::CreateOrderCancelRequest(unsigned short orig_clord_id, unsigned short order_id, unsigned short symbol, unsigned short side);
	static Message* MessageFactory::CreateOrderCancelReject(unsigned short ref_seq_num, FixedString clord_id, FixedString orig_clord_id, FixedString text);
};
