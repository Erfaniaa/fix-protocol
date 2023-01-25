#include "../include/lookuptable.h"


template <typename T>
LookupTable<T>::LookupTable(const T& default_value) : size_(0), default_value_(default_value) {}

template <typename T>
void LookupTable<T>::insert(unsigned short key, const T& value) {
	if (size_ < MaxSize) {
		if (value != default_value_ && values_[key] == default_value_)
			++size_;
		values_[key] = value;
	}
}

template <typename T>
T& LookupTable<T>::operator[](unsigned short key) {
	if (key >= 0 && key < MaxSize) {
		return values_[key]; 
	} else {  // Return default value if key is not found 
		return default_value_; 
	}
}

template <typename T>
const T& LookupTable<T>::operator[](unsigned short key) const { 
	if (key >= 0 && key < MaxSize) { 
		return values_[key]; 
	} else { // Return default value if key is not found 
		return default_value_; 
	}
}

template <typename T>
bool LookupTable<T>::has_key(unsigned short key) {
	return table[key] != default_value_;
}

template <typename T>
std::size_t LookupTable<T>::size() {
	return size_;
}
