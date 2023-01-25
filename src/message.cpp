#include "../include/message.h"

Message::Message(FixedString message_type) : message_type_(message_type) {}

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
