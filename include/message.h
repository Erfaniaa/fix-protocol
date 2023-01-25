#include "constants.h"
#include "fixedstring.h"
#include "fixedvector.h"
#include "field.h"

class Message
{
public:
	Message(FixedString str);
	FixedString message_type() const;
	void add_field(const Field &field);
	FixedString serialize() const;

private:
	FixedString message_type_;
	FixedVector<Field> fields_;
};
