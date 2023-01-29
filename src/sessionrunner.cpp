#include "../include/sessionrunner.h"


SessionRunner::SessionRunner(bool is_server) {
	session_ = new Session(is_server);
}

SessionRunner::~SessionRunner() {
	if (session_ != NULL)
		delete session_;
}

void SessionRunner::run() {
	session_->start();
	while (session_->is_session_running()) {
		session_->receive_and_handle_message();
	}
}
