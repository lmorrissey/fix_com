#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <iomanip>
#include <ctime>

#include "fix_msg.h"

int main(int argc , char **argv)
{
    static uint16_t port = 7777;
    std::string host = "127.0.0.1";
    char server_reply[2000];

//    std::time_t t = std::time(nullptr);
//    std::tm tm = *std::localtime(&t);
//    std::cout<<std::put_time(&tm, "%F-%T")<<std::endl; //tag52, SendTime, time YYYYMMDD-HH:MM:SS.sss

    if (argc > 1)
    {
        std::cout << "Expecting host and port; use this format: <host> <port>"<< std::endl;
        port = atoi(argv[2]);
    } else
    {
        std::cout << "Using host: " << host << " port: " << port << std::endl;
    }
    int sock_fd;
    struct sockaddr_in server;
	/////////////////////////////////////
	//	Initialize msgheader
	/////////////////////////////////////
/*	 FixHeader header = { { 075, 8, "FIX.5.2", 1 },     //fix version
			 { 075, 9, 6, 1 },                          //fix length
			 { 075, 35, 'D', 1 },                       //order type
			 { 075, 52, "YYYYMMDD-HH:MM:SS.sss", 1 },   //send time
			 { 075, 56,"TARGET", 1 },                   //target company
			 { 075, 49, "BANZAI", 1 } };                //sender
*/
/*	 NewOrderSingle neworder =
	         { { 075, 11, "23487097", 1 },              //order id
             { 075, 55, "YOKU", 1 },                    //symbol
             { 075, 54, '1', 1 },                       //side
             { 075, 60, "YYYYMMDD-HH:MM:SS.sss", 1 },   //transact time
             { 075, 38, 30, 1 },                      //quantity
             { 075, 40, '1', 1 } };                //order type  1 = market, 2 limit
*/

/*	OrderCancelRequest cancelorder =
	             { { 075, 11, "23487097", 1 },           //order id
	             { 075, 55, "YOKU", 1 },                 //symbol
	             { 075, 54, '1', 1 },                    //side
	             { 075, 60, "YYYYMMDD-HH:MM:SS.sss", 1 },//transact time
	             { 075, 38, 30.0, 1 } };                   //quantity
*/
	// Checksum eom = {075, 10, "0", 1};

	 NewOrder order = { { { 075, 8, "FIX.5.2", 1 },     //fix version
             { 075, 9, 6, 1 },                          //fix length
             { 075, 35, 'D', 1 },                       //order type
             { 075, 52, "YYYYMMDD-HH:MM:SS.sss", 1 },   //send time
             { 075, 56,"TARGET", 1 },                   //target company
             { 075, 49, "BANZAI", 1 } },  { { 075, 11, "23487097", 1 },              //order id
                     { 075, 55, "YOKU", 1 },                    //symbol
                     { 075, 54, '1', 1 },                       //side
                     { 075, 60, "YYYYMMDD-HH:MM:SS.sss", 1 },   //transact time
                     { 075, 38, 30, 1 },                      //quantity
                     { 075, 40, '1', 1 } }, {075, 10, "ABC", 1}};


    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)
    {
        std::cerr << "Socket creation failed" << std::endl;
    }

    server.sin_addr.s_addr = inet_addr(host.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    //Connect to remote server
    if (connect(sock_fd, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        std::cerr << "Connection to Server failed" << std::endl;
        return 1;
    }

    while (1)
    {
        //Send a header
        if (send(sock_fd, &order, sizeof(order), 0) < 0)
        {
            std::cerr << "Could not send header data" << std::endl;
            return 1;
        }
        std::cerr << "Waiting....." << std::endl;
        //Wait for ack
        if (recv(sock_fd, server_reply, 2000, 0) < 0)
        {
            std::cerr << "No Ack from server" << std::endl;
            break;
        }
        std::cout<<"Server sent "<<server_reply<<std::endl;
        //Send Cancel
        //Wait for ack
    }

    close(sock_fd);
    return 0;
}



