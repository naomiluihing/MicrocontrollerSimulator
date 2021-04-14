#ifndef __MICROSIMPROJECT_SENSOR_HH__
#define __MICROSIMPROJECT_SENSOR_HH__

#include "params/Sensor.hh"
#include "sim/sim_object.hh"

class Sensor : public SimObject
{
    private:
      void processEvent();
      
      EventWrapper<Sensor, &Sensor::processEvent> event;
      
      int newTemp;
      int curTemp;
      
      
    public:
      Sensor(SensorParams *p);
      
      void startup();
};

#endif //  __MICROSIMPROJECT_SENSOR_HH__ 
