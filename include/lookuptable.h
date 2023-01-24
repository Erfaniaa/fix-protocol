#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H

#include <cstddef>

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
	static constexpr std::size_t MaxSize = 1024;  
	std::size_t size_;  
	Value values_[MaxSize];
	Value default_value_;
};

#endif
