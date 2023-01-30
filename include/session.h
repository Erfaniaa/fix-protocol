#ifndef SESSION_H
#define SESSION_H

#include <chrono>
#include <ctime>
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
	Session(bool is_server);
	~Session();
	void start();
	void end();
	void handle_logon(Message& msg);
	void handle_checksum(Message& msg);
	void handle_heart_beat(Message& msg);
	void handle_send_heart_beat_a(Message& msg);
	void handle_send_heart_beat_b(Message& msg);
	void handle_send_test_request();
	void handle_reject();
	void receive_and_handle_message();
	bool is_session_running();

private:
	bool is_user_duplicated_or_unauthenticated(Message& msg) const;
	Connection* connection_ = NULL;
	unsigned int next_msg_seq_num_ = 0;
	bool is_session_running_ = false;
	bool logon_message_received_ = false;
	bool is_server_, use_boost_ = constants::USE_BOOST;
	double heartbeat_interval = 1e9;
	std::chrono::time_point<std::chrono::system_clock> last_received_message_time = std::chrono::system_clock::now();
};

#endif
