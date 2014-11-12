/*
 * fix_spec.h
 *
 *  Created on: Nov 9, 2014
 *      Author: laura
 */

#ifndef FIX_SPEC_H_
#define FIX_SPEC_H_

/////////////////////////
//      TAG 8
/////////////////////////
#pragma pack(push, 1)
struct FixVersion
{
    FixVersion() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag8;
    char begin_fix_version[8];
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 9
/////////////////////////
#pragma pack(push, 1)
struct FixLength
{
    FixLength() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag9;
    std::uint16_t body_length; // get this from checksum
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 35
/////////////////////////
#pragma pack(push, 1)
struct MsgType
{
    MsgType() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag35;
    char msg;
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 52
/////////////////////////
#pragma pack(push, 1)
struct SendTime
{
    SendTime() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag52;
    char time[22]; // UTCTimestamp =YYYYMMDD-HH:MM:SS.sss
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 56
/////////////////////////
#pragma pack(push, 1)
struct TargetCompId
{
    TargetCompId() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag56;
    char compid[21];
    unsigned soh :1;
//      std::uint8_t soh : 001;
};
#pragma pack(pop)
/////////////////////////
//      TAG 49
/////////////////////////
#pragma pack(push, 1)
struct SenderCompId
{
    SenderCompId() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag49;
    char senderid[8];
    unsigned soh :1;
//       std::uint8_t soh : 001;
};
#pragma pack(pop)
/////////////////////////
//      TAG 11
/////////////////////////
#pragma pack(push, 1)
struct ClOrderId
{
    ClOrderId() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag11;
    char orderid[32];
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 55
/////////////////////////
#pragma pack(push, 1)
struct Symbol
{
    Symbol() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag55;
    char symbol[10];
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 54
/////////////////////////
#pragma pack(push, 1)
struct Side
{
    Side() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag54;
    char side;
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 60
/////////////////////////
#pragma pack(push, 1)
struct TransactTime
{
    TransactTime() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag60;
    char transact_time[22];
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 38
/////////////////////////
#pragma pack(push, 1)
struct OrderQty
{
    OrderQty() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag38;
    float orderqty;
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 40
/////////////////////////
#pragma pack(push, 1)
struct OrderType
{
    OrderType() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag40;
    char ordtype[1];
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 37
/////////////////////////
#pragma pack(push, 1)
struct ExchangeOrderId
{
    ExchangeOrderId() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag37;
    char orderid[32];
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 17
/////////////////////////
#pragma pack(push, 1)
struct ExecId
{
    ExecId() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag17;
    uint32_t exec_id;
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 150
/////////////////////////
#pragma pack(push, 1)
struct ExecType
{
    ExecType() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag150;
    char exec_type;
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 39
/////////////////////////
#pragma pack(push, 1)
struct OrderStatus
{
    OrderStatus() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag39;
    char ord_status;
    unsigned soh :1;
};
#pragma pack(pop)
/////////////////////////
//      TAG 10
/////////////////////////
#pragma pack(push, 1)
struct Checksum
{
    Checksum() noexcept = default;
    std::uint8_t e;
    std::uint16_t tag10;
    char chksum[4];
    unsigned soh :1;
};
#pragma pack(pop)

#endif /* FIX_SPEC_H_ */
