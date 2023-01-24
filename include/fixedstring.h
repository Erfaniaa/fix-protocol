#ifndef FIXED_STRING_H
#define FIXED_STRING_H

#include <cstddef>
#include <cstring>
#include <string>
#include <vector>

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

private:
	static constexpr std::size_t MaxSize = 1024;
	std::size_t size_;
	char data_[MaxSize + 1];
};

#endif
