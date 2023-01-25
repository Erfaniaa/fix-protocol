#include "../include/message.h"

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
	fields_.push_back(field);
}

FixedString Message::serialize() const {
	FixedString serialized_message;
	for (unsigned short i = 0; i < fields_.size(); i++) {
		serialized_message = serialized_message + FixedString(std::to_string(fields_[i].tag())) + FixedString("=") + fields_[i].value() + constants::SOH;
	}
	return serialized_message;
}
