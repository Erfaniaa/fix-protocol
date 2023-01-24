#include "../include/field.h"

Field::Field(unsigned short tag, FixedString value) : tag_(tag), value_(value) {}

unsigned short Field::tag() const {
	return tag_;
}

FixedString Field::value() const {
	return value_;
}