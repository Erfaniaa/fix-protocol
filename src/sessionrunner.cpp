#include "../include/sessionrunner.h"


SessionRunner::SessionRunner(bool is_server) {
	session_ = std::make_unique<Session>(is_server);
}

void SessionRunner::run() {
	session_->start();
	while (session_->is_session_running()) {
		session_->receive_and_handle_message();
	}
}
