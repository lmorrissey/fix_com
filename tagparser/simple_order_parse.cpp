
#include <cstdint>
#include <iostream>
#include <stdio.h>      /* printf */
#include <cstring>

int main()
{
	char neworder[] =
			"8=FIX.5.0\0019=103\00135=D\00134=3\00149=BANZAI\00152=20121105-23:24:42\00156=EXEC\00111=1352157882577\00138=10000\00140=1\00154=1\00155=MSFT\00159=0\00110=062\001";
	char exec_order[] = "\001150=2\001151=0";

	char* next_value = strtok(neworder, "= \001");

	////////////////////////////////////////////////
	///            FIX HEADER
	////////////////////////////////////////////////
	struct alignas (16) FixHeader
	{
		FixHeader() noexcept = default;
		char begin_fix_version[7];
		std::uint16_t body_length;
		std::uint16_t msgseqnum;
		char msg_type;   //messages of D, F, or 8.
	};
	FixHeader header = { };

	////////////////////////////////////////////////
	///            FIX HEADER DETAIL
	////////////////////////////////////////////////
	struct alignas(64) FixHeaderDetail
	{
		FixHeaderDetail() noexcept = default;
		char sendingtime[21]; // UTCTimestamp =YYYYMMDD-HH:MM:SS.sss
		char targetcompid[11];
		char sendercompid[11];
	};
	FixHeaderDetail header_detail = { };

	////////////////////////////////////////////////
	///           NEW/CANCEL ORDER
	////////////////////////////////////////////////
	struct alignas(64) OrderInfo
	{
		OrderInfo() noexcept = default;
		char transact_time[20];
		char symbol[10];
		uint32_t orderid;
		float orderqty;
		char side;
		char ordtype;  //1 = market, 2 = limit
	};
	OrderInfo order = { };

	////////////////////////////////////////////////
	///           EXECUTION REPORT
	////////////////////////////////////////////////

	struct alignas(64) ExecutionReport
	{
		ExecutionReport() noexcept = default;
		char symbol[10];
		uint32_t orderid;  //tag 37
		uint32_t exec_id;//tag 17
		char side;
		char exec_type;// tag 150. 0 = new, 4 = cancelled.
		char ord_status;// tag 39. 0 = new, 4 = cancelled.
		//Not using cumulative qty or leaves qty; we're just acking.
	};
	ExecutionReport ack= { };

	////////////////////
	// EOM
	//////////////////
	struct alignas(8) Checksum
	{
		Checksum() noexcept = default;
		char chksum[3];
	};
	Checksum eom= { };


	while (next_value != nullptr)
    {
        //FIX guarantees message will start with tag
        int tag_value = std::stoi(next_value);
        std::cout << "tag value..." << tag_value << std::endl;
        switch (tag_value)
        {
          // group the packet header values together; FIX specifies ordering of these tags
          case 8:
            std::memcpy(&header.begin_fix_version, strtok(nullptr, "= \001"),sizeof(header.begin_fix_version));
            strtok(nullptr, "= \001");
            header.body_length = std::stoi(strtok(nullptr, "= \001"));
            strtok(nullptr, "= \001");
            std::memcpy(&header.msg_type, strtok(nullptr, "= \001"), sizeof(header.msg_type));
            next_value = strtok(nullptr, "= \001");
            break;
          case 49:
            std::memcpy(&header_detail.sendercompid, strtok(nullptr, "= \001"),sizeof(header_detail.sendercompid));
            next_value = strtok(nullptr, "= \001");
            break;
          case 56:
            std::memcpy(&header_detail.targetcompid, strtok(nullptr, "= \001"),sizeof(header_detail.targetcompid));
            next_value = strtok(nullptr, "= \001");
            break;
          case 34:
            header.msgseqnum = std::stoi(strtok(nullptr, "= \001"));
            next_value = strtok(nullptr, "= \001");
            break;
          case 52:
            std::memcpy(&header_detail.sendingtime, strtok(nullptr, "= \001"),sizeof(header_detail.sendingtime));
            next_value = strtok(nullptr, "= \001");
            break;
          default:
          case header.msg_type == 'D' || 'F':
          {
            switch (tag_value)
            {
              case 11:
                order.orderid = std::stol(strtok(nullptr, "= \001"));
                next_value = strtok(nullptr, "= \001");
                break;
              case 55:
                std::memcpy(&order.symbol, strtok(nullptr, "= \001"),sizeof(order.symbol));
                next_value = strtok(nullptr, "= \001");
                break;
              case 54:
                std::memcpy(&order.side, strtok(nullptr, "= \001"), sizeof(order.side));
                next_value = strtok(nullptr, "= \001");
                break;
              case 60:
                std::memcpy(&order.transact_time, strtok(nullptr, "= \001"),sizeof(order.transact_time));
                next_value = strtok(nullptr, "= \001");
                break;
              case 38:
                order.orderqty = std::stoi(strtok(nullptr, "= \001"));
                next_value = strtok(nullptr, "= \001");
                break;
              case 40:
                std::memcpy(&order.ordtype, strtok(nullptr, "= \001"), sizeof(order.ordtype));
                next_value = strtok(nullptr, "= \001");
                break;
            }
          }
          case 10: //end of message, get the Checksum, exit, and ack.
            std::memcpy(&eom.chksum, strtok(nullptr, "= \001"), sizeof(eom.chksum));
            next_value = strtok(nullptr, "= \001");
            break;
        } //end case
      } //end loop
  }
