#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H

#include <cstddef>
#include "../include/constants.h"

template <typename T>
class LookupTable {
public:
	LookupTable(const T& default_value);
	void insert(unsigned short key, const T& value);
	T& operator[](unsigned short key);
	const T& operator[](unsigned short key) const;
	bool has_key(unsigned short key);
	std::size_t size();

private:
	static constexpr std::size_t kMaxSize = constants::MAX_MESSAGE_LENGTH;  
	std::size_t size_;  
	T values_[kMaxSize];
	T default_value_;
};

#endif
