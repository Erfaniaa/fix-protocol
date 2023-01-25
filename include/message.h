#include "constants.h"
#include "fixedstring.h"
#include "lookuptable.h"
#include "field.h"

class Message {
public:
	Message();
	Message(FixedString str);
	FixedString message_type() const;
	void add_field(const Field &field);
	FixedString serialize() const;
	bool has_tag(unsigned short tag);
	FixedString get_tag_value(unsigned short tag);
	FixedString get_checksum();

private:
	FixedString message_type_;
	LookupTable fields_lookup_table_;
	FixedVector<Field> fields_fixed_vector_;
};
