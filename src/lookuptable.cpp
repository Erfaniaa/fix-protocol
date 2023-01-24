#include "../include/lookuptable.h"

#include <cstddef>

template <typename Value>
LookupTable<Value>::LookupTable(const Value& default_value) : size_(0), default_value_(default_value) {}

template <typename Value>
void LookupTable<Value>::insert(int key, const Value& value) {
	if (size_ < MaxSize) {
		if (value != default_value_ && values_[key] == default_value_)
			++size_;
		values_[key] = value;
	}
}

template <typename Value>
Value& LookupTable<Value>::operator[](int key) {
	if (key >= 0 && key < MaxSize) {
		return values_[key]; 
	} else {  // Return default value if key is not found 
		return default_value_; 
	}
}

template <typename Value>
const Value& LookupTable<Value>::operator[](int key) const { 
	if (key >= 0 && key < MaxSize) { 
		return values_[key]; 
	} else { // Return default value if key is not found 
		return default_value_; 
	}
}

template <typename Value>
bool LookupTable<Value>::has_key(int key) {
	return table[key] != default_value_;
}

template <typename Value>
std::size_t LookupTable<Value>::size() {
	return size_;
}
