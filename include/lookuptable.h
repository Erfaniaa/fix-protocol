#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H

#include <cstddef>
#include "constants.h"
#include "fixedstring.h"


class LookupTable {
public:
	LookupTable();
	void insert(unsigned short key, const FixedString& value);
	FixedString& operator[](unsigned short key);
	const FixedString& operator[](unsigned short key) const;
	bool has_key(unsigned short key);
	std::size_t size();

private:
	static constexpr std::size_t kMaxSize = constants::MAX_TAGS_COUNT;
	std::size_t size_;  
	FixedString values_[constants::MAX_TAGS_COUNT];
	FixedString default_value_ = "-1";
};

#endif
