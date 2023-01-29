#ifndef FIELD_H
#define FIELD_H

#include <sstream>
#include <string>
#include "fixedvector.h"
#include "fixedstring.h"
#include "logger.h"


class Field {
public:
	Field();
	Field(unsigned short tag, const FixedString& value);
	Field(const FixedString& str);
	unsigned short tag() const;
	FixedString value() const;

private:
	unsigned short tag_;
	FixedString value_;
};

#endif
