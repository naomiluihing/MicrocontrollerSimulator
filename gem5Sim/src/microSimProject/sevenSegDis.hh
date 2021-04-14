#ifndef __MICROSIMPROJECT_SEVENSEGDIS_HH__
#define __MICROSIMPROJECT_SEVENSEGDIS_HH__

#include "mem/port.hh"
#include "params/SevenSegDis.hh"
#include "sim/sim_object.hh"

class SevenSegDis : public SimObject
{
    private:
    	void processEvent();
      
      	EventWrapper<SevenSegDis, &SevenSegDis::processEvent> event;
      	
      	std::string displayChar;
      
	class CPUSidePort : public SlavePort
	{
		private:
			SevenSegDis *owner; //Can call functions on that object
			bool needRetry;
			PacketPtr blockedPacket;
			//std::string displayChar;
			
		public:
			CPUSidePort(const std::string& name, SevenSegDis *owner):
			    SlavePort(name, owner), owner(owner),needRetry(false), blockedPacket(nullptr)
		{ }
		
			void sendPacket(PacketPtr pkt);
			//Returns list of non-overlapping address ranges the owner is responsible for
			AddrRangeList getAddrRanges() const override;
			void trySendRetry();


		protected:
		   	//Called whenever CPU tries to make an atomic memory access
		   	Tick recvAtomic (PacketPtr pkt) override { panic("recvAtomic unimpl."); }
		   	//Called when CPU makes a functional access
		   	void recvFunctional (PacketPtr pkt) override;
		   	//Called when  the peer to the port calls sendTimingReq
		   	bool recvTimingReq (PacketPtr pkt) override;
		   	//Called when the peer port calls sendRespRetry
		   	void recvRespRetry() override;
			
	};

	class MemSidePort: public MasterPort
	{
		private:
			SevenSegDis *owner;
			PacketPtr blockedPacket;
			//std::string displayChar;
		
		public:
			MemSidePort(const std::string& name, SevenSegDis *owner) :
				MasterPort(name, owner), owner(owner), blockedPacket(nullptr)
			{ }
			
			void sendPacket(PacketPtr pkt);
			
		protected:
			//Called when the slave peer to this port calls sendTimingResp
			bool recvTimingResp (PacketPtr pkt) override;
			//Called when peer port calls sendReqRetry
			void recvReqRetry() override;
			//Called whenpeer port wants to notify the object that that address ranges it accepts are changing
			void recvRangeChange() override;

	};     
	
	bool handleRequest(PacketPtr pkt);

    bool handleResponse(PacketPtr pkt);

    void handleFunctional(PacketPtr pkt);

    AddrRangeList getAddrRanges() const;

    void sendRangeChange(); 
	
	/// Instantiation of the CPU-side ports
    CPUSidePort instPort;
    CPUSidePort dataPort;

    /// Instantiation of the memory-side port
    MemSidePort memPort;
    
    bool blocked;
 
    public:
    	SevenSegDis(SevenSegDisParams *p);
     	
     	Port &getPort(const std::string &if_name, PortID idx=InvalidPortID) override;
      	
      	void startup();
};

#endif //  __MICROSIMPROJECT_SEVENSEGDIS_HH__ 
