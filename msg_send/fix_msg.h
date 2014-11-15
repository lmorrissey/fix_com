#ifndef FIX_MSG_H_
#define FIX_MSG_H_

#include "fix_tag.h"
#include <iostream>
#include <cstdint>

//////////////////////////////////
//          HEADER
/////////////////////////////////
#pragma pack(push, 1)
struct FixHeader
{
    FixHeader() noexcept = default;
    FixHeader(FixVersion v, FixLength l, MsgType m,SendTime t, TargetCompId tgt, SenderCompId sndr)
             : version(v), length(l), message(m), time(t), target(tgt), sender(sndr) {};
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
    NewOrderSingle(ClOrderId oid, Symbol sym,
    Side s, TransactTime t, OrderQty oqty, OrderType otype )
    : orderId(oid), symbolId(sym), side(s),
      time(t), ordqty(oqty), ordtype(otype){};
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
    OrderCancelRequest(ClOrderId oid, Symbol sym,
            Side s, TransactTime t, OrderQty oqty )
            : orderId(oid), symbolId(sym), side(s),
              time(t), ordqty(oqty) {};
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
    ExecReport(ExchangeOrderId oId,
            ExecId eid, ExecType etype,
            OrderStatus ostatus,
            Symbol sym, Side s,
            LeavesQty lqty,
            CumQty cqty)
            : orderId(oId),
              execId(eid),
              execType(etype),
              ordStatus(ostatus),
              symbolId(sym),
              side(s),
              leaveqty(lqty),
              cumqty(cqty) {};
    ExchangeOrderId orderId;
    ExecId execId;
    ExecType execType;
    OrderStatus ordStatus;
    Symbol symbolId;
    Side side;
    LeavesQty leaveqty;
    CumQty cumqty;
};
#pragma pack(pop)
/////////////////////////////////////////////
//              MESSAGES
////////////////////////////////////////////
#pragma pack(push, 1)
struct SendOrderMsg
{
    SendOrderMsg() noexcept = default;
    SendOrderMsg(FixHeader h,NewOrderSingle n,
    Checksum e) : header(h), neworder(n), eom(e) {}
    FixHeader header;
    NewOrderSingle neworder;
    Checksum eom;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct CancelOrderMsg
{
    CancelOrderMsg() noexcept = default;
    CancelOrderMsg(FixHeader h, OrderCancelRequest c,
        Checksum e) : header(h), cancel(c), eom(e) {}
    FixHeader header;
    OrderCancelRequest cancel;
    Checksum eom;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct AckOrder
{
    AckOrder() noexcept = default;
    AckOrder(FixHeader h, ExecReport r, Checksum e)
    : header(h), report(r), eom(e) {}
    FixHeader header;
    ExecReport report;
    Checksum eom;
};
#pragma pack(pop)

const char EQUALS = '=';
const uint8_t SOH = 001;

//namespace OrderMsgs
//{
////Initialize messages for client send
//    SendOrderMsg new_order = {
//        { { EQUALS, 8, "FIX.5.2", SOH },             //fix version
//        { EQUALS, 9, 6, SOH },                       //fix length
//        { EQUALS, 35, 'D', 1 },                    //order type
//        { EQUALS, 52, "YYYYMMDD-HH:MM:SS.sss", SOH },//send time
//        { EQUALS, 56,"TARGET", SOH },                //target company
//        { EQUALS, 49, "BANZAI", SOH } },             //sender
//        { { EQUALS, 11, "23487097", SOH },           //order id
//        { EQUALS, 55, "YOKU", SOH },                 //symbol
//        { EQUALS, 54, '1', SOH },                    //side
//        { EQUALS, 60, "YYYYMMDD-HH:MM:SS.sss", SOH },//transact time
//        { EQUALS, 38, 30, SOH },                     //quantity
//        { EQUALS, 40, '1', SOH } },                  //order type
//        {EQUALS, 10, "ABC", SOH}};                   //checksum
//
//
//    CancelOrderMsg cancel_ord = {
//         { { EQUALS, 8, "FIX.5.2", SOH },             //fix version
//         { EQUALS, 9, 6, SOH },                       //fix length
//         { EQUALS, 35, 'D', 1 },                    //order type
//         { EQUALS, 52, "YYYYMMDD-HH:MM:SS.sss", SOH },//send time
//         { EQUALS, 56,"TARGET", SOH },                //target company
//         { EQUALS, 49, "BANZAI", SOH } },             //sender       end header
//         { { EQUALS, 11, "23487097", SOH },           //order id
//         { EQUALS, 55, "YOKU", SOH },                 //symbol
//         { EQUALS, 54, '1', SOH },                    //side
//         { EQUALS, 60, "YYYYMMDD-HH:MM:SS.sss", SOH },//transact time
//         { EQUALS, 38, 30, SOH }},                     //quantity
//         {EQUALS, 10, "ABC", SOH}};                   //checksum
//}
//namespace OrderAck
//{
//    AckOrder ackorder = {
//        { { EQUALS, 8, "FIX.5.2", 1 },               //fix version
//          { EQUALS, 9, 6, 1 },                       //fix length
//          { EQUALS, 35, 'D', 1 },                    //order type
//          { EQUALS, 52, "YYYYMMDD-HH:MM:SS.sss", 1 },//send time
//          { EQUALS, 56,"TARGET", 1 },                //target company
//          { EQUALS, 49, "BANZAI", 1 } },             //sender
//          { { EQUALS, 37, "23487097", 1},            //exchange order id
//          { EQUALS, 17, 0, 1},                       //exec id, 0 for 150
//          { EQUALS, 150, '0', 1},                    //0=new, 4=cancelled, 6=pending cancel
//          { EQUALS, 39, '0', 1},                     //0=new, 4=cancelled, 6=pending cancel
//          { EQUALS, 55, "YOKU", 1},                  //symbol id
//          { EQUALS, 54, '1', 1 },                    //side
//          { EQUALS, 151, '1', 1 },                   //leaves qty
//          { EQUALS, 14, '1', 1 } },                  // cumulative qty
//          { EQUALS, 10, "ABC", 1} };                   //checksum}
//
//}
//  DEBUG

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

void PrintServerAck(AckOrder ack)
{
    std::cout << "exec id" <<ack.report.execId.exec_id << std::endl;
    std::cout << "exec type" <<ack.report.execType.exec_type << std::endl;
    std::cout << "OrderSTatus" <<ack.report.ordStatus.ord_status <<std::endl;

}




//void PrintNewOrder(SendOrderMsg sendOrder)
//{
//    std::cout << "fix header tag" << rcv_header.version.tag8 << std::endl;
//    std::cout << "fix version" << rcv_header.version.begin_fix_version
//    << std::endl;
//    std::cout << "fix length tag" << rcv_header.length.tag9 << std::endl;
//    std::cout << "fix length" << rcv_header.length.body_length << std::endl;
//    std::cout << "msg type tag" << rcv_header.message.tag35 << std::endl;
//    std::cout << "msg type msg" << rcv_header.message.msg << std::endl;
//    std::cout << "send time" << rcv_header.time.tag52 << std::endl;
//    std::cout << "send time" << rcv_header.time.time << std::endl;
//    std::cout << "target comp" << rcv_header.target.tag56 << std::endl;
//    std::cout << "target comp" << rcv_header.target.compid << std::endl;
//    std::cout << "sender comp id" << rcv_header.sender.tag49 << std::endl;
//    std::cout << "sender comp id" << rcv_header.sender.senderid << std::endl;
//}

//void PrintCancelOrderMsg(CancelOrderMsg cancelMsg)
//{
//
//}

#endif /* FIX_MSG_H_ */
