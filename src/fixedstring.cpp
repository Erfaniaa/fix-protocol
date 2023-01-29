#include "../include/fixedstring.h"


FixedString::FixedString() : size_(0) {}

FixedString::~FixedString() {}

FixedString::FixedString(const std::string& str) {
	size_ = str.size();

	if (size_ > kMaxSize) {
		size_ = kMaxSize;
	}

	std::copy(str.begin(), str.begin() + size_, data_);
	data_[size_] = '\0';
}

FixedString::FixedString(const char* str) {
	size_ = 0;

	while (str[size_] != '\0' && size_ < kMaxSize) {
		data_[size_] = str[size_];
		++size_;
	}

	data_[size_] = '\0';  // Terminate the string with a null character. 
}

FixedString::FixedString(unsigned short x) {
	std::stringstream ss;
	std::string str;
	ss << x;
	ss >> str;
	
	size_ = str.size();

	if (size_ > kMaxSize) {
		size_ = kMaxSize;
	}

	std::copy(str.begin(), str.begin() + size_, data_);
	data_[size_] = '\0';
}

void FixedString::push_back(const char& value) {
	if (size_ < kMaxSize) {
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
	for (std::size_t i = 0; i < len && i < kMaxSize; ++i) {
		data_[i] = str[i];
		++size_;
	}
	data_[size_] = '\0';
	return *this;
}

void FixedString::operator=(const std::string& str) {
	if (str.size() > kMaxSize) {
		Logger().log_error(const_cast<char*>("String exceeds maximum size of FixedString"));
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

bool FixedString::operator==(const std::string& other) const {
	if (size_ != other.size()) {
		return false;
	}
	for (std::size_t i = 0; i < size_; ++i) {
		if (data_[i] != other[i]) {
			return false;
		}
	}
	return true;
}

FixedVector<FixedString> FixedString::split(const char& delimiter) {
	FixedVector<FixedString> result;
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

boost::array<char, constants::MAX_MESSAGE_LENGTH> FixedString::to_boost_array() const {
	boost::array<char, constants::MAX_MESSAGE_LENGTH> arr;
	std::copy(data_, data_ + size_, arr.begin());
	arr[size_] = '\0';

	return arr;
}

int FixedString::to_int() const {
	// TODO: handle errors if it is not an integer
	return std::atoi(c_str());
}

void FixedString::clear() {
	size_ = 0;
	data_[0] = '\0';
}

FixedString FixedString::get_checksum() {
	unsigned short sum = 0;
	for (unsigned short i = 0; i < size(); i++)
		sum = (sum + (unsigned short)data_[i]) % 256;
	if (sum < 10) {
		FixedString result("00");
		result += FixedString(sum);
		return result;
	}
	else if (sum < 100) {
		FixedString result("0");
		result += FixedString(sum);
		return result;
	}
	else
		return FixedString(sum);
}

FixedString& FixedString::operator+=(const FixedString& other) {
	if (size_ + other.size_ > kMaxSize) {
		Logger().log_error(const_cast<char*>("FixedString length exceeded"));
		throw std::length_error("FixedString length exceeded");
	}

	for (std::size_t i = 0; i < other.size_; ++i) {
		push_back(other.data_[i]);
	}

	return *this;
}


FixedString& FixedString::operator=(const FixedString& other) {
	size_ = other.size_;
	std::copy(other.data_, other.data_ + size_, data_);
	data_[size_] = '\0';

	return *this;
}

FixedString& FixedString::operator=(const unsigned short x) {
	std::stringstream ss;
	std::string str;
	ss << x;
	ss >> str;

	size_ = str.size();

	if (size_ > kMaxSize) {
		size_ = kMaxSize;
	}

	std::copy(str.begin(), str.begin() + size_, data_);
	data_[size_] = '\0';  // Terminate the string with a null character. 

    return *this;  // Return the modified FixedString object 
} 

