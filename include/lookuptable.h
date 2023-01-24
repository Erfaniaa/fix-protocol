#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H

#include <cstddef>

template <typename Value>
class LookupTable {
public:
	LookupTable(const Value& default_value);

	void insert(int key, const Value& value);

	Value& operator[](int key);

	const Value& operator[](int key) const;

	bool has_key(int key);

	std::size_t size();

private:
	static constexpr std::size_t MaxSize = 1024;  
	std::size_t size_;  
	Value values_[MaxSize];
	Value default_value_;
};

#endif
