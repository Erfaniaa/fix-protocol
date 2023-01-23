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

	// Field tags
	const int SENDER_COMP_ID = 49;
	const int TARGET_COMP_ID = 56;
	const int MSG_TYPE = 35;
	const int MSG_SEQ_NUM = 34;
	const int SENDING_TIME = 52;
	const int USERNAME = 553;
	const int PASSWORD = 554;
	const int CLORDID = 11;
	const int SYMBOL = 55;
	const int SIDE = 54;
	const int ORDER_QTY = 38;
	const int ORDER_TYPE = 40;
	const int PRICE = 44;
	const int ORDER_STATUS = 39;
	const int EXEC_TYPE = 150;
	const int EXEC_ID = 17;
	const int CUM_QTY = 14;
	const int AVG_PX = 6;
	const int LEAVES_QTY = 151;
	const int LAST_QTY = 32;
	const int LAST_PX = 31;
	const int TEXT = 58;
	const int EXEC_TRANS_TYPE = 20;
	const int HANDL_INST = 21;
	const int ORD_TYPE = 40;
	const int TIME_IN_FORCE = 59;
	const int ORDER_CAPACITY = 47;
	const int ORDER_RESTATTRIBS = 376;
	const int ORDER_ID = 37;
	const int ORDER_QTY_TYPE = 854;
	const int ORDER_QTY_TYPE_QTY = 854;
	const int ORDER_QTY_TYPE_UNITS = 855;
	const int ORDER_QTY_TYPE_CONTRACTS = 856;
	const int ORDER_QTY_TYPE_ALL_EXECUTED = 857;
	const int ORDER_QTY_TYPE_PARTIALLY_EXECUTED = 858;
	const int ORDER_QTY_TYPE_CANCELLED = 859;

	// Delimiter
	const char SOH = '\x01';
}

#endif
