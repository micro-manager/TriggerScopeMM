/*
 * Simple class to store Output requirements
 * Used to calculate sequence of events after 
 * input trigger is received
 */
#ifndef OutputEvent_h
#define OutputEvent_h

class OutputEvent
{
   public:
      OutputEvent(int dacNr, uint32_t muSeconds, int newState);
      int getDacNr();
      uint32_t getMuSeconds();
      int getNewState();

   private:
      int dacNr_;
      uint32_t muSeconds_;
      int newState_;
};


#endif
