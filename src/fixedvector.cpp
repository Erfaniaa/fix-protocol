#include "../include/fixedvector.h"

template <typename T>
FixedVector<T>::FixedVector() : size_(0) {}

template <typename T>
void FixedVector<T>::push_back(const T& value) {
	if (size_ < kMaxSize) {
		data_[size_++] = value;
	}
}

template <typename T>
void FixedVector<T>::pop_back() {
	if (size_ > 0) {
		--size_;
	}
}

template <typename T>
std::size_t FixedVector<T>::size() const {
	return size_;
}

template <typename T>
T& FixedVector<T>::operator[](std::size_t index) {
	return data_[index];
}

template <typename T>
const T& FixedVector<T>::operator[](std::size_t index) const {
	return data_[index];
}

template <typename T>
bool FixedVector<T>::operator==(const FixedVector<T>& other) const {
	if (size() != other.size()) {
		return false;
	}

	for (std::size_t i = 0; i < size(); ++i) {
		if ((*this)[i] != other[i]) {
			return false;
		}
	}

	return true;
}

template <typename T> 
FixedVector<T>& FixedVector<T>::operator=(const FixedVector<T>& other) const { 
	size_ = other.size_; 

	for (std::size_t i = 0; i < size(); ++i) { 
		data_[i] = other.data_[i]; 
	} 

	return this; 
}

template <typename T> 
void FixedVector<T>::clear() {
	size_ = 0;
}
