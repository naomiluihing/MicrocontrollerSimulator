#ifndef __MICROSIMPROJECT_SEVENSEGDIS_HH__
#define __MICROSIMPROJECT_SEVENSEGDIS_HH__

#include "params/SevenSegDis.hh"
#include "sim/sim_object.hh"

class SevenSegDis : public SimObject
{
    private:
      void processEvent();
      
      EventWrapper<SevenSegDis, &SevenSegDis::processEvent> event;
      
      int displayChar;
      
      
    public:
      SevenSegDis(SevenSegDisParams *p);
      
      void startup();
};

#endif //  __MICROSIMPROJECT_SEVENSEGDIS_HH__ 
