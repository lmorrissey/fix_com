#include <iostream>
#include<stdio.h>
#include <string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <cstring>
#include "fix_msg.h"

static uint16_t port = 7777;
int main(int argc, char **argv)
{
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    char server_coughs[] = "Ack Ack Ack";
    NewOrder order;
    FixHeader rcv_header;
    NewOrderSingle neworder;
//    OrderCancelRequest cancelorder;
//    Checksum chksum;
   /* ExecReport ack_cancel =
        { { 075, 37, "23487097", 1 },               //exchange order id
        { 075, 17, 0, 1 },                          //exec id
        { 075, 150, '6', 1 },                        //exec type; 0 = new, 6 = pending cancel, 4 cancelled
        { 075, 39, '4', 1 },                         //identifies current status: order status 0 = new, 4 = cancelled, 6 = pending cancel
        { 075, 55, "YOKU", 1 },                      //symbol
        { 075, 54, '1', 1 } };                //side
*/

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
        if ((read_size = recv(client_sock, &order, sizeof(NewOrder), 0))> 0)
        {
            if (order.eom.chksum != 0)
            {
                std::cerr<<"checksum "<<order.eom.chksum<<std::endl;
                memset(&neworder, sizeof(NewOrder), 0);
            }
        }
        std::cerr<<"Got EOM"<<std::endl;
        write(client_sock, server_coughs, strlen(server_coughs));
        memset(&neworder, sizeof(NewOrder), 0);

    }
    //Based off of message type, populate the struct and ack.
//    write(client_sock, server_coughs, strlen(server_coughs)); //TODO: Send Execution report
    if (read_size == 0)
        std::cout << "Client has disconnected" << std::endl;
    else if (read_size == -1)
    {
        std::cerr << "recv failed" << std::endl;
    }
    PrintFixHeader(rcv_header);

    return 0;
}
