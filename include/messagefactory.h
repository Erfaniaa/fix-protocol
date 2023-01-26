#include "../include/constants.h"
#include "../include/message.h"


class MessageFactory {
public:
	MessageFactory();
	static Message* MessageFactory::CreateLogon();
	static Message* MessageFactory::CreateLogout();
	static Message* MessageFactory::CreateHeartbeat();
	static Message* MessageFactory::CreateTestRequest();
	static Message* MessageFactory::CreateResendRequest(unsigned short beginSeqNum, unsigned short endSeqNum);
	static Message* MessageFactory::CreateReject(unsigned short refSeqNum, FixedString refTagId, FixedString refMsgType);
};
