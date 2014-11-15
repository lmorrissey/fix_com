#ifndef FIX_SPEC_H_
#define FIX_SPEC_H_
#include <iostream>
#include <string.h>
#include <cstring>

/*Note:
    Due to gcc bug 43453, char arrays can not
    be initialized in a struct's  initializer list.
    The struct member will be populated using memcpy instead.
    For structs containing a char array, the tag number is used as
    a dummy parameter so we can properly initialize the remaining members.
    The fix for gcc bug 43453 is in gcc version 4.10.
    but 4.10 has not been adopted by Linux.
*/



/////////////////////////
//      TAG 8
/////////////////////////
#pragma pack(push, 1)
struct FixVersion
{
    FixVersion() noexcept = default;
    FixVersion(std::uint16_t tag) : equals('='), tag8(tag), soh(001)  {};
    char equals;
    std::uint16_t tag8;
    char begin_fix_version[8];
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 9
/////////////////////////
#pragma pack(push, 1)
struct FixLength
{
    FixLength() noexcept = default;
    FixLength( uint16_t blength) : equals('='), tag9(9), body_length(blength), soh(001)  {};
    char equals;
    std::uint16_t tag9;
    std::uint16_t body_length; // get this from checksum
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 35
/////////////////////////
#pragma pack(push, 1)
struct MsgType
{
    MsgType() noexcept = default;
    MsgType(char msg) : equals('='), tag35(35), msg(msg), soh(001)  {};
    char equals;
    std::uint16_t tag35;
    char msg;
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 52
/////////////////////////
#pragma pack(push, 1)
struct SendTime
{
    SendTime() noexcept = default;
    SendTime(std::uint16_t tag) : equals('='), tag52(tag), soh(001)  {};
    char equals;
    std::uint16_t tag52;
    char time[22]; // UTCTimestamp =YYYYMMDD-HH:MM:SS.sss
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 56
/////////////////////////
#pragma pack(push, 1)
struct TargetCompId
{
    TargetCompId() noexcept = default;
    TargetCompId(std::uint16_t tag) : equals('='), tag56(tag), soh(001)  {};
    char equals;
    std::uint16_t tag56;
    char compid[21];
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 49
/////////////////////////
#pragma pack(push, 1)
struct SenderCompId
{
    SenderCompId() noexcept = default;
    SenderCompId(std::uint16_t tag) : equals('='), tag49(tag), soh(001)  {};
    char equals;
    std::uint16_t tag49;
    char senderid[8];
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 11
/////////////////////////
#pragma pack(push, 1)
struct ClOrderId
{
    ClOrderId() noexcept = default;
    ClOrderId(std::uint16_t tag) : equals('='), tag11(tag), soh(001)  {};
    char equals;
    std::uint16_t tag11;
    char orderid[32];
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 55
/////////////////////////
#pragma pack(push, 1)
struct Symbol
{
    Symbol() noexcept = default;
    Symbol(std::uint16_t tag) : equals('='), tag55(tag), soh(001)  {};
    char equals;
    std::uint16_t tag55;
    char symbol[10];
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 54
/////////////////////////
#pragma pack(push, 1)
struct Side
{
    Side() noexcept = default;
    Side(char s) : equals('='), tag54(54), side(s),soh(001)  {};
    char equals;
    std::uint16_t tag54;
    char side;
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 60
/////////////////////////
#pragma pack(push, 1)
struct TransactTime
{
    TransactTime() noexcept = default;
    TransactTime(std::uint16_t tag) : equals('='), tag60(tag), soh(001)  {};
    char equals;
    std::uint16_t tag60;
    char transact_time[22];
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 38
/////////////////////////
#pragma pack(push, 1)
struct OrderQty
{
    OrderQty() noexcept = default;
    OrderQty(float oqty) : equals('='), tag38(38), orderqty(oqty),soh(001)  {};
    char equals;
    std::uint16_t tag38;
    float orderqty;
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 40
/////////////////////////
#pragma pack(push, 1)
struct OrderType
{
    OrderType() noexcept = default;
    OrderType(std::uint16_t tag) : equals('='), tag40(tag), soh(001) {};
    char equals;
    std::uint16_t tag40;
    char ordtype[1];
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 37
/////////////////////////
#pragma pack(push, 1)
struct ExchangeOrderId
{
    ExchangeOrderId() noexcept = default;
    ExchangeOrderId(std::uint16_t tag) : equals('='), tag37(tag), soh(001) {};
    char equals;
    std::uint16_t tag37;
    char orderid[32];
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 17
/////////////////////////
#pragma pack(push, 1)
struct ExecId
{
    ExecId() noexcept = default;
    ExecId(uint32_t execid ) : equals('='), tag17(17), exec_id(execid), soh(001) {};
    char equals;
    std::uint16_t tag17;
    uint32_t exec_id;
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 150
/////////////////////////
#pragma pack(push, 1)
struct ExecType
{
    ExecType() noexcept = default;
    ExecType(char etype) : equals('='), tag150(150), exec_type(etype), soh(001) {};
    char equals;
    std::uint16_t tag150;
    char exec_type;
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 39
/////////////////////////
#pragma pack(push, 1)
struct OrderStatus
{
    OrderStatus() noexcept = default;
    OrderStatus(char ordstatus) : equals('='), tag39(39), ord_status(ordstatus),soh(001) {};
    char equals;
    std::uint16_t tag39;
    char ord_status;
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 151
/////////////////////////
#pragma pack(push, 1)
struct LeavesQty
{
    LeavesQty() noexcept = default;
    LeavesQty(float lqty) : equals('='), tag151(151), leavesqty(lqty), soh(001) {};
    char equals;
    std::uint16_t tag151;
    float leavesqty;
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 14
/////////////////////////
#pragma pack(push, 1)
struct CumQty
{
    CumQty() noexcept = default;
    CumQty(float cqty) : equals('='), tag14(14), cumqty(cqty),soh(001) {};
    char equals;
    std::uint16_t tag14;
    float cumqty;
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 10
/////////////////////////
#pragma pack(push, 1)
struct Checksum
{
    Checksum() noexcept = default;
    Checksum(std::uint16_t tag) : equals('='), tag10(tag), soh(001) {};
    char equals;
    std::uint16_t tag10;
    char csum[4];
    uint8_t soh;
};

#pragma pack(pop)

#endif /* FIX_SPEC_H_ */
