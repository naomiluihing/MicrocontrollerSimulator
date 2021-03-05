#include "learning_gem5/hello_object.hh"

#include <iostream>

#include "debug/Hello.hh"

HelloObject::HelloObject(HelloObjectParams *params):
    SimObject(params), event([this]{processEvent();}, name())
{
    DPRINTF(Hello, "Created the hello object!\n");
}

void
HelloObject::processEvent()
{
    DPRINTF(Hello, "Hellow world! Processing the Event!\n");
}

void HelloObject::startup()
{
    schedule(event, 100);
}

HelloObject*
HelloObjectParams::create()
{
    return new HelloObject(this);
}

