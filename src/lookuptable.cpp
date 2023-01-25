#include "../include/lookuptable.h"


LookupTable::LookupTable() : size_(0) {}

void LookupTable::insert(unsigned short key, const FixedString& value) {
	if (size_ < kMaxSize) {
		if (!(value == default_value_) && values_[key] == default_value_)
			++size_;
		values_[key] = value;
	}
}

FixedString& LookupTable::operator[](unsigned short key) {
	if (key >= 0 && key < kMaxSize) {
		return values_[key]; 
	} else {  // Return default value if key is not found 
		return default_value_; 
	}
}

const FixedString& LookupTable::operator[](unsigned short key) const { 
	if (key >= 0 && key < kMaxSize) { 
		return values_[key]; 
	} else { // Return default value if key is not found 
		return default_value_; 
	}
}

bool LookupTable::has_key(unsigned short key) {
	return !(values_[key] == default_value_);
}

std::size_t LookupTable::size() {
	return size_;
}
