#include "../include/logger.h"


Logger::Logger() {}
	
Logger::~Logger() {}
	
void Logger::log(std::string str) {
	std::cout << str << std::endl;
}

void Logger::log(char* s) {
	std::cout << s << std::endl;
}
	
void Logger::log_error(std::string str) {
	std::cout << "Error: " << str << std::endl;
}

void Logger::log_error(char* s) {
	std::cout << "Error: " << s << std::endl;
}
	
void Logger::log_info(std::string str) {
	std::cout << "Info: " << str << std::endl;
}

void Logger::log_info(char* s) {
	std::cout << "Info: " << s << std::endl;
}
	
void Logger::log_warning(std::string str) {
	std::cout << "Warning: " << str << std::endl;
}

void Logger::log_warning(char* s) {
	std::cout << "Warning: " << s << std::endl;
}
