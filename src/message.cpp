#include "../include/message.h"

Message::Message() {}

Message::Message(FixedString str) {
	// Split string into tokens
	FixedVector<FixedString> tokens;
	std::istringstream iss(str.c_str());
	for (std::string token; std::getline(iss, token, constants::SOH[0]); ) {
		tokens.push_back(token);
	}

	// Parse fields from remaining tokens
	for (int i = 0; i < tokens.size(); ++i) {
		Field field(tokens[i]);
		add_field(field);
  	}
}

Message& Message::operator=(FixedString str) {
	// Split string into tokens
	FixedVector<FixedString> tokens;
	std::istringstream iss(str.c_str());
	for (std::string token; std::getline(iss, token, constants::SOH[0]); ) {
		tokens.push_back(token);
	}

	// Parse fields from remaining tokens
	for (int i = 0; i < tokens.size(); ++i) {
		Field field(tokens[i]);
		add_field(field);
	}

	return *this;  // Return reference to this object for chaining. 
}

void Message::add_field(const Field& field) {
	fields_fixed_vector_.push_back(field);
	fields_lookup_table_[field.tag()] = field.value();
}

void Message::add_field(unsigned short tag, FixedString value) {
	add_field(Field(tag, value));
}

FixedString Message::serialize() const {
	FixedString serialized_message;
	for (unsigned short i = 0; i < fields_fixed_vector_.size(); i++) {
		serialized_message = serialized_message + FixedString(std::to_string(fields_fixed_vector_[i].tag())) + FixedString("=") + fields_fixed_vector_[i].value() + constants::SOH;
	}
	return serialized_message;
}

bool Message::has_tag(unsigned short tag) {
	return fields_lookup_table_.has_key(tag);	
}

FixedString Message::get_tag_value(unsigned short tag) {
	return fields_lookup_table_[tag];
}

FixedString Message::get_checksum() {
	FixedString serialized_message;
	unsigned short last_index = serialized_message.size();
	unsigned short sum = 0;
	if (has_tag(10))
		last_index -= 7;
	for (unsigned short i = 0; i < last_index; i++)
		sum = (sum + (unsigned short)serialized_message[i]) % 256;
	if (sum < 10)
		return FixedString("00") + FixedString(sum);
	else if (sum < 100)
		return FixedString("0") + FixedString(sum);
	else
		return FixedString(sum);
}
