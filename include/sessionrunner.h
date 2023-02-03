#ifndef SESSION_RUNNER_H
#define SESSION_RUNNER_H

#include <memory>

#include "session.h"


class SessionRunner {
public:
	SessionRunner(bool is_server);
	~SessionRunner() = default;
	void run();
private:
	std::unique_ptr<Session> session_;
};

#endif
