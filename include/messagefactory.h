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
};
