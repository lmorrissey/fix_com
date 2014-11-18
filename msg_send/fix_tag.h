#ifndef FIX_SPEC_H_
#define FIX_SPEC_H_
#include <iostream>
#include <string.h>
#include <cstring>
#include <array>

const char* FIX_VERSION = "FIX.5.2";
const char EQUALS = EQUALS;
const uint8_t SOH = SOH;

//order state
const char NEW = '0';
const char CANCELLED = '4';
const char PENDING_CANCEL = '6';

//side
const char BID = '0';
const char ASK = '1';

//order type
const char MARKET = '1';
const char LIMIT = '2';

//message type
const char NEW_ORDER = 'D';
const char CANCEL_ORDER = 'F';
const char ACK_ORDER = '8';

//0=new, 4=cancelled, 6=pending cancel
/////////////////////////
//      TAG 8
/////////////////////////
#pragma pack(push, 1)
struct FixVersion
{
    FixVersion() noexcept = default;
    FixVersion(const char* fix_version) : equals(EQUALS), tag8(8), soh(SOH)
    { std::memcpy(begin_fix_version.data(), fix_version, 8); };
    char equals;
    std::uint16_t tag8;
    std::array<char, 8> begin_fix_version;  // array does not have a constructor; we're still a pod.
//    char begin_fix_version[8];
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
    FixLength( uint16_t blength) : equals(EQUALS), tag9(9), body_length(blength), soh(SOH)  {};
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
    MsgType(char msg) : equals(EQUALS), tag35(35), msg(msg), soh(SOH)  {};
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
    SendTime(const char* time) : equals(EQUALS), tag52(52), soh(SOH)
    {std::memcpy(sendtime.data(), time, 22);};
    char equals;
    std::uint16_t tag52;
    std::array<char, 22> sendtime; // UTCTimestamp =YYYYMMDD-HH:MM:SS.sss
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
    TargetCompId(const char* id) : equals(EQUALS), tag56(56), soh(SOH)
    { std::memcpy(compid.data(), id, 21); };
    char equals;
    std::uint16_t tag56;
    std::array<char, 21> compid;
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
    SenderCompId(const char* id) : equals(EQUALS), tag49(49), soh(SOH)
    { std::memcpy(senderid.data(), id, 8); };
    char equals;
    std::uint16_t tag49;
    std::array<char, 8> senderid;
    uint8_t soh;
};
#pragma pack(pop)
/////////////////////////
//      TAG 34
/////////////////////////
#pragma pack(push, 1)
struct MsgSeqNum
{
    MsgSeqNum() noexcept = default;
    MsgSeqNum(std::uint32_t seq) : equals(EQUALS), tag34(34), msgseq(seq),soh(SOH)
    {};
    char equals;
    std::uint16_t tag34;
    std::uint32_t msgseq;
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
    ClOrderId(const char* id) : equals(EQUALS), tag11(11), soh(SOH)
    { std::memcpy(orderid.data(), id, 32); };
    char equals;
    std::uint16_t tag11;
    std::array<char, 32> orderid;
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
    Symbol(const char* sym) : equals(EQUALS), tag55(55), soh(SOH)
    { std::memcpy(symbol.data(), sym, 10); };
    char equals;
    std::uint16_t tag55;
    std::array<char, 10> symbol;
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
    Side(char s) : equals(EQUALS), tag54(54), side(s),soh(SOH)  {};
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
    TransactTime(const char* time) : equals(EQUALS), tag60(60), soh(SOH)
    { std::memcpy(transact_time.data(), time, 22); };
    char equals;
    std::uint16_t tag60;
    std::array<char, 22> transact_time;
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
    OrderQty(float oqty) : equals(EQUALS), tag38(38), orderqty(oqty), soh(SOH) {};
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
    OrderType(const char ord) : equals(EQUALS), tag40(40), ordtype(ord), soh(SOH)
    {};
    char equals;
    std::uint16_t tag40;
    char ordtype;
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
    ExchangeOrderId(const char* ordid) : equals(EQUALS), tag37(37), soh(SOH)
    { std::memcpy(orderid.data(), ordid, 32); };
    char equals;
    std::uint16_t tag37;
    std::array<char, 32> orderid;
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
    ExecId(uint32_t execid ) : equals(EQUALS), tag17(17), exec_id(execid), soh(SOH) {};
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
    ExecType(char etype) : equals(EQUALS), tag150(150), exec_type(etype), soh(SOH) {};
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
    OrderStatus(char ordstatus) : equals(EQUALS), tag39(39), ord_status(ordstatus),soh(SOH) {};
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
    LeavesQty(float lqty) : equals(EQUALS), tag151(151), leavesqty(lqty), soh(SOH) {};
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
    CumQty(float cqty) : equals(EQUALS), tag14(14), cumqty(cqty),soh(SOH) {};
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
    Checksum(const char* sum) : equals(EQUALS), tag10(10), soh(SOH)
    { std::memcpy(csum.data(), sum, 4); };
    char equals;
    std::uint16_t tag10;
    std::array<char, 4> csum;
    uint8_t soh;
};

#pragma pack(pop)

#endif /* FIX_SPEC_H_ */
