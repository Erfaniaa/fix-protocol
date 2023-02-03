# FIX Protocol

FIX 4.4 session layer implementation for a single pair of initiator (client) and acceptor (server) over TCP (might be helpful for educational purposes)

## What is FIX?

The **Financial Information eXchange** (**FIX**) protocol is an electronic communications protocol initiated in 1992 for international real-time exchange of information related to securities transactions and markets. With trillions of dollars traded annually on the NASDAQ alone, financial service entities are employing direct market access (DMA) to increase their speed to financial markets. Managing the delivery of trading applications and keeping latency low increasingly requires an understanding of the FIX protocol.

Source: [English Wikipedia](https://en.wikipedia.org/wiki/Financial_Information_eXchange)

## Basic FIX Timeline

<img src="https://aquaq.co.uk/wp-content/uploads/2016/03/FIX-message-timeline1.png">

Source: [AQUAQ Analytics](https://aquaq.co.uk/kdb-fix-adapter/)

## Run

1. Clone this repository.

2. Install Boost library. For example, on Ubuntu you can run this command:

   `sudo apt-get install libboost-all-dev`

3. Compile the source code with `g++` with the following commands:

   1. `g++ -O2 -std=c++2a -o bin/server.out mainserver.cpp src/* -I include -L lib -lboost_system -lboost_thread -pthread -fconcepts`
   2. `g++ -O2 -std=c++2a -o bin/client.out maintestclient.cpp src/* -I include -L lib -lboost_system -lboost_thread -pthread -fconcepts`

4. Run the executable files with the following commands:

   1. `bin/server.out`
   2. `bin/client.out`

## Configuration

- If you are running server and client from two different machines, set the host and port in `include/constants.h`.
- You can change `MAX_MESSAGE_LENGTH` and `MAX_TAGS_COUNT` constants in `include/constants.h` if you want to transmit larger messages.
- If you want to use Boost Asio for the socket programming part (instead of C++ classic sockets), set `USE_BOOST` constant to `true` in `include/constants.h`.

## Notes

- Instead of using STL vector, I implemented `FixedVector` class. It uses C++ classic arrays to handle operations exactly in O(1) (while STL vector handles them in *amortized* O(1)). Also it prevents large amount of memory fragmentations. It is useful when we know that our messages' size is limited.
- Instead of using STL string, I implemented `FixedString` class. It uses C++ classic character arrays to handle operations exactly in O(1) (while STL string handles them in *amortized* O(1)). Also it prevents large amount of memory fragmentations. It is useful when we know that our messages' size is limited.
- Instead of using STL unordered_map, I implemented `LookupTable` class. It uses C++ classic arrays to handle operations exactly in O(1). It doesn't need hashing algorithms and linked-lists, so it's faster.
- According to my research the median/average size of FIX protocol message's length is not greater than 200. So I set `MAX_MESSAGE_LENGTH` constant to 256.
- Both classic sockets and Boost Asio sockets have been implemented in this project. You can switch between them easily.
- I used `-O2` flag for optimization.
- I used `unsigned short` data type to reduce the memory usage for integer numbers.
- I used references and pointers in functions' arguments to reduce the memory and time usage.
- The `Session` class is commented based on [FIX Protocol 4.4 testcases](https://www.fixtrading.org/standards/fix-session-testcases-online/).
- C++ OOP concepts like abstract classes have been used in this project.

## Benchmarking

1. Run command `bin/server.out > server_output.txt`.

2. Run command `time bin/client.out > client_output.txt`.

   This will send 5000 messages to the server (session acceptor), and receives some messages. It waits for 50 milliseconds before sending each message. In this case, we added 50 * 5000 milliseconds (250 seconds) to the run-time.

   I tested this on a Lenovo Thinkpad P14s Gen 3 laptop, and it took 253.35 seconds. I had added 250 seconds manually, therefore our algorithm took 3.35 seconds to run (for sending 5000 messages and receiving their responses).

## To-do

- Handle the 14th scenario of [FIX Protocol 4.4 testcases](https://www.fixtrading.org/standards/fix-session-testcases-online/).
- Separate configuration constants from FIX protocol constants. Don't store everything in a single `include/constants.h` file.
- Use move semantics to improve efficiency.
