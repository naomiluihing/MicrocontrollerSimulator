#include "microSimProject/sevenSegDis.hh"
#include "debug/Seven.hh"
#include <stdlib.h>
SevenSegDis::SevenSegDis(SevenSegDisParams *params) : 
    SimObject(params),
    event(*this),
    displayChar(params->toDisplay)
{
    DPRINTF(Seven, "display object created\n");
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
void
SevenSegDis::processEvent()
{
    printf("What do you want to display?\n");
    DPRINTF(Seven, "the input is: %s!\n", displayChar);
    
    if (displayChar.compare("0")==0)
         DPRINTF(Seven,"Displaying 1111110\n");
    if (displayChar.compare("1")==0)sa
         DPRINTF(Seven,"Displaying 0110000\n");
    if (displayChar.compare("2")==0)
         DPRINTF(Seven,"Displaying 1101101\n");
    if (displayChar.compare("3")==0)
         DPRINTF(Seven,"Displaying 1111001\n");
    if (displayChar.compare("4")==0)
         DPRINTF(Seven,"Displaying 0110011\n");
    if (displayChar.compare("A")==0)
         DPRINTF(Seven,"Displaying 1110111\n");
    if (displayChar.compare("b")==0)
         DPRINTF(Seven,"Displaying 0011111\n");
    if (displayChar.compare("C")==0)
         DPRINTF(Seven,"Displaying 1001110\n");
    if (displayChar.compare("d")==0)
         DPRINTF(Seven,"Displaying 0111101\n");
    if (displayChar.compare("E")==0)
         DPRINTF(Seven,"Displaying 1001111\n");
    
   DPRINTF(Seven, "Done displaying!\n"); 
}
