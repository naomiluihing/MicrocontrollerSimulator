#include "microSimProject/sevenSegDis.hh"
#include "debug/Seven.hh"
#include <stdlib.h>

/*Basic MemObject functions*/
SevenSegDis::SevenSegDis(SevenSegDisParams *params) : 
    SimObject(params),
    event(*this),
    displayChar(params->toDisplay),
    instPort(params->name + ".inst_port", this),
    dataPort(params->name + ".data_port", this),
    memPort(params->name + ".mem_side", this),
    blocked(false)
{
    DPRINTF(Seven, "display object created\n");

}

Port &
SevenSegDis::getPort(const std::string &if_name, PortID idx)
{
    panic_if(idx != InvalidPortID, "This object doesn't support vector ports");

    // This is the name from the Python SimObject declaration (SimpleMemobj.py)
    if (if_name == "mem_side") {
        return memPort;
    } else if (if_name == "inst_port") {
        return instPort;
    } else if (if_name == "data_port") {
        return dataPort;
    } else {
        // pass it along to our super class
        return SimObject::getPort(if_name, idx);
    }
}


/*Master and Slave port functions*/
//Call into the SevenSegDis
AddrRangeList
SevenSegDis::CPUSidePort::getAddrRanges() const
{
	return owner->getAddrRanges();
}

void
SevenSegDis::CPUSidePort::recvFunctional(PacketPtr pkt)
{
	return owner->handleFunctional(pkt);
}

//Pass through requst to the memory side
void
SevenSegDis::handleFunctional(PacketPtr pkt)
{
    memPort.sendFunctional(pkt);
}

AddrRangeList
SevenSegDis::getAddrRanges() const
{
    DPRINTF(Seven, "Sending new ranges\n");//Used to track what is happening for debugging purposes
    return memPort.getAddrRanges();
}

//Forward requests through slave port
void
SevenSegDis::MemSidePort::recvRangeChange()
{
    owner->sendRangeChange();
}

void
SevenSegDis::sendRangeChange()
{
    instPort.sendRangeChange();
    dataPort.sendRangeChange();
}

/*Receiving requests*/
//Stores metadata of the control flow of requests. Will send a retry if request is blocked
bool
SevenSegDis::CPUSidePort::recvTimingReq(PacketPtr pkt)
{
    if (!owner->handleRequest(pkt)) {
        needRetry = true;
        return false;
    } else {
        return true;
    }
}

//Helper function for SevnSegDis implementation
bool
SevenSegDis::handleRequest(PacketPtr pkt)
{
    if (blocked) {
        return false;
    }
   // DPRINTF(Seven, "Got request for addr %#x\n", pkt->getAddr());
    blocked = true;
    memPort.sendPacket(pkt);
    return true;
}

//Handles the flow control in case the peer slave port cannot accept the request.
void
SevenSegDis::MemSidePort::sendPacket(PacketPtr pkt)
{
    panic_if(blockedPacket != nullptr, "Should never try to send if blocked!");
    if (!sendTimingReq(pkt)) {
        blockedPacket = pkt;
    }
}

//Resends packet when it is allowed to
void
SevenSegDis::MemSidePort::recvReqRetry()
{
    assert(blockedPacket != nullptr);

    PacketPtr pkt = blockedPacket;
    blockedPacket = nullptr;

    sendPacket(pkt);
}

/*Receiving responses*/
bool
SevenSegDis::MemSidePort::recvTimingResp(PacketPtr pkt)
{
    return owner->handleResponse(pkt);
}

//Checks to see if packet is an instruction or a data packet & sends it to the appropriate port
bool
SevenSegDis::handleResponse(PacketPtr pkt)
{
    assert(blocked);
    //DPRINTF(Seven, "Got response for addr %#x\n", pkt->getAddr());

    blocked = false;

    // Simply forward to the memory port
    if (pkt->req->isInstFetch()) {
        instPort.sendPacket(pkt);
    } else {
        dataPort.sendPacket(pkt);
    }

    instPort.trySendRetry();
    dataPort.trySendRetry();

    return true;
}

//Send packet but from the CPU end
void
SevenSegDis::CPUSidePort::sendPacket(PacketPtr pkt)
{
    panic_if(blockedPacket != nullptr, "Should never try to send if blocked!");

    if (!sendTimingResp(pkt)) {
        blockedPacket = pkt;
    }
}

void
SevenSegDis::CPUSidePort::recvRespRetry()
{
    assert(blockedPacket != nullptr);

    PacketPtr pkt = blockedPacket;
    blockedPacket = nullptr;

    sendPacket(pkt);
}

//Checks if a rety is needed
void
SevenSegDis::CPUSidePort::trySendRetry()
{
    if (needRetry && blockedPacket == nullptr) {
        needRetry = false;
        DPRINTF(Seven, "Sending retry req for %d\n", id);
        sendRetryReq();
    }
}


SevenSegDis*
SevenSegDisParams::create()
{
   return new SevenSegDis(this);
}

void SevenSegDis::startup()
{
    schedule(event, rand()%600);
}

void SevenSegDis::processEvent()
{
    printf("What do you want to display?\n");
    DPRINTF(Seven, "the input is: %s\n", displayChar);
    
    if (displayChar.compare("0")==0)
         DPRINTF(Seven,"Displaying 1111110\n");
    else if (displayChar.compare("1")==0)
         DPRINTF(Seven,"Displaying 0110000\n");
    else if (displayChar.compare("2")==0)
         DPRINTF(Seven,"Displaying 1101101\n");
    else if (displayChar.compare("3")==0)
         DPRINTF(Seven,"Displaying 1111001\n");
    else if (displayChar.compare("4")==0)
         DPRINTF(Seven,"Displaying 0110011\n");
    else if (displayChar.compare("A")==0)
         DPRINTF(Seven,"Displaying 1110111\n");
    else if (displayChar.compare("b")==0)
         DPRINTF(Seven,"Displaying 0011111\n");
    else if (displayChar.compare("C")==0)
         DPRINTF(Seven,"Displaying 1001110\n");
    else if (displayChar.compare("d")==0)
         DPRINTF(Seven,"Displaying 0111101\n");
    else if (displayChar.compare("E")==0)
         DPRINTF(Seven,"Displaying 1001111\n");
    else 
         DPRINTF(Seven,"Displaying 0000000\n");
   DPRINTF(Seven, "Done displaying!\n"); 
}


