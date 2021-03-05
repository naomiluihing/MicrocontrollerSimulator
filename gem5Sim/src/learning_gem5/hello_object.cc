#include "learning_gem5/hello_object.hh"

#include "debug/Hello.hh"

HelloObject::HelloObject(HelloObjectParams *params):
    SimObject(params), event([this]{processEvent();}, name()), latency(100), timesLeft(10)
{
    DPRINTF(Hello, "Created the hello object!\n");
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


