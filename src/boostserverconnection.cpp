#include "../include/boostserverconnection.h"


BoostServerConnection::BoostServerConnection() {}

BoostServerConnection::~BoostServerConnection() {
	if (new_socket != NULL)
		delete new_socket;
}

void BoostServerConnection::open_connection() {
	boost::asio::io_service service;
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
	boost::asio::ip::tcp::acceptor acc(service, ep);
	new_socket = new boost::asio::ip::tcp::socket(service);
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
    char data[constants::MAX_MESSAGE_LENGTH]; // create a buffer to store data received from the client    
    boost::asio::read(*new_socket, boost::asio::buffer(data)); // read data from the socket connection    
    return data; // return the data received from the client
}

bool BoostServerConnection::is_connected() {
	return new_socket->is_open();
}
