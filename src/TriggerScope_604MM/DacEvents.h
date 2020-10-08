/*
 * Simple class to store Output requirements
 * Used to calculate sequence of events after 
 * input trigger is received
 */
#ifndef DacEvents_h
#define DacEvents_h

#include "Arduino.h"

class DacEvents
{
   public:
      DacEvents(int dacNr);
      boolean used_;
      uint32_t blankDelay_;
      uint32_t blankDuration_;
      int getDacNr();

   private:
      int dacNr_;
};

#endif
