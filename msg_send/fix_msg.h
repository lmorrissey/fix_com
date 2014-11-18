#ifndef FIX_MSG_H_
#define FIX_MSG_H_

#include "fix_tag.h"
#include <iostream>
#include <cstdint>

////////////////////////////////////////////////
///           NEW ORDER
////////////////////////////////////////////////
#pragma pack(push, 1)
struct NewOrderSingle
{
    NewOrderSingle() noexcept = default;
    NewOrderSingle(FixLength l,
                   SendTime stime,
                   MsgSeqNum seq,
                   TransactTime t,
                   Checksum eom )
                  : version("FIX.5.2"),
                    length(l),
                    message(NEW_ORDER),
                    sendtime(stime),
                    target("TARGET"),
                    sender("BANZAI"),
                    msgseq(seq),
                    orderId("123NewOrderId"),
                    symbolId("YOKU"),
                    side(BID),
                    transtime(t),
                    ordqty(30),
                    ordtype(LIMIT),
                    chksum(eom) {};
    FixVersion version;
    FixLength length;
    MsgType message;
    SendTime sendtime;
    TargetCompId target;
    SenderCompId sender;
    MsgSeqNum msgseq;
    ClOrderId orderId;
    Symbol symbolId;
    Side side;
    TransactTime transtime;
    OrderQty ordqty;
    OrderType ordtype;
    Checksum chksum;
};
#pragma pack(pop)
////////////////////////////////////////////////
///           CANCEL ORDER
////////////////////////////////////////////////
#pragma pack(push, 1)
struct OrderCancelRequest
{
    OrderCancelRequest() noexcept = default;
    OrderCancelRequest(FixLength l,
                       SendTime stime,
                       MsgSeqNum seq,
                       TransactTime t,
                       Checksum eom )
                      : version("FIX.5.2"),
                        length(l),
                        message(CANCEL_ORDER),
                        sendtime(stime),
                        target("TARGET"),
                        sender("BANZAI"),
                        msgseq(seq),
                        orderId("123CancelOrderId"),
                        symbolId("YOKU"),
                        side(BID),
                        transtime(t),
                        ordqty(30),
                        chksum(eom){};
        FixVersion version;
        FixLength length;
        MsgType message;
        SendTime sendtime;
        TargetCompId target;
        SenderCompId sender;
        MsgSeqNum msgseq;
        ClOrderId orderId;
        Symbol symbolId;
        Side side;
        TransactTime transtime;
        OrderQty ordqty;
        Checksum chksum;
};
#pragma pack(pop)
///////////////////////////////////////////////
//              EXEC REPORT
//////////////////////////////////////////////
#pragma pack(push, 1)
struct ExecReportAck
{
    ExecReportAck() noexcept = default;
    ExecReportAck(FixLength l,
              SendTime stime,
              MsgSeqNum seq,
              ExchangeOrderId oId,
              ExecType etype,
              OrderStatus ostatus,
              Checksum eom)
            : version("FIX.5.2"),
              length(l),
              message(ACK_ORDER),
              sendtime(stime),
              target("TARGET"),
              sender("BANZAI"),
              msgseq(seq),
              orderId(oId),
              execId(0),
              execType(etype),
              ordStatus(ostatus),
              symbolId("YOKU"),
              side(BID),
              leaveqty(0),
              cumqty(0),
              chksum(eom) {};
    FixVersion version;
    FixLength length;
    MsgType message;
    SendTime sendtime;
    TargetCompId target;
    SenderCompId sender;
    MsgSeqNum msgseq;
    ExchangeOrderId orderId;
    ExecId execId;
    ExecType execType;
    OrderStatus ordStatus; //0=new, 4=cancelled, 6=pending cancel
    Symbol symbolId;
    Side side;
    LeavesQty leaveqty;
    CumQty cumqty;
    Checksum chksum;
};
#pragma pack(pop)

//  DEBUG

template<std::size_t N>
std::string MakeString(std::array<char, N> const& array)
{
    const char* str = reinterpret_cast<const char*>(array.data());
    return std::string( str, str+N );
}

