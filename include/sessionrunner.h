#ifndef SESSION_RUNNER_H
#define SESSION_RUNNER_H

#include "session.h"


class SessionRunner {
public:
	SessionRunner(bool is_server);
	~SessionRunner();
	void run();
private:
	Session *session_ = NULL;
};

#endif
