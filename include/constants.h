#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>


namespace constants {
	// FIX version
	const std::string VERSION = "4.4";

	// Message types
	const std::string NEW_ORDER_SINGLE = "D";
	const std::string EXECUTION_REPORT = "8";
	const std::string ORDER_CANCEL_REQUEST = "F";
	const std::string ORDER_CANCEL_REJECT = "9";
	const std::string LOGON = "A";
	const std::string LOGOUT = "5";
	const std::string ORDER_STATUS_REQUEST = "H";
	const std::string MARKET_DATA_REQUEST = "V";
	const std::string MARKET_DATA_SNAPSHOT = "W";
	const std::string NEW_ORDER_ABANDONED = "AO";
	const std::string QUOTE = "S";
	const std::string QUOTE_CANCEL = "Z";
	const std::string MASS_QUOTE = "i";
	const std::string QUOTE_STATUS_REQUEST = "a";
	const std::string HEART_BEAT = "0";
	const std::string TEST_REQUEST = "1";
	const std::string RESEND_REQUEST = "2";
	const std::string REJECT = "3";
	const std::string SEQUENCE_RESET_MSG_TYPE = "4";

	// Field tags
	const unsigned short SENDER_COMP_ID = 49;
	const unsigned short TARGET_COMP_ID = 56;
	const unsigned short SENDER_SUB_ID = 50;
	const unsigned short SENDER_LOC_ID = 142;
	const unsigned short TARGET_SUB_ID = 57;
	const unsigned short TARGET_LOC_ID = 143;
	const unsigned short MSG_TYPE = 35;
	const unsigned short MSG_SEQ_NUM = 34;
	const unsigned short SENDING_TIME = 52;
	const unsigned short USERNAME = 553;
	const unsigned short PASSWORD = 554;
	const unsigned short CLORDID = 11;
	const unsigned short SYMBOL = 55;
	const unsigned short SIDE = 54;
	const unsigned short ORDER_QTY = 38;
	const unsigned short ORDER_TYPE = 40;
	const unsigned short PRICE = 44;
	const unsigned short ORDER_STATUS = 39;
	const unsigned short EXEC_TYPE = 150;
	const unsigned short EXEC_ID = 17;
	const unsigned short CUM_QTY = 14;
	const unsigned short AVG_PX = 6;
	const unsigned short LEAVES_QTY = 151;
	const unsigned short LAST_QTY = 32;
	const unsigned short LAST_PX = 31;
	const unsigned short TEXT = 58;
	const unsigned short EXEC_TRANS_TYPE = 20;
	const unsigned short HANDL_INST = 21;
	const unsigned short TIME_IN_FORCE = 59;
	const unsigned short ORDER_CAPACITY = 47;
	const unsigned short ORDER_RESTATTRIBS = 376;
	const unsigned short ORDER_ID = 37;
	const unsigned short ORDER_QTY_TYPE_QTY = 854;
	const unsigned short ORDER_QTY_TYPE_UNITS = 855;
	const unsigned short ORDER_QTY_TYPE_CONTRACTS = 856;
	const unsigned short ORDER_QTY_TYPE_ALL_EXECUTED = 857;
	const unsigned short ORDER_QTY_TYPE_PARTIALLY_EXECUTED = 858;
	const unsigned short ORDER_QTY_TYPE_CANCELLED = 859;
	const unsigned short ENCRYPT_METHOD = 98;
	const unsigned short HEART_BT_INT = 108;
	const unsigned short TEST_REQ_ID = 112;
	const unsigned short BEGIN_SEQ_NUM = 7;
	const unsigned short END_SEQ_NUM = 16;
	const unsigned short REF_SEQ_NUM = 45;
	const unsigned short REF_TAG_ID = 371;
	const unsigned short REF_MSG_TYPE = 372;
	const unsigned short SEQUENCE_RESET = 141;
	const unsigned short NEW_SEQ_NUM = 36;
	const unsigned short GAP_FILL_FLAG = 123;
	const unsigned short ORIG_CLORD_ID = 41;
	const unsigned short CHECKSUM = 10;
	const unsigned short POSS_DUP_FLAG = 43;
	const unsigned short BODY_LENGTH = 9;
	const unsigned short SESSION_REJECT_REASON = 373;

	// Values for tags
	const std::string TEST_REQ_ID_VALUE = "123";

	// Sender and receiver tag values
	const std::string SENDER_COMP_ID_VALUE = "1";
	const std::string TARGET_COMP_ID_VALUE = "2";
	const std::string SENDER_SUB_ID_VALUE = "11";
	const std::string TARGET_SUB_ID_VALUE = "22";
	const std::string SENDER_LOC_ID_VALUE = "111";
	const std::string TARGET_LOC_ID_VALUE = "222";

	// Delimiter
	// const std::string SOH = "\x01";
	const std::string SOH = "|";

	// Socket
	const std::string HOST = "127.0.0.1";
	const unsigned short PORT = 5555;

	// Messages length
	const unsigned short MAX_MESSAGE_LENGTH = 256;

	// Tags count
	const unsigned short MAX_TAGS_COUNT = 1024;

	// Logger config
	constexpr bool LOG_GENERAL_MESSAGES = true;
	constexpr bool LOG_INFO = true;
	constexpr bool LOG_WARNINGS = true;
	constexpr bool LOG_ERRORS = true;

	// Use Boost socket library
	constexpr bool USE_BOOST = false;
}

#endif
