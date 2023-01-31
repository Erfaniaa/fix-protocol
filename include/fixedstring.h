#ifndef FIXED_STRING_H
#define FIXED_STRING_H

#include <cstddef>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <boost/array.hpp>
#include "fixedvector.h"
#include "constants.h"
#include "logger.h"


class FixedString {
public:
	FixedString();
	~FixedString();
	FixedString(const std::string& str);
	FixedString(const char* str);
	FixedString(unsigned int x);
	void push_back(const char& value);
	void pop_back();
	std::size_t size() const;
	char& operator[](std::size_t index);
	const char& operator[](std::size_t index) const;
	FixedString& operator=(const char* str);
	FixedString& operator=(const FixedString& other);
	FixedString& operator=(unsigned int x);
	void operator=(const std::string& str);
	bool operator==(const FixedString& other) const;
	bool operator==(const std::string& other) const;
	FixedVector<FixedString> split(const char& delimiter);
	const char* c_str() const;
	boost::array<char, constants::MAX_MESSAGE_LENGTH> to_boost_array() const;
	int to_int() const;
	void clear();
	FixedString get_checksum();
	FixedString& operator+=(const FixedString& other);

private:
	static constexpr std::size_t kMaxSize = constants::MAX_MESSAGE_LENGTH;
	std::size_t size_;
	char data_[constants::MAX_MESSAGE_LENGTH + 1];
};

#endif
