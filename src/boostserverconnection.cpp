#include "../include/boostserverconnection.h"


void BoostServerConnection::open_connection() {
	boost::asio::io_service service;
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
	boost::asio::ip::tcp::acceptor acc(service, ep);
	new_socket = std::make_unique<boost::asio::ip::tcp::socket>(service);
	acc.accept(*new_socket); // accept connection from a client
}

void BoostServerConnection::close_connection() {
	new_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both); // shutdown both send and receive operations
	new_socket->close(); // close socket connection 					  	  	  	  	  	  	  	  	  
}

void BoostServerConnection::send_message(FixedString message) { 
	boost::asio::write(*new_socket, boost::asio::buffer(message.to_boost_array())); // write message to the socket connection
}

FixedString BoostServerConnection::receive_message() {
	// receive a message from the socket connection
	char buffer[constants::MAX_MESSAGE_LENGTH + 1];
	boost::system::error_code error;
	std::size_t length = new_socket->read_some(boost::asio::buffer(buffer), error);
	if (error == boost::asio::error::eof)
		return "";
	else if (error) {
		Logger().log_error(const_cast<char*>(""));
		throw boost::system::system_error(error);
	}
	return buffer;
}

bool BoostServerConnection::is_connected() {
	return new_socket->is_open();
}
