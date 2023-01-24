#include <cstddef>
#include <cstring>
#include <string>
#include <stdexcept>
#include <iostream>
#include "../include/fixedstring.h"

FixedString::FixedString() : size_(0) {
	data_[0] = '\0';
}

FixedString::FixedString(const std::string& str) {
	size_ = str.size();

	if (size_ > MaxSize) {
		size_ = MaxSize;
	}

	std::copy(str.begin(), str.begin() + size_, data_);
	data_[size_] = '\0';
}

FixedString::FixedString(const char* str) {
	size_ = 0;

	while (str[size_] != '\0' && size_ < MaxSize) {
		data_[size_] = str[size_];
		++size_;
    }

    data_[size_] = '\0';  // Terminate the string with a null character. 
}

void FixedString::push_back(const char& value) {
	if (size_ < MaxSize) {
		data_[size_++] = value;
		data_[size_] = '\0';
	}
}

void FixedString::pop_back() {
	if (size_ > 0) {
		--size_;
		data_[size_] = '\0';
	}
}

std::size_t FixedString::size() const {
	return size_;
}

char& FixedString::operator[](std::size_t index) {
	return data_[index];
}

const char& FixedString::operator[](std::size_t index) const {
	return data_[index];
}

FixedString& FixedString::operator=(const char* str) {
	size_ = 0;
	std::size_t len = std::strlen(str);
	for (std::size_t i = 0; i < len && i < MaxSize; ++i) {
		data_[i] = str[i];
		++size_;
	}
	data_[size_] = '\0';
	return *this;
}

void FixedString::operator=(const std::string& str) {
	if (str.size() > MaxSize) {
		throw std::length_error("String exceeds maximum size of FixedString");
	}

	size_ = str.size();
	std::copy(str.begin(), str.end(), data_);
	data_[size_] = '\0'; // Ensure null-terminated string
}

bool FixedString::operator==(const FixedString& other) const {
	if (size_ != other.size_) {
		return false;
	}
	for (std::size_t i = 0; i < size_; ++i) {
		if (data_[i] != other.data_[i]) {
			return false;
		}
	}
	return true;
}

FixedString& FixedString::operator+(const FixedString& other) {
	if (size_ + other.size_ > MaxSize) {
		throw std::length_error("FixedString length exceeded");
	}

	for (std::size_t i = 0; i < other.size_; ++i) {
		data_[size_ + i] = other.data_[i];
	}

	size_ += other.size_;

	return *this;
}

std::vector<FixedString> FixedString::split(const char& delimiter) {
	std::vector<FixedString> result;
	FixedString current;

	for (std::size_t i = 0; i < size_; ++i) {
		if (data_[i] == delimiter) {
			result.push_back(current);
			current = FixedString();
		} else {
			current.push_back(data_[i]);
		}
    }

    if (current.size() > 0) {  // Add the last element if it exists 
        result.push_back(current); 
    }

    return result;  // Return the vector of FixedStrings 
}

const char* FixedString::c_str() const {
	return data_;
}

std::ostream& FixedString::operator<<(std::ostream& os) {
	os << c_str();
	return os;
}

std::istream& FixedString::operator>>(std::istream& is) {
	char buffer[FixedString::MaxSize + 1];
	is >> buffer;
	*this = buffer;
	return is;
}
