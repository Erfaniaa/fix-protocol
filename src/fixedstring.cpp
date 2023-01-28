#include "../include/fixedstring.h"


FixedString::FixedString() : size_(0) {}

FixedString::~FixedString() {
	if (data_ != NULL)
		delete data_;
}

FixedString::FixedString(const std::string& str) {
	new_data_if_null();

	size_ = str.size();

	if (size_ > kMaxSize) {
		size_ = kMaxSize;
	}

	std::copy(str.begin(), str.begin() + size_, data_);
	data_[size_] = '\0';
}

FixedString::FixedString(const char* str) {
	new_data_if_null();

	size_ = 0;

	while (str[size_] != '\0' && size_ < kMaxSize) {
		data_[size_] = str[size_];
		++size_;
	}

	data_[size_] = '\0';  // Terminate the string with a null character. 
}

FixedString::FixedString(unsigned short x) {
	new_data_if_null();

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
	new_data_if_null();

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
	new_data_if_null();

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
	new_data_if_null();

	if (str.size() > kMaxSize) {
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

FixedString FixedString::operator+(const FixedString& other) {
	FixedString new_fixed_string("");

	new_fixed_string = *this;

	if (size_ + other.size_ > kMaxSize) {
		throw std::length_error("FixedString length exceeded");
	}

	for (std::size_t i = 0; i < other.size_; ++i) {
		new_fixed_string.push_back(other.data_[i]);
	}

	return new_fixed_string;
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

boost::array<char, constants::MAX_MESSAGE_LENGTH> FixedString::to_boost_array() const {
	boost::array<char, constants::MAX_MESSAGE_LENGTH> arr;
	std::copy(data_, data_ + size_, arr.begin());
	arr[size_] = '\0';

	return arr;
}

std::ostream& FixedString::operator<<(std::ostream& os) {
	os << c_str();
	return os;
}

std::istream& FixedString::operator>>(std::istream& is) {
	char buffer[kMaxSize + 1];
	is >> buffer;
	*this = buffer;
	return is;
}

void FixedString::clear() {
	size_ = 0;
	data_[0] = '\0';
}

void FixedString::new_data_if_null() {
	if (data_ == NULL) {
		data_ = new char[kMaxSize + 1];
		data_[0] = '\0';
	}
}
