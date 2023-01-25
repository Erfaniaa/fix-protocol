#ifndef FIXED_STRING_H
#define FIXED_STRING_H

#include <cstddef>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <boost/array.hpp>
#include "../include/constants.h"

class FixedString {
public:
	FixedString();
	FixedString(const std::string& str);
	FixedString(const char* str);
	void push_back(const char& value);
	void pop_back();
	std::size_t size() const;
	char& operator[](std::size_t index);
	const char& operator[](std::size_t index) const;
	FixedString& operator=(const char* str);
	void FixedString::operator=(const std::string& str);
	bool operator==(const FixedString& other) const;
	FixedString& operator+(const FixedString& other);
	std::vector<FixedString> FixedString::split(const char& delimiter);
	const char* c_str() const;
	boost::array<char, constants::MAX_MESSAGE_LENGTH> to_boost_array() const;
	std::ostream& operator<<(std::ostream& os);
	std::istream& operator>>(std::istream& is);

private:
	static constexpr std::size_t kMaxSize = constants::MAX_MESSAGE_LENGTH;
	std::size_t size_;
	char data_[kMaxSize + 1];
};

#endif
