#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <type_traits>

#include "fix_msg.h"

int main(int argc , char **argv)
{
    static uint16_t port = 7777;
    std::string host = "127.0.0.1";

    ExecReportAck serverAck;

//    std::time_t t = std::time(nullptr);
//    std::tm tm = *std::localtime(&t);
//    std::cout<<std::put_time(&tm, "%F-%T")<<std::endl; //tag52, SendTime, time YYYYMMDD-HH:MM:SS.sss

    if (argc > 1)
    {
        std::cout << "Expecting host and port; use this format: <host> <port>"<< std::endl;
        port = std::atoi(argv[2]);
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
    //Populate new order

    NewOrderSingle newOrder(FixLength(30), SendTime("YYYYMMDD-HH:MM:SS.sss"),
                        MsgSeqNum(1987123), TransactTime("YYYYMMDD-HH:MM:SS.sss"),
                        Checksum("123"));

    OrderCancelRequest orderCancel(FixLength(30), SendTime("YYYYMMDD-HH:MM:SS.sss"),
                        MsgSeqNum(1987123), TransactTime("YYYYMMDD-HH:MM:SS.sss"),
                        Checksum("123"));

    while (1)
    {
        //Send new order
        if (send(sock_fd, &newOrder, sizeof(NewOrderSingle), 0) < 0)
        {
            std::cerr << "Could not send new order" << std::endl;
            return 1;
        }
        //Wait for ack
        if (recv(sock_fd, &serverAck, sizeof(ExecReportAck), 0) < 0)
        {
            std::cerr << "No Ack from server" << std::endl;
            break;
        }
        if (serverAck.ordStatus.ord_status == NEW)
        {

          std::cout << "Server acked new order " << std::endl;
          std::cout<<"CLIENT RECEIVES: "<<std::endl;
          PrintServerAck(serverAck);
          if (send(sock_fd, &orderCancel, sizeof(OrderCancelRequest), 0) < 0)
          {
              std::cerr << "Client could not cancel order" << std::endl;
              return 1;
          }
        }
        if (serverAck.ordStatus.ord_status == PENDING_CANCEL)
        {
            std::cout << "Client received pending cancel.. " << std::endl;
            std::cout<<"CLIENT RECEIVES: "<<std::endl;
            PrintServerAck(serverAck);
            memset(&serverAck, sizeof(ExecReportAck), 0);
        }
        if (serverAck.ordStatus.ord_status == CANCELLED)
        {
           std::cout << "Client received cancel.. " << std::endl;
           memset(&serverAck, sizeof(ExecReportAck), 0);
           break;
        }

    }

    close(sock_fd);
    return 0;
}



