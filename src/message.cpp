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

Message::Message(FixedString str) {
	// Split string into tokens
	FixedVector<FixedString> tokens;
	std::istringstream iss(str.c_str());
	for (std::string token; std::getline(iss, token, constants::SOH[0]); ) {
		tokens.push_back(token);
	}

	// Set message type to first token
	message_type_ = FixedString(tokens[0]);

	// Parse fields from remaining tokens
	for (int i = 1; i < tokens.size(); ++i) {
		Field field(tokens[i]);
		add_field(field);
  	}
}

FixedString Message::message_type() const {
	return message_type_;
}

void Message::add_field(const Field& field) {
	fields_fixed_vector_.push_back(field);
	fields_lookup_table_[field.tag()] = field.value();
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
