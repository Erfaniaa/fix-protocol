#include <cstddef>
#include "../include/constants.h"


template <typename T>
class FixedVector {
public:
    FixedVector();
    void push_back(const T& value);
    void pop_back();
    std::size_t size() const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
	bool operator==(const FixedVector<T>& other) const;
	FixedVector<T>& operator=(const FixedVector<T>& other);
    void clear();

private:
    static constexpr std::size_t kMaxSize = constants::MAX_MESSAGE_LENGTH;
    std::size_t size_;
    T data_[constants::MAX_MESSAGE_LENGTH];
};


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
FixedVector<T>& FixedVector<T>::operator=(const FixedVector<T>& other) { 
	size_ = other.size_; 

	for (std::size_t i = 0; i < size(); ++i) { 
		data_[i] = other.data_[i]; 
	} 

	return *this; 
}

template <typename T> 
void FixedVector<T>::clear() {
	size_ = 0;
}
