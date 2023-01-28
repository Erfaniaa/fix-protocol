#include "../include/boostclientconnection.h"


void BoostClientConnection::open_connection() {
	boost::asio::io_service io_service;

	// Get a list of endpoints corresponding to the server name. 
	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(host.c_str(), std::to_string(port));
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

	// Try each endpoint until we successfully establish a connection. 
	new_socket = boost::asio::ip::tcp::socket(io_service);

	try {
		boost::asio::connect(new_socket, endpoint_iterator);

	} catch (std::exception& e) {
		logger_.log_error("Connection failed error");
	}
	
	client_fd = new_socket.native_handle();  // get the file descriptor for the socket 
} 

void BoostClientConnection::close_connection() {
     new_socket.close();   // closes the socket connection
}  

void BoostClientConnection::send_message(FixedString message) {   // send a message over the socket connection
 	boost::asio::write(new_socket, boost::asio::buffer(message.to_boost_array()));
}   

FixedString BoostClientConnection::receive_message() {
	// receive a message from the socket connection
	char buffer[constants::MAX_MESSAGE_LENGTH + 1];
	boost::system::error_code error;
	std::size_t length = new_socket.read_some(boost::asio::buffer(buffer), error);
	if (error == boost::asio::error::eof)
		return "";
	else if (error)
		throw boost::system::system_error(error);
	return buffer;
}