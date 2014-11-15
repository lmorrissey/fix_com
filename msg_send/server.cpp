#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "fix_msg.h"
#include <type_traits>



int main(int argc, char **argv)
{
    uint16_t port = 7777;
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    FixHeader header;
    NewOrderSingle neworder;
    OrderCancelRequest ordercancel;
    ExecReport execReport();
    AckOrder ackOrder;
    Checksum chksum;

    std::strncpy(chksum.csum, "023", sizeof(chksum.csum));

    std::cout << std::boolalpha;
    std::cout << std::is_pod<ExecReport>::value << '\n';


    if (argc > 1)
    {
        std::cout << "Expecting port; use this format: <port>"<< std::endl;
        port = atoi(argv[2]);
    }
    else
    {
        std::cout << "Using port: " << port << std::endl;
    }

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        std::cerr << "Failed socket creation" << std::endl;
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    //Bind
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        std::cerr << "Failed to bind" << std::endl;
        return 1;
    }

    //Listen for the client connection
    listen(socket_desc, 1);

    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *) &client,(socklen_t*) &c);
    if (client_sock < 0)
    {
        std::cerr << "Failed to accept incoming client connection" << std::endl;
        return 1;
    }

    //Read until the connection is closed
    while (1)
    {
        if ((read_size = recv(client_sock, &header, sizeof(FixHeader), 0))> 0)
        {
//            uint16_t chksum = header.length.body_length;
            switch(header.message.msg)
            {
                case 'D':
                    recv(client_sock, &neworder, sizeof(NewOrderSingle), 0);
                    //set up ack for new order
                case 'F':
                    recv(client_sock, &ordercancel, sizeof(OrderCancelRequest), 0);
                    //set up ack for cancel order


            }
            if (chksum.csum != 0)
            {
                std::cerr<<"checksum "<<chksum.csum<<std::endl;
                memset(&neworder, sizeof(SendOrderMsg), 0);
            }
        }

        std::cerr<<"Got EOM"<<std::endl;
        if (send(client_sock, &ackOrder, sizeof(AckOrder), 0) <0)
            std::cerr<<"Could not send ack"<<std::endl;

    }
    if (read_size == 0)
        std::cout << "Client has disconnected" << std::endl;
    else if (read_size == -1)
    {
        std::cerr << "recv failed" << std::endl;
    }
//    PrintFixHeader(neworder.header);

    return 0;
}



void CreateExecReport()
{





}
