#include "microSimProject/sevenSegDis.hh"

#include "debug/Seven.hh"

SevenSegDis::SevenSegDis(SevenSegDisParams *params) : 
    SimObject(params),
    displayChar(params->toDisplay)
{
    switch (displayChar){
        case 1111110:
            DPRINTF(Seven,"Displaying 0\n");
            break;
        case 0110000:
            DPRINTF(Seven,"Displaying 1\n");
            break;
        case 1101101:
            DPRINTF(Seven,"Displaying 2\n");
            break;
        case 1111001:
            DPRINTF(Seven,"Displaying 3\n");
            break;
        case 0110011:
            DPRINTF(Seven,"Displaying 4\n");
            break;
        case 1110111:
            DPRINTF(Seven,"Displaying A\n");
            break;
        case 0011111:
            DPRINTF(Seven,"Displaying b\n");
            break;
        case 1001110:
            DPRINTF(Seven,"Displaying C\n");
            break;
        case 0111101:
            DPRINTF(Seven,"Displaying d\n");
            break;
        case 1001111:
            DPRINTF(Seven,"Displaying E\n");
            break;
        default:
            DPRINTF(Seven, "Nothing to Display.\n");
            break;
    }

}

SevenSegDis*
SevenSegDisParams::create()
{
    return new SevenSegDis(this);
}
