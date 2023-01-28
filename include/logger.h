#ifndef LOGGER_H
#define LOGGER

#include <string>
#include <iostream>
#include "fixedstring.h"


class Logger {
public:
	Logger();
	~Logger();
	static void log(std::string str);
	static void log(char* s);
	static void log_error(std::string str);
	static void log_error(char* s);
	static void log_info(std::string str);
	static void log_info(char* s);
	static void log_warning(std::string str);
	static void log_warning(char* s);
};

#endif