void PrintNewOrder(NewOrderSingle neworder)
{
    std::cout<< "NewOrderSingle Header:" <<std::endl;
    std::cout<< "FixVersion: " << MakeString(neworder.version.begin_fix_version)<<std::endl;
    std::cout<< "\tFixLength: " << neworder.length.body_length <<std::endl;
    std::cout<< "\tMsgType: " << neworder.message.msg <<std::endl;
    std::cout<< "\tSendTime: " << MakeString(neworder.sendtime.sendtime) <<std::endl;
    std::cout<< "\tTargetCompId: " << MakeString(neworder.target.compid) <<std::endl;
    std::cout<< "\tSenderCompId: " << MakeString(neworder.sender.senderid) <<std::endl;
    std::cout<< "\tMsgSeqNum: " << neworder.message.msg <<std::endl;
    std::cout<< "NewOrderSingle message body:" <<std::endl;
    std::cout<< "\tClOrderId: " << MakeString(neworder.orderId.orderid) << std::endl;
    std::cout<< "\tSymbol: " << MakeString(neworder.symbolId.symbol) << std::endl;
    std::cout<< "\tSide: " << neworder.side.side << std::endl;
    std::cout<< "\tTransactTime: " << MakeString(neworder.transtime.transact_time)<< std::endl;
    std::cout<< "\tOrderQty: " << neworder.ordqty.orderqty << std::endl;
    std::cout<< "\tOrderType: " << neworder.ordtype.ordtype << std::endl;
    std::cout<< "Trailer:" <<std::endl;
    std::cout<< "\tChecksum: " <<MakeString(neworder.chksum.csum) << std::endl;
}

void PrintCancelOrder(OrderCancelRequest cancelorder)
{
    std::cout << "Cancel Order Header:" <<std::endl;
    std::cout<< "FixVersion: " << MakeString(cancelorder.version.begin_fix_version)<<std::endl;
    std::cout<< "\tFixLength: " << cancelorder.length.body_length <<std::endl;
    std::cout<< "\tMsgType: " << cancelorder.message.msg <<std::endl;
    std::cout<< "\tSendTime: " << MakeString(cancelorder.sendtime.sendtime) <<std::endl;
    std::cout<< "\tTargetCompId: " << MakeString(cancelorder.target.compid) <<std::endl;
    std::cout<< "\tSenderCompId: " << MakeString(cancelorder.sender.senderid) <<std::endl;
    std::cout<< "\tMsgSeqNum: " << cancelorder.message.msg <<std::endl;
    std::cout << "OrderCancelRequest message body:" <<std::endl;
    std::cout << "\tClOrderId: " << MakeString(cancelorder.orderId.orderid) << std::endl;
    std::cout << "\tSymbol: " << MakeString(cancelorder.symbolId.symbol) << std::endl;
    std::cout << "\tSide: " << cancelorder.side.side << std::endl;
    std::cout << "\tTransactTime: " << MakeString(cancelorder.transtime.transact_time)<< std::endl;
    std::cout << "\tOrderQty: " << cancelorder.ordqty.orderqty << std::endl;
    std::cout << "Trailer:" <<std::endl;
    std::cout << "\tChecksum: " << MakeString(cancelorder.chksum.csum)<< std::endl;
}

void PrintServerAck(ExecReportAck execreport)
{
    std::cout << "Exec Report Header:" <<std::endl;
    std::cout<< "FixVersion: " << MakeString(execreport.version.begin_fix_version)<<std::endl;
    std::cout<< "\tFixLength: " << execreport.length.body_length <<std::endl;
    std::cout<< "\tMsgType: " << execreport.message.msg <<std::endl;
    std::cout<< "\tSendTime: " << MakeString(execreport.sendtime.sendtime) <<std::endl;
    std::cout<< "\tTargetCompId: " << MakeString(execreport.target.compid) <<std::endl;
    std::cout<< "\tSenderCompId: " << MakeString(execreport.sender.senderid) <<std::endl;
    std::cout<< "\tMsgSeqNum: " << execreport.message.msg <<std::endl;
    std::cout << "ExecReport message body:" <<std::endl;
    std::cout << "\tExchangeOrderId: " << MakeString(execreport.orderId.orderid) << std::endl;
    std::cout << "\tExecId: " << execreport.execId.exec_id << std::endl;
    std::cout << "\tExecType: " << execreport.execType.exec_type << std::endl;
    std::cout << "\tOrderStatus: " << execreport.ordStatus.ord_status << std::endl;
    std::cout << "\tSymbol: " <<  MakeString(execreport.symbolId.symbol) << std::endl;
    std::cout << "\tSide: " << execreport.side.side << std::endl;
    std::cout << "\tLeavesQty: " << execreport.leaveqty.leavesqty << std::endl;
    std::cout << "\tCumQty: " << execreport.cumqty.cumqty << std::endl;
    std::cout << "Trailer:" <<std::endl;
    std::cout << "\tChecksum: " <<  MakeString(execreport.chksum.csum) << std::endl;
}


#endif /* FIX_MSG_H_ */
