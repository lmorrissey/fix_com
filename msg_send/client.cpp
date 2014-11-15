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
#include <type_traits>

#include "fix_msg.h"

int main(int argc , char **argv)
{
    static uint16_t port = 7777;
    std::string host = "127.0.0.1";
//    char server_reply[2000];
    //send to server
    FixHeader header_send;
    NewOrderSingle new_order;
    OrderCancelRequest ordercancel;
    Checksum chksum_send;


    //receivefrom server
    FixHeader header_receive;
    AckOrder serverAck;
    Checksum chksum_receive;

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
        //Send the header
        if (send(sock_fd, &header_send, sizeof(header_send), 0) < 0)
        {
            std::cerr << "Could not send new order" << std::endl;
            return 1;
        }
       //Send new order
        if (send(sock_fd, &new_order, sizeof(new_order), 0) < 0)
        {
            std::cerr << "Could not send new order" << std::endl;
            return 1;
        }
        // Send the checksum
        if (send(sock_fd, &chksum_send, sizeof(chksum_send), 0) < 0)
        {
            std::cerr << "Could not send new order" << std::endl;
            return 1;
        }
        //Wait for ack
        if (recv(sock_fd, &serverAck, sizeof(AckOrder), 0) < 0)
        {
            std::cerr << "No Ack from server" << std::endl;
            break;
        }
        std::cout << "Server response" << std::endl;
        PrintServerAck(serverAck);
        //Send Cancel
        //Wait for ack
    }

    close(sock_fd);
    return 0;
}



