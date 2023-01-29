#ifndef MESSAGE_H
#define MESSAGE_H

#include "constants.h"
#include "fixedstring.h"
#include "lookuptable.h"
#include "field.h"


class Message {
public:
	Message();
	Message(const FixedString& str);
	Message& operator=(const FixedString& str);
	void add_field(const Field &field);
	void add_field(unsigned short tag, const FixedString& value);
	FixedString serialize() const;
	bool has_tag(unsigned short tag);
	FixedString get_tag_value(unsigned short tag);
	FixedString get_checksum();

private:
	LookupTable fields_lookup_table_;
	FixedVector<Field> fields_fixed_vector_;
};

#endif
