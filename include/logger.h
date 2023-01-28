#include <string>
#include <iostream>
#include "fixedstring.h"


class Logger {
public:
	Logger();
	~Logger();
	void log(std::string str);
	void log(char* s);
	void log_error(std::string str);
	void log_error(char* s);
	void log_info(std::string str);
	void log_info(char* s);
	void log_warning(std::string str);
	void log_warning(char* s);
};
