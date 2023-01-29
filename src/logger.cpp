#include "../include/logger.h"


Logger::Logger() {}
	
Logger::~Logger() {}
	
void Logger::log(std::string str) {
	if (constants::LOG_GENERAL_MESSAGES)
		std::cout << str << std::endl;
}

void Logger::log(char* s) {
	if (constants::LOG_GENERAL_MESSAGES)
		std::cout << s << std::endl;
}
	
void Logger::log_error(std::string str) {
	if (constants::LOG_ERRORS)
		std::cout << "Error: " << str << std::endl;
}

void Logger::log_error(char* s) {
	if (constants::LOG_ERRORS)
		std::cout << "Error: " << s << std::endl;
}
	
void Logger::log_info(std::string str) {
	if (constants::LOG_INFO)
		std::cout << "Info: " << str << std::endl;
}

void Logger::log_info(char* s) {
	if (constants::LOG_INFO)
		std::cout << "Info: " << s << std::endl;
}
	
void Logger::log_warning(std::string str) {
	if (constants::LOG_WARNINGS)
		std::cout << "Warning: " << str << std::endl;
}

void Logger::log_warning(char* s) {
	if (constants::LOG_WARNINGS)
		std::cout << "Warning: " << s << std::endl;
}
