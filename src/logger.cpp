#include "../include/logger.h"


Logger::Logger(std::string filename) : file_(filename) {}
	
Logger::~Logger() {
	file_.close();
}
	
void Logger::log(std::string str) {
	file_ << str << std::endl;
}

void Logger::log(char* s) {
	file_ << s << std::endl;
}
	
void Logger::log_error(std::string str) {
	file_ << "Error: " << str << std::endl;
}

void Logger::log_error(char* s) {
	file_ << "Error: " << s << std::endl;
}
	
void Logger::log_info(std::string str) {
	file_ << "Info: " << str << std::endl;
}

void Logger::log_info(char* s) {
	file_ << "Info: " << s << std::endl;
}
	
void Logger::log_warning(std::string str) {
	file_ << "Warning: " << str << std::endl;
}

void Logger::log_warning(char* s) {
	file_ << "Warning: " << s << std::endl;
}
