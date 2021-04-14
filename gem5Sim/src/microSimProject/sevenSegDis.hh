#ifndef __MICROSIMPROJECT_SEVENSEGDIS_HH__
#define __MICROSIMPROJECT_SEVENSEGDIS_HH__

#include "params/SevenSegDis.hh"
#include "sim/sim_object.hh"

class SevenSegDis : public MemObject
{
    private:
    	void processEvent();
      
      	EventWrapper<SevenSegDis, &SevenSegDis::processEvent> event;
      
      	std::string displayChar;
      
	class CPUSidePort : public SlavePort
	{
		private:
			SevenSegDis *owner; //Can call functions on that object
			
		public:
			CPUSidePort(const std::string& name, SevenSegDis *owner):
			    SlavePort(name, owner), owner(owner)
		{ }
		
			//Returns list of non-overlapping address ranges the owner is responsible for
			AddrRangeList getAddrRanges() const override;

		protected:
		   	//Called whenever CPU tries to make an atomic memory access
		   	Tick recvAtomic (PacketPtr pkt) override { panic("recvAtomic unimpl."); }
		   	//Called when CPU makes a functional access
		   	void recvFunctional (PacketPtr pkt) override;
		   	//Called when  the peer to the port calls sendTimingReq
		   	bool recvTimingReq (PacketPrt pkt) override;
		   	//Called when the peer port calls sendRespRetry
		   	void recvRespRetry() override;
			
	};

	class MemSidePort: public MasterPort
	{
		private:
			SevenSegDis *owner;
		
		public:
			MemSidePort(const std:: string& name, SevenSegDis *owner;) :
				MasterPort(name, owner), owner(owner)
				
			{ }
		
		protected:
			//Called when the slave peer to this port calls sendTimingResp
			bool recvTimingResp (PacketPtr pkt) override;
			//Called when peer port calls sendReqRetry
			void recvReqRetry() override;
			//Called whenpeer port wants to notify the object that that address ranges it accepts are changing
			void recvRangeChange() override;

	};      
 
 	//Slave ports
 	CPUSidePort instPort;
 	CPUSidePort dataPort;
 	
 	//Master ports
 	MemSidePort memPort;
  
    public:
    	//SevenSegDis(SevenSegDisParams *p);
      
      	//void startup();
      
      	SimpleMemobj(SimpleMemobjParams *params);

		//called when trying to connect a slave port to the object. will throw an override if the name of the port is wrong
    	BaseMasterPort& getMasterPort(const std::string& if_name,
                                  PortID idx = InvalidPortID) override;
		//called when trying to connect master port to the object. will throw an override if the name of the port is wrong
    	BaseSlavePort& getSlavePort(const std::string& if_name,
                                PortID idx = InvalidPortID) override;
};


#endif //  __MICROSIMPROJECT_SEVENSEGDIS_HH__ 
