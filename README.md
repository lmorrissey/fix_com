fix_com
=======
msg_send folder contains a working TCP/IP stream client/server, blocking.A packed struct representing a fix message is sent from the client to the server. The server receives the message and acks to the client.

tagparser contains a simple function that tokenizes a string representing a fix message. The calls to std::stoi are not efficient. It would be nice to switch off of a multi character array when the literal type functionality is fully implemented in C++14.

Building

tagparser: g++ -std=c++11 main.cpp simple_order_parse.cpp

msg_send: make
