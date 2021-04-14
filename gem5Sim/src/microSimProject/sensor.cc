#include "microSimProject/sensor.hh"
#include "debug/Sensor.hh"
#include <stdlib.h>

Sensor::Sensor(SensorParams *params) : 
    SimObject(params),
    event(*this),
    newTemp(params->newTemp),
    curTemp(params->curTemp)
{ 
    DPRINTF(Sensor, "Sensor created\n");    
}
Sensor*
SensorParams::create()
{
   return new Sensor(this);
}
void Sensor::startup()
{
    schedule(event, rand()%600);
}
void
Sensor::processEvent()
{
    DPRINTF(Sensor, "Current temperature is %d\n", curTemp); 
    
    DPRINTF(Sensor, "New temperature detected: %d\n", newTemp);
}
