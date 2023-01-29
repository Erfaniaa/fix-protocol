#include "../include/sessionrunner.h"


SessionRunner::SessionRunner() {}

SessionRunner::~SessionRunner() {}

void SessionRunner::run() {
	session_.start();
	while (session_.is_session_running()) {
		session_.receive_and_handle_message();
	}
}
