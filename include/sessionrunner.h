#ifndef SESSION_RUNNER_H
#define SESSION_RUNNER_H

#include "session.h"


class SessionRunner {
public:
	SessionRunner();
	~SessionRunner();
	void run();
private:
	Session session_;
};

#endif
