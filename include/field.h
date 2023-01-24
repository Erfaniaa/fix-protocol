#ifndef FIELD_H
#define FIELD_H

#include "fixedstring.h"

class Field {
public:
	Field(unsigned short tag, FixedString value);
	unsigned short tag() const;
	FixedString value() const;

private:
	unsigned short tag_;
	FixedString value_;
};

#endif
