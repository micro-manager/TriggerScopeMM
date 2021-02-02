#include "Arduino.h"
#include "OutputEvent.h"


OutputEvent::OutputEvent(int dacNr, uint32_t muSeconds, int newState)
{
   dacNr_ = dacNr;
   muSeconds_ = muSeconds;
   newState_ = newState;
}

int OutputEvent::getDacNr()
{
   return dacNr_;
}

uint32_t OutputEvent::getMuSeconds()
{
   return muSeconds_;
}

int OutputEvent::getNewState() 
{
   return newState_;
}



