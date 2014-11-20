#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "fix_msg.h"

int main(int argc, char **argv)
{
    uint16_t port = 7777;
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;

    NewOrderSingle neworder;
    OrderCancelRequest ordercancel;

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
        if ((read_size = recv(client_sock, &neworder, sizeof(NewOrderSingle), 0))> 0)
        {
            ExecReportAck execReport(FixLength(23), SendTime("YYYYMMDD-HH:MM:SS.sss"),
                                    MsgSeqNum(1), ExchangeOrderId("exchangeneworderid"),
                                    ExecType('0'), OrderStatus('0'), Checksum("123"));

            #ifdef DEBUG
            PrintNewOrder(neworder);
            #endif
            send(client_sock, &execReport, sizeof(ExecReportAck), 0);
            memset(&execReport, sizeof(ExecReportAck), 0);
        }

        if ((read_size = recv(client_sock, &ordercancel, sizeof(OrderCancelRequest), 0))> 0)
        {
            ExecReportAck execReport(FixLength(23), SendTime("YYYYMMDD-HH:MM:SS.sss"),
                                    MsgSeqNum(2),ExchangeOrderId("exchangecancelorderid"),
                                    ExecType('4'), OrderStatus('6'), Checksum("123"));
            #ifdef DEBUG
            PrintCancelOrder(ordercancel);
            #endif
            send(client_sock, &execReport, sizeof(ExecReportAck), 0);
            execReport.msgseq.msgseq=3;
            execReport.ordStatus.ord_status='4';
            send(client_sock, &execReport, sizeof(ExecReportAck), 0);
            memset(&execReport, sizeof(ExecReportAck), 0);
        }
    }
    if (read_size == 0)
        std::cout << "Client has disconnected" << std::endl;
    else if (read_size == -1)
    {
        std::cerr << "recv failed" << std::endl;
    }
    return 0;
}
