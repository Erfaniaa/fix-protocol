#include "../include/field.h"


Field::Field(unsigned short tag, FixedString value) : tag_(tag), value_(value) {}

Field::Field(FixedString str) {
	// Parse the string to set tag and value
	std::stringstream ss(str.c_str());
	std::string item;
	FixedVector<FixedString> tokens;

	while (getline(ss, item, '=')) {
		tokens.push_back(item);
	}

	if (tokens.size() == 2) {
		tag_ = std::stoi(tokens[0].c_str());
		value_ = tokens[1];
	} else {
		// Throw an exception if the string is not in the correct format
		Logger().log_error("Invalid field format"); 
		throw std::invalid_argument("Invalid field format"); 
	} 
}

unsigned short Field::tag() const {
	return tag_;
}

FixedString Field::value() const {
	return value_;
}
