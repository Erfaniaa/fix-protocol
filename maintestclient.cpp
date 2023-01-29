#include "../include/fixedstring.h"
#include "../include/messagefactory.h"
#include "../include/clientconnection.h"


int main() {
	ClientConnection client_connection;
	client_connection.open_connection();
	for (int i = 1; i <= 10; i++) {
		client_connection.send_message(MessageFactory().create_logon()->serialize());
	}
	return 0;
}
