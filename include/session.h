#ifndef SESSION_H
#define SESSION_H

#include "connection.h"
#include "clientconnection.h"
#include "serverconnection.h"
#include "boostclientconnection.h"
#include "boostserverconnection.h"
#include "message.h"
#include "messagefactory.h"
#include "constants.h"


class Session {
public:
	Session(bool is_server, bool use_boost);
	~Session();
	void start();
	void end();
	void handle_logon(Message& msg);
	void receive_and_handle_message();
	bool is_session_running();
private:
	bool is_user_duplicated_or_unauthenticated(Message& msg) const;
	Connection* connection_ = NULL;
	unsigned int next_msg_seq_num_ = 0;
	bool is_session_running_ = false;
	bool logon_message_received_ = false;
	bool is_server_, use_boost_;
};

#endif
