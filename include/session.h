#ifndef SESSION_H
#define SESSION_H

#include "serverconnection.h"
#include "message.h"
#include "messagefactory.h"
#include "constants.h"


class Session {
public:
	Session();
	~Session();
	void start();
	void end();
	void handle_logon(Message& msg);
	void receive_and_handle_message();
	bool is_session_running();
private:
	bool is_user_duplicated_or_unauthenticated(Message& msg) const;
	ServerConnection connection_;
	unsigned int next_msg_seq_num_ = 0;
	bool is_session_running_ = false;
};

#endif
