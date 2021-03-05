#include "learning_gem5/hello_object.hh"

#include "debug/Hello.hh"

HelloObject::HelloObject(HelloObjectParams *params):
    SimObject(params), 
    event(*this), 
    myName(params->name), 
    latency(params->time_to_wait), 
    timesLeft(params->number_of_fires)
{
    DPRINTF(Hello, "Created the hello object with the name %s!\n", myName);
}

HelloObject*
HelloObjectParams::create()
{
    return new HelloObject(this);
}

void HelloObject::startup()
{
    schedule(event, latency);
}

void
HelloObject::processEvent()
{
    timesLeft--;
    DPRINTF(Hello, "Hellow world! Processing the Event! %d left\n", timesLeft);
    
    if (timesLeft<=0) {
        DPRINTF(Hello, "Done firing!\n");
    } else {
        schedule(event, curTick() + latency);
    }
}


