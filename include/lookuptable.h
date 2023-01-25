#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H

#include <cstddef>
#include "../include/constants.h"

template <typename Value>
class LookupTable {
public:
	LookupTable(const Value& default_value);
	void insert(unsigned short key, const Value& value);
	Value& operator[](unsigned short key);
	const Value& operator[](unsigned short key) const;
	bool has_key(unsigned short key);
	std::size_t size();

private:
	static constexpr std::size_t kMaxSize = constants::MAX_MESSAGE_LENGTH;  
	std::size_t size_;  
	Value values_[kMaxSize];
	Value default_value_;
};

#endif
