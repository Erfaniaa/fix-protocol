#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include "fixedstring.h"
#include "constants.h"


class Logger {
public:
	Logger() = default;
	~Logger() = default;

	static void log(const auto &message) {
		if constexpr(constants::LOG_GENERAL_MESSAGES) {
			std::cout << message << std::endl;
		}
	};

	static void log_error(const auto &message) {
		if constexpr(constants::LOG_ERRORS) {
			std::cout << "Error: " << message << std::endl;
		}
	}

	static void log_info(const auto &message) {
		if constexpr(constants::LOG_INFO) {
			std::cout << "Info: " << message << std::endl;
		}
	}

	static void log_warning(const auto &message) {
		if constexpr(constants::LOG_WARNINGS) {
			std::cout << "Warning: " << message << std::endl;
		}
	}
};

#endif
