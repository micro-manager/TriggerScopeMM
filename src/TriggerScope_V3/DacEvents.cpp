#include "Arduino.h"
#include "DacEvents.h"

DacEvents::DacEvents(int dacNr)
{
   dacNr_ = dacNr;
}

int DacEvents::getDacNr() 
{
   return dacNr_;
}
