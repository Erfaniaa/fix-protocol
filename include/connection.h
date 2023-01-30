#ifndef CONNECTION_H
#define CONNECTION_H

#include "fixedstring.h"


class Connection {
public:
	virtual void open_connection() = 0;
	virtual void close_connection() = 0;
	virtual void send_message(FixedString message) = 0;
	virtual FixedString receive_message() = 0;
	virtual bool is_connected() = 0;
};

#endif
