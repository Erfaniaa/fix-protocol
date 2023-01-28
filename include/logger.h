#include <string>
#include <fstream>
#include "fixedstring.h"


class Logger {
public:
	Logger(std::string filename);
	~Logger();
	void log(std::string str);
	void log(char* s);
	void log_error(std::string str);
	void log_error(char* s);
	void log_info(std::string str);
	void log_info(char* s);
	void log_warning(std::string str);
	void log_warning(char* s);

private:
	std::ofstream file_;
};
