/*
 * fix_msg.h
 *
 *  Created on: Nov 12, 2014
 *      Author: laura
 */

#ifndef FIX_MSG_H_
#define FIX_MSG_H_
#include "fix_tag.h"
#include <iostream>

//////////////////////////////////
//          HEADER
/////////////////////////////////
#pragma pack(push, 1)
struct FixHeader
{
    FixHeader() noexcept = default;
    FixVersion version;
    FixLength length;
    MsgType message;
    SendTime time;
    TargetCompId target;
    SenderCompId sender;
};
#pragma pack(pop)
////////////////////////////////////////////////
///           NEW ORDER
////////////////////////////////////////////////
#pragma pack(push, 1)
struct NewOrderSingle
{
    NewOrderSingle() noexcept = default;
    ClOrderId orderId;
    Symbol symbolId;
    Side side;
    TransactTime time;
    OrderQty ordqty;
    OrderType ordtype;
};
#pragma pack(pop)
////////////////////////////////////////////////
///           CANCEL ORDER
////////////////////////////////////////////////
#pragma pack(push, 1)
struct OrderCancelRequest
{
    OrderCancelRequest() noexcept = default;
    ClOrderId orderId;
    Symbol symbolId;
    Side side;
    TransactTime time;
    OrderQty ordqty;
};
#pragma pack(pop)
///////////////////////////////////////////////
//              EXEC REPORT
//////////////////////////////////////////////
#pragma pack(push, 1)
struct ExecReport
{
    ExecReport() noexcept = default;
    ExchangeOrderId orderId;
    ExecId execId;
    ExecType execType;
    OrderStatus ordStatus;
    Symbol symbolId;
    Side side;
};

struct NewOrder
{
    FixHeader header;
    NewOrderSingle neworder;
    Checksum eom;
};
void PrintFixHeader(FixHeader rcv_header)
{
    std::cout << "fix header tag" << rcv_header.version.tag8 << std::endl;
    std::cout << "fix version" << rcv_header.version.begin_fix_version
    << std::endl;
    std::cout << "fix length tag" << rcv_header.length.tag9 << std::endl;
    std::cout << "fix length" << rcv_header.length.body_length << std::endl;
    std::cout << "msg type tag" << rcv_header.message.tag35 << std::endl;
    std::cout << "msg type msg" << rcv_header.message.msg << std::endl;
    std::cout << "send time" << rcv_header.time.tag52 << std::endl;
    std::cout << "send time" << rcv_header.time.time << std::endl;
    std::cout << "target comp" << rcv_header.target.tag56 << std::endl;
    std::cout << "target comp" << rcv_header.target.compid << std::endl;
    std::cout << "sender comp id" << rcv_header.sender.tag49 << std::endl;
    std::cout << "sender comp id" << rcv_header.sender.senderid << std::endl;
}


#endif /* FIX_MSG_H_ */
