#ifndef __MICROSIMPROJECT_SEVENSEGDIS_HH__
#define __MICROSIMPROJECT_SEVENSEGDIS_HH__

#include "params/SevenSegDis.hh"
#include "sim/sim_object.hh"

class SevenSegDis : public SimObject
{
    private:
      int displayChar;
      
    public:
      SevenSegDis(SevenSegDisParams *p);
};

#endif //  __MICROSIMPROJECT_SEVENSEGDIS_HH__ 
