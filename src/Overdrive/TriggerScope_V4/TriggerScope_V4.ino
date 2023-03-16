/******************************************
 Trigger Scope v. 604MM for Arduino microscope control by 
 ADVANCED RESEARCH CONSULTING @ 2015
 Regents of the University of California, 2020

 Command set:

 Commands to the device are in ASCI and terminated with "\n".
 Returns can be multiple lines, terminated with "\r\n" (carriage retun / new line).
 Error messages start with "!ERROR_" followed by the command causing the error, semi-colon 
 and error message (example: "!ERROR_RANGE: Command out of range, DAC=1-16, Range = 1-5...")

 "*"  - prints ID (example: "ARC TRIGGERSCOPE 16 R3C v.604-MM"
 "?"  - pirnts message listing available commands and their parameters
 ----------------------analog output functions-------------------------
 "SAO"  - sets the voltage of specified DAC. Expected format: "DAC1-4236"  
          where 1 is the line nr, and 4236 the new value to be send to the DAC.
          Resulting voltage depends on bit range of the DAC, and the voltage range 
          Returns: "!DAC1,4236" or error message (not starting with !DAC) on failure.
 "PAN"   - Queries the number of analog output states that can be pre-programmed.
          Format: "PANn".           
          Where n=1-16 (DAC1-16).  
          Returns: "!PANn,q" where q is the maximum number of states that can be programmed
 "PAO" - Sends sequence of analog output states to be used in triggered sequences.
          Format: "PAOn-s-o1-o2-on", where  
          - n=1-16 for DAC 1-16         
          - s: position in the sequence to start inserting values. First position is 0.
          - o1, o2, etc... values (0-65535) to be consecutively  inserted in the list.
          Returns: "!PA0n-s-q" where q is the number of values successfully  inserted in the internal buffer.
 "POV"  - Sets an array of overvoltage values for use before typical state transition. 
          Format: "POVn-s-o1-o2-on", where  
          - n=1-16 for DAC 1-16         
          - s: position in the sequence to start inserting values. First position is 0.
          - o1, o2, etc... values (0-65535) to be consecutively  inserted in the list.
          Returns: "!PA0n-s-q" where q is the number of values successfully  inserted in the internal buffer.

 "POD"  - Sets an array of overvoltage delay times for use with POV commands. 
          Format: "POVn-s-o1-o2-on", where  
          - n=1-16 for DAC 1-16         
          - s: position in the sequence to start inserting values. First position is 0.
          - o1, o2, etc... values (0-4294967295) to be consecutively  inserted in the list.
          Returns: "!PA0n-s-q" where q is the number of values successfully  inserted in the internal buffer.

 "PAC"  - Clears the sequence of ananlog states
          Format: "PACn", where n is the DAC pinNr (1-16)
 "PAS"  - Starts triggered transitions in analog output state as pre-loaded in PAO
          Format: "PASn-s-t" where
          - n=1-16 for DAC 1-16
          = s=0 or 1 where 0 stops and 1 starts triggered transitions 
          - t=0 or 1 and determines whether transition will happen on the falling (0) or rising (1) edge 
            of a pulse on the input pin 
"BAO"  - Activates blanking mode of the analog output.  Output state will be coupled to the 
         state of the input trigger.  If input trigger is active, the DAC will be active (
         as set with SDA), if input trigger is inactive, the output will go (which may not be 0V, depending on the range).
         Format: "BAOn-s-t" 
          - n=1-16 for DAC 1-16
          - s=0 or 1 where 0 stops and 1 starts balnking mode 
          - t translates state of the input pin to its activity for blanking.  If t = 0, 
              DAC  will be 0 when input trigger pin is low. t = 1: DAC will be active when input trigger is low.
 "SAR" - Sets the output range in volts of the DAC.  Example: "SAR2-1" where 2
           specified the DAC number, and 1 the range.  Allowed ranges are number 1-5:
           1:  0-5V
           2:  0-10V
           3:  -5-+5V
           4:  -10-+10V
           5:  -2-+2V  
           Returns: "!RANGE2,1"
-------------------------digital output functions------------------------
"SDO"    - sets TTL outputs of pins1-8 and 9-16 in a single operation
          Format: DOn-o   
          Where n=0 or 1.  0 address pins 1-8, 1 goes to pins 9-16
          0 is digital output bitmask, 0: all off, 1: pin 1 on, 2: pin 2 on, 3: pins 1&2 on, etc..  
          Example: DO1,4  sets pin 3 high and pins 1,2, 4-8 low
          Returns: "!DOn-o" or error message ("!ERROR_DO: ") on failure.
"PDN"   - Queries the number of digital output states that can be pre-programmed.
          Format: "PDNn".           
          Where n=0 or 1.  0 address pins 1-8, 1 goes to pins 9-16
          Returns: "!PDNn-q" where q is the maximum number of states that can be programmed
"PDO"  - Sends sequence of digital output states to be used in triggered sequences.
          Format: "PDOn-s-o1-o2-on", where  
          - n=0 or 1 and directs the command to either pins1-8 or 9-16,         
          - s: position in the sequence to start inserting values. First position is 0.
          - o1, o2, etc... values to be consecutively  inserted in the list.
          Returns: "!PD0n-s-q" where q is the number of values successfully  inserted in the internal buffer.
"PDC"  - Clears the sequence of digital states
          Format: "PDCn", where n is the pingroup, 0=pins1-8, 1=pins9-16
"PDS"  - Starts triggered transitions in digital output state as pre-loaded in PDO
          Format: "PDSn-s-t" where
          - n=0 or 1 and directs the command to either pins 1-8 or 9-16
          = s=0 or 1 where 0 stops and 1 starts triggered transitions 
          - t=0 or 1 and determines whether transition will happen on the falling (0) or rising (1) edge 
            of a pulse on the input pin 
"BDO"  - Activates blanking mode of the digital output.  Output state will be coupled to the 
         state of the input trigger.  If input trigger is active, the pingroup will be active (
         as set with DO), if input trigger is inactive, the pingroup will go low.
         Format: "BDOn-s-t" 
         where n is the pingroup (0 or 1) and s switched blanking mode on (1) or off (0). 
         t translates state of the input pin to its activity for blanking.  If t = 0, 
         output pins will be low when input trigger pin is low.  When t = 1, output pins 
         will be active when input trigger is low.       
 "SSL" - Set Signal LEDs.
         In some cases, setting signal LEDs slows down triggered operation, so offer the option to 
         not set them.
         Format: "SSLn" where
         - n - 0 ("Off") or 1 ("On")
         Signal LEDs are On by default 
 


*****************************
Contact Advanced Research Consulting for Driver libraries! www.advancedresearch.consulting
 ******************************/
#include <SD.h> 
#include <SPI.h>
#include <Wire.h>
#include "Linduino.h"
#include "Adafruit_MCP23017.h"

#define focus 15     //sets focus line #
#define pwrLed 11    //POWER indication
#define dacLed 12    //POWER indication
#define ttlLed 13    //POWER indication
#define trigLed 14   //POWER indication
#define readyLed 15  //POWER indication
#define ttlblock2OE 10
#define ttlblock2DIR 8
#define ttlblock1OE 9
#define ttlblock1DIR 7

#define NR_DACS 16
#define NR_DAC_STATES 1200
#define NR_DO_STATES 1200


String idname = "ARC TRIGGERSCOPE 16 R3C Board 4 v.613-MM";

const char* helpString = "Available commands: \r\n"
  "SAOn-s - sets DACs. n = DAC number (1-16), s = value (0-65535)\r\n"
  "PANn - queries the number of programmable analogoutput states, n = DAC pin number (1-16)\r\n"
  "PAOn-s-o1-o2-on - sends sequence of programmable analog output states, n = DAC pin number (1-16)\r\n"
  "                  s = 0-based index in the sequence to start inserting, \r\n"
  "                  o = comma separated series of output values (0-65535)\r\n"
  "POVn-s-o1-o2-on - sends sequence of analog overdrive states, n = DAC pin number (1-16)\r\n"
  "                  s = 0-based index in the sequence to start inserting, \r\n"
  "                  o = comma separated series of output values (0-65535)\r\n"
  "PODn-s-o1-o2-on - sends sequence of overdrive durations in microseconds, n = DAC pin number (1-16)\r\n"
  "                  s = 0-based index in the sequence to start inserting, \r\n"
  "                  o = comma separated series of delay times (0-(0-4294967295))\r\n"
  
  "PACn - clears the sequence of analog states, n = DAC pin number (1-16)\r\n"
  "PASn-s-t - starts triggered transition in programmable analog output states as programmed in PAO\r\n"
  "           n = DAC pin number (1-16), s = 0 (stops) or 1 (starts), \r\n"
  "           t = transition on falling (0) or rising (1) edge of input trigger.\r\n" 
  "BAOn-s-t starts blanking mode of ananlog output.  n = DAC pin number (1-16), \r\n"
  "           s = 0 (stops) or 1 (starts), t = output low when trigger low (0), or inverse (1)\r\n"

  
  "SARn-s - sets DAC voltages range. n = DAC number (1-16), s= 1:0-5V 2:0-10V 3:-5-+5V 4: -10-+10V 5:-2-+2V\r\n"
  "SDOn-s - sets digital output state, n = 0(pins1-8) or 1(pins9-16), s binary mask 0-255\r\n" 
  "PDNn - queries the number of programmable digital output states, n = pin group 0(1-8) or 1 (9-16)\r\n"
  "PDOm-s-o1-o2-on - sends sequence of programmable digital output states, n = pin group 0(1-8) or 1(9-16)\r\n"
  "                  s = 0-based index in the sequence to start inserting\r\n"
  "                  o = comma separated series of output states (0-255)\r\n"   
  "PDCn - clears the sequence of digital states, n = pin group 0(1-8) or 1 (9-16)\r\n"
  "PDSn-s-t - starts triggered transitions in digital output state as pre-loaded in PDO, \r\n"
  "           n = pin group 0(1-8) or 1 (9-16), s = 0 stops 1 starts, \r\n"
  "           t = transition on falling (0) or rising (1) edge of input trigger.\r\n"
  "BDn-s-t - sync digital output with input trigger. n = pin group 0(1-8) or 1 (9-16)\r\n"
  "          s = 0 stops 1 starts, t = output low when trigger low (0), or inverse (1)\r\n"
  "SSLn - switches use of signal LEDs.  n=0 (Off) or n=1 (On)\r\n"
  "\r\n"; // empty line to signal end of help textd


const char sep = '-';

//new IC assignments and SD card access for V4 board
Adafruit_MCP23017 mcp; //create mux object
File myFile; //create settings file
const int chipSelect = BUILTIN_SDCARD; //set SD card access CS line

//set up menu modes and vars
byte opMode = 1;            //sets operation mode, 1=MANUAL control, 2 = PC CONTROL, 3=TTL Slave via Programmed Steps
boolean trigArmed=false;    //enables while loop for just the high speed trig sequencing
unsigned long debugT=0;     //debugger flag - not used in a few versions
unsigned long trigInterval; //tracks frequency of inputs from camera or external source
int trigStep=0;             //optionally used to sequence more than 1 PROG line at a time, not fully implemented
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

//PIN ASSIGNMENTS
const byte DAC[NR_DACS] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; //MOVE THESE FOR CUSTOMERS IF NEEDED!
const byte ttl[NR_DACS] = {5,6,7,8,14,15,16,17,20,0,1,2,3,4,5,6}; //ttl pin #'s
const byte trig[4] = {0,1,2,3};

/*HIGH SPEED PROGRAMMING MODE MEMORY BLOCK*/
int    dacArray[NR_DAC_STATES][NR_DACS] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; // DACprogram list
uint8_t ttlArray[NR_DO_STATES][2] = {{0,0}}; // digital output states program list
int ttlArrayMaxIndex[2] = {0, 0}; // maintains the max index in the array that was set
int ttlArrayIndex[2] = {0, 0}; // keeps track of current position in the array
int dacArrayMaxIndex[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int dacArrayIndex[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int dacOverdriveIndex[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t dacBlankDelay[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t dacBlankDuration[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t dacBlankExpire[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
boolean useSignalLEDs_ = true;

// data structures to be assembled from blanking settings above that have a time-ordered sequence of events
int dacBlankEventsNr = 0;
// there can be a delay and a duration for each blanking event
uint32_t dacBlankEventNextWait[2 * NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t dacBlankEventPinNr[2 * NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// 0 : off, 1: set normal state, 2: set value from dacArray
uint8_t dacBlankEventState[2 * NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

byte pinGroupState[2] = {0, 0};
byte pinGroupStoredState[2] = {0, 0};
bool pinGroupBlanking[2] = {false, false};
bool pinGroupBlankOnLow[2] = {true, true};
bool pinGroupSequencing[2] = {false, false};
byte pinGroupSequenceMode[2] = {0, 0}; // 0: falling edge, 1: rising edge
int dacState[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int dacStoredState[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool dacBlanking[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
bool dacBlankOnLow[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
bool dacSequencing[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
byte dacSequenceMode[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int      povArray[NR_DAC_STATES][NR_DACS] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; // DAC overdrive value list
uint32_t podArray[NR_DAC_STATES][NR_DACS] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; // overdrive delay on state
uint32_t podExpire[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //timers for real overdrive expire
int      lastDac[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //holes the last DAC value and used for implement on timer expire

bool triggerPinState = false;

int    delArray[500]; //time delay array for high speed sequences
int    focArray[6]; //array for focus stacks = start, step, #loops,direction,slave,current step
uint16_t ttlState = 0;
// boolean ttlActive[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int timeCycles = 1; //used for high speed switching inside of a loop
int runCycles = 0; //holds running position vs total cycles for timelapse

volatile boolean inTrigger=false;
byte program=0; //this sets the active program # used in the Mode 3 high speed sequencer
byte maxProgram=0; //this holds the maximum program value entered, and is used to set the maxium sequence step.
uint32_t maxDel = 0; //used fro maximum delay on state inside sequencing - AB addition
// byte stepMode = 1; //1 = waits for TTL IN, 2=runs continually
// unsigned long timeOut = 1000; //timeout for sequence (set to 10 seconds by default)
// unsigned long tStart = 0; //sequence start timer
// unsigned long trigLedTimer = 0;
// boolean reportTime = 0;
// boolean umArmIgnore = 0; //this handles micromanagers multiple ARM commands which are issued back-to-back on MDA acqtivation. Ignores after a short wait. 
// boolean usepwm = false;
// byte pChannel =0; //number of channels micromanager has attempted to control
// byte lastPT=20;
// byte trigMode = 2; //0 = LOW 1 = HIGH 2 = RISING 3 = FALLING 4 = CHANGE

bool error = false;

const char* saoErrorString = "!ERROR_SAO: Format: SAOn-s n=1-16 (DAC1-16), s=value 0-65535";
const char* sarErrorString = "!ERROR_SAR: Format: SARn-s n=1-16 (DAC=1-16), s=1:0-5V 2:0-10V 3:-5-+5V 4:-10-+10V 5:-2-+2V";
const char* panErrorString = "!ERROR_PAN: Format: PANn  n=1-16 (DAC1-16)";
const char* paoErrorString = "!ERROR_PAO: Format: PAOn-s-01-02-0n n=1-16 (DAC1-16), s= >=0 (position), 0n=values 0-65535";
const char* pacErrorString = "!ERROR_PAC: Format: PACn n=1-16 (DAC1-16)";
const char* baoErrorString = "!ERROR_BAO: Format: BAOn-s-t n=1-16 (DAC1-16), s blank 0(off) or 1(on), t 0 (blank on low) or 1 (blank on high)";
const char* povErrorString = "!ERROR_POV: Format: POVn-s-01-02-0n n=1-16 (DAC1-16), s= >=0 (position), 0n=values 0-65535";
const char* podErrorString = "!ERROR_POD: Format: PODn-s-01-02-0n n=1-16 (DAC1-16), s= >=0 (position), 0n=values 0-4294967295";
const char* pasErrorString = "!ERROR_PAS: Format: PASn-s-t n=1-16 (DAC1-16) s 0=stop 1=start, t=transition on falling(0) or rising(1) edge";   
const char* sdoErrorString = "!ERROR_SDO: Format: SDOn-s n=pingroup 0-1, s=value 0-255";
const char* pdnErrorString = "!ERROR_PDN: Format: PDNn n=pingroup 0-1";
const char* pdoErrorString = "!ERROR_PDO: Format: PDOn-s-01-02-0n n=pingroup 0-1, s=position, 0n=values 0-255";
const char* bdoErrorString = "!ERROR_BDO: Format: BDOn-s-t n=pingroup 0-1, s blank 0(off) or 1(on), t 0 (blank on low) or 1 (blank on high)";
const char* pdcErrorString = "!ERROR_PDC: Format: PDCn n=pinGroup(1/2)";   
const char* pdsErrorString = "!ERROR_PDS: Format: PDSn-s-t n=pinGroup(1/2) s 0=stop 1=start, t=transition on falling(0) or rising(1) edge";
const char* sslErrorString = "!ERROR_SSL: Format: SSLn n=0 (Off) or 1 (On)";
const char* generalErrorString = "ERROR_UNKNOWN_COMMAND";


void setup() 
{
  mcp.begin(0x27);   //turn on MUX comms
  
  for(int i=0;i<16;++i) {  //configure MCP pins as outputs
    mcp.pinMode(i, OUTPUT);
    mcp.digitalWrite(i,LOW);
  }
  mcp.digitalWrite(pwrLed,HIGH); //indicate setup complete
  
  //configure TTL outputs 5-12
  mcp.digitalWrite(ttlblock2OE,LOW); //low for enable
  mcp.digitalWrite(ttlblock2DIR,HIGH); //high to enable 3.3v -> 5V output
  
  //configure TTL outputs 13-16 & TRIG 1-4
  mcp.digitalWrite(ttlblock1OE,LOW); //low for enable
  mcp.digitalWrite(ttlblock1DIR,LOW); //high to enable 3.3v -> 5V output
  delay(10);
  //configureTrigger(trigMode); //will attach interrupt
  for(byte i=0;i<9;++i) { pinMode(ttl[i],OUTPUT); digitalWrite(ttl[i],LOW); } //SET OUTPUT PINS ON TTL AND CAMERA LINES
  for(byte i=9;i<16;++i) { 
    mcp.pinMode(ttl[i],OUTPUT); 
    delay(5); 
    mcp.digitalWrite(ttl[i],LOW); 
    delay(10);
  } //SET OUTPUT PINS ON TTL AND CAMERA LINES

   Serial.begin(115200); // start serial @ 115,200 baud
  while (!Serial) { ; } // wait for serial port

  //read from SD card
  //Serial.print("Reading Settings...");
  if (!SD.begin(chipSelect)) {
    //Serial.println("SD Read Failure. Contact ARC");
    return;
  }
  myFile = SD.open("tgs.txt", FILE_WRITE);
  if (myFile) {
    //Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    myFile.close();
    Serial.println("done.");
  }
  else {
    // if the file didn't open, print an error:
    //Serial.println("SD Read Failure. Contact ARC");
  }

  /***Dac startup ***/
  pinMode(9,OUTPUT); //CLR pin must stay high!
  digitalWrite(9,LOW); //CLR Stays high ALWAYAS
  delay(50);
  digitalWrite(9,HIGH); //CLR Stays high ALWAYAS
  delay(50);
  
  SPI.begin();
  pinMode(10,OUTPUT); // DAC CS
  SPI.beginTransaction(SPISettings(30000000, MSBFIRST, SPI_MODE0)); //teensy can do 30000000 !! 
  
  //Drive All DACs & TTLs to 0
   for(int i=1;i<=16;++i) {
      setTTL(i,0);
      setDac(i, 0);
    }
  opMode=3; //HYBRID mode default HYBRID=3 / MANUAL=0 /  
  delay(100);
  Serial.println(idname); //issue identifier so software knows we are running 
  // configureTrigger(trigMode); //will attach interrupt
  mcp.digitalWrite(15,HIGH); //indicate setup complete
  triggerPinState = digitalReadFast(trig[0]);
  
}

void loop()
{
  //************************   DEVICE CONTROL & COMMAND CODE          ***********************//
  //************************  SERIAL COMMUNICATION CODE    ******************///
  /*
  if(inTrigger && reportTime) //reports time delay from previous interrupt
  {
    Serial.print("@TIME =");
    Serial.println(trigInterval);
    inTrigger = false;
  }
  */
  for (byte i = 0; i < NR_DACS; i++) // investigates if an overdrive or delay timer is enabled
    {
    if (podExpire[i] != 0) 
    { // delay is still on
       if (podExpire[i] < micros())
       { // time has expired
        setDac(i, lastDac[i]); //issue normal on state value 
        podExpire[i] = 0; //remove exire timer
       }
    }
  }
  if (triggerPinState != digitalReadFast(trig[0]))
  {
    triggerPinState = ! triggerPinState;
    if (useSignalLEDs_)
    {
      digitalWriteDirect(trigLed, triggerPinState);
    }
    for (byte i = 0; i < NR_DACS; i++) // todo: optimize by ordering an array with sequenceable DACS and only cycle through those
    {
      if (dacSequencing[i])
      {
        if (dacSequenceMode[i] == triggerPinState)
        {
          dacState[i] = dacArray[dacArrayIndex[i]][i];
          dacArrayIndex[i]++;
          
          if (dacArrayIndex[i] == dacArrayMaxIndex[i]) { dacArrayIndex[i] = 0; }
          if (!dacBlanking[i])
          {
            if(povArray[dacArrayIndex[i]][i] ) //if pov has an overdrive value
            {  
              setDac(i, povArray[dacArrayIndex[i]][i]); //issue overdrive
              podExpire[i] = micros() + podArray[dacArrayIndex[i]][i]; //set disable timer
              lastDac[i] = dacState[i]; //save the normal dac output value for later update
            }
            else{
              setDac(i, dacState[i]);
            }
          }          
          
        }
      }
      if (dacBlanking[i]) {
        dacBlankOnLow[i] == triggerPinState ? setDac(i, dacState[i]) : setDac(i, 0);
      }
    }
    
    for (byte i = 0; i < 2; i++)
    {
      if (pinGroupSequencing[i]) 
      {
        if (pinGroupSequenceMode[i] == triggerPinState) 
        {
          pinGroupState[i] = ttlArray[ttlArrayIndex[i]][i];
          ttlArrayIndex[i]++;
          if (ttlArrayIndex[i] == ttlArrayMaxIndex[i]) { ttlArrayIndex[i] = 0; }
          if (!pinGroupBlanking[i])
          {
            setPinGroup(i, pinGroupState[i]);
          } // if we are blanking, fall through to the code below to set 
        }
      }
      if (pinGroupBlanking[i])
      {
        pinGroupBlankOnLow[i] == triggerPinState ? setPinGroup(i, pinGroupState[i]) : 
                                                   setPinGroup(i, 0);
      }
    }
    //delayMicroseconds(maxDel); //AB addition
   for (byte i = 0; i < NR_DACS; i++) // todo: optimize by ordering an array with sequenceable DACS and only cycle through those
    {
      if (dacSequencing[i])
      {
        if(dacBlankDuration[i] > 0){ //AB addition
         setDac(i, 0);
        }
      }
    }  
   
  }
      
  if (stringComplete)  // There is a new line terminated string ready to be processed 
  {
    digitalWrite(readyLed,LOW);

    String command = inputString.substring(0,3);

    if (inputString == "?\n")
    {
      Serial.println(helpString);
    }

    else if(inputString == "*\n")
    { 
      Serial.println(idname);
    } //return ID line if queried

    // SAO command - Set DAC
    // Expected format: "SAO1-4236"  where 1 is the line nr, and 4236 the new value to be send to the DAC 
    else if(command == "SAO")
    { 
      error = false;
      byte dacNum = 0; // initialize to error conditino 
      int offset = 5;
      if (inputString[4] == sep) 
      { 
        dacNum = atoi(&inputString[3]); 
      } else if (inputString[5] == sep) 
      { 
        dacNum = atoi(inputString.substring(3,5).c_str());  
        offset++; 
      } else 
      { 
        error = true; 
      }
      if (dacNum < 1 || dacNum > 16) 
      {
        error = true;
      }

      int value = atoi(inputString.substring(offset).c_str());
      if (value < 0 || value > 65535) 
      {
        error = true;
      }
        
      if (!error) //if inputs are valid
      {  
        Serial.print("!SAO"); //print recieve message to operator
        Serial.print(dacNum); //print recieve message to operator
        Serial.print(sep);
        Serial.println(value);
        dacState[dacNum - 1] = value;
        setDacCheckBlanking(dacNum - 1);
      } else 
      {
        Serial.println(saoErrorString);
      }  
    }

    // PAN   - 
    // Queries the number of analog output states that can be pre-programmed.
    //      Format: "PANn", n is 1-6 for DAC1-16.
    //      Returns: "!PANn-q" where q is the maximum number of states that can be programmed
    else if (command == "PAN")
    {
      byte dac = atoi(&inputString[3]);
      if (dac < 1 || dac > 16)
      {
        Serial.println(panErrorString);
      } else 
      {
        Serial.print("!PAN");
        Serial.print(dac);
        Serial.print(sep);
        Serial.println(NR_DAC_STATES);
      }
    }

    /*
     * 
     *"PAO" - Sends sequence of analog output states to be used in triggered sequences.
          Format: "PAOn,s,o1,o2,on", where  
          - n=1-16 for DACS1-16         
          - s: position in the sequence to start inserting values. First position is 0.
          - o1, o2, etc... values (0-65535) to be consecutively  inserted in the list.
          Returns: "!PA0n,s,q" where q is the number of values successfully  inserted in the internal buffer.
    */
    else if (command == "PAO")
    {
      error = false;
      int n = 0;
      int s = 0;
      int dacNr = 0;
      unsigned int scp = 5;
      if (inputString[4] == sep) { dacNr = inputString.substring(3,4).toInt(); }
      else if (inputString[5] == sep){ dacNr = inputString.substring(3,5).toInt(); scp = 6; }
      else { error = true; }
      if (dacNr < 1 || dacNr > 16) { error = true; }
      unsigned int ecp = scp + 1;
      if (!error)
      {
        while (inputString[ecp - 1] != sep && ecp < inputString.length())
        {
          ecp++; 
        }
        if (ecp < inputString.length()) { s = inputString.substring(scp, ecp).toInt(); }
        else  {  error = true; }
        while (!error && ecp < inputString.length())
        {
          scp = ecp;
          ecp++;
          while (inputString[ecp - 1] != sep && ecp < inputString.length())
          {
            ecp++;
          }
          if ( (ecp - scp) > 1)
          {
            int val = inputString.substring(scp, ecp).toInt();
            if (val < 0 || val > 65535)
            {
              error = true;
            } else 
            {
              dacArray[n + s][dacNr-1] = val;
              n++;
              int index = n+s;
              if (index > dacArrayMaxIndex[dacNr-1])
              {
                dacArrayMaxIndex[dacNr-1] = index; 
              }
            }  
          }
        }     
      }
      
      if (!error)
      {
        char out[20];
        sprintf(out, "!PAO%d%c%d%c%d%c%d", dacNr, sep, s, sep, n, sep, dacArrayMaxIndex[dacNr-1]);
        Serial.println(out);
      } else 
      {
        Serial.println(paoErrorString);
      }
    }


     /*
     *  "PAC"  - Clears the sequence of ananlog states
          Format: "PACn", where n is the DAC pinNr (1-16)
     */
    else if (command == "PAC")
    {
      error = false;
      if (inputString.length() == 5 || inputString.length() == 6)
      {
        int dacNr = inputString.substring(3).toInt(); 
        if (dacNr < 1 || dacNr > 16) { error = true; }
        if (!error)
        {
          dacSequencing[dacNr - 1] = false;
          dacArrayIndex[dacNr - 1] = 0;
          dacArrayMaxIndex[dacNr - 1] = 0;
          dacBlankDelay[dacNr - 1] = 0;
          dacBlankDuration[dacNr - 1] = 0;
          clearPAO(dacNr - 1); 
          clearPOD(dacNr - 1);//addition for overdrive
          clearPOV(dacNr - 1);//addition for overdrive
          for ( byte d = 0;d<NR_DACS;d++){
            podExpire[d] = 0; //clear out expiration array
          }
          char out[20];
          sprintf(out, "!PAC%d", dacNr);
          Serial.println(out);
        }
      } else 
      {
        error = true;
      }
      if (error)
      {
        Serial.println(pacErrorString);
      }
    }

    /*
    "PAS"  - Starts and stops triggered transitions in analog output state as pre-loaded in PAO
          Format: "PASn,s,t" where
          - n=1-16 (DAC 1-16)
          = s=0 or 1 where 0 stops and 1 starts triggered transitions 
          - t=0 or 1 and determines whether transition will happen on the falling (0) or rising (1) edge 
            of a pulse on the input pin 
    */
    else if (command == "PAS")
    {
      error = false;
      if (inputString.length() == 9 || inputString.length() == 10)
      {
        error = false;
        int dacNr = 0;
        int scp = 4;
        if (inputString[scp] == sep) { dacNr = inputString.substring(3,scp).toInt(); }
        else if (inputString[scp+1] == sep) 
        {
          scp++; 
          dacNr = inputString.substring(3,scp).toInt(); 
        }
        if (dacNr < 1 || dacNr > 16 || inputString[scp] != sep)
        {
          error = true;
        }
        int state = inputString.substring(scp+1,scp+2).toInt();
        if (state < 0 || state > 1) { error = true; }
        int rising = inputString.substring(scp+3).toInt();
        if (rising < 0 || rising > 1) { error = true; }
        if (!error)
        {
          dacSequencing[dacNr - 1] = (boolean) state;
          dacSequenceMode[dacNr - 1] = rising;
          if (state)
          {
            dacStoredState[dacNr - 1] = dacState[dacNr - 1];
            dacArrayIndex[dacNr - 1] = 0; 
            if (!rising) { // if we trigger on the falling edge, set initial state now, and advance counter here
              setDac(dacNr -1, dacArray[dacArrayIndex[dacNr - 1]][dacNr - 1]); // Check blanking?
              dacArrayIndex[dacNr - 1]++;
            }
          } else
          {
            dacState[dacNr - 1] = dacStoredState[dacNr - 1];
          }
          char out[20];
          sprintf(out, "!PAS%d%c%d%c%d", dacNr, sep, state, sep, rising);
          Serial.println(out);
        }
      } else 
      {
        error = true;
      }
      if (error)
      {
        Serial.println(pasErrorString);
      }
       
    }




    /*
     * 
     *"POV" - Sends sequence of analog overdrive states to be used in triggered sequences.
          Format: "POVn,s,o1,o2,on", where  
          - n=1-16 for DACS1-16         
          - s: position in the sequence to start inserting values. First position is 0.
          - o1, o2, etc... values (0-65535) to be consecutively  inserted in the list.
          Returns: "!POVn,s,q" where q is the number of values successfully  inserted in the internal buffer.
    */
    else if (command == "POV")
    {
      error = false;
      int n = 0;
      int s = 0;
      int dacNr = 0;
      unsigned int scp = 5;
      if (inputString[4] == sep) { dacNr = inputString.substring(3,4).toInt(); }
      else if (inputString[5] == sep){ dacNr = inputString.substring(3,5).toInt(); scp = 6; }
      else { error = true; }
      if (dacNr < 1 || dacNr > 16) { error = true; }
      unsigned int ecp = scp + 1;
      if (!error)
      {
        while (inputString[ecp - 1] != sep && ecp < inputString.length())
        {
          ecp++; 
        }
        if (ecp < inputString.length()) { s = inputString.substring(scp, ecp).toInt(); }
        else  {  error = true; }
        while (!error && ecp < inputString.length())
        {
          scp = ecp;
          ecp++;
          while (inputString[ecp - 1] != sep && ecp < inputString.length())
          {
            ecp++;
          }
          if ( (ecp - scp) > 1)
          {
            int val = inputString.substring(scp, ecp).toInt();
            if (val < 0 || val > 65535)
            {
              error = true;
            } else 
            { 
              povArray[n + s][dacNr-1] = val;
              n++;
              int index = n+s;
              if (index > dacArrayMaxIndex[dacNr-1])
              {
                dacArrayMaxIndex[dacNr-1] = index; 
              }
            }  
          }
        }     
      }
      
      if (!error)
      {
        char out[20];
        sprintf(out, "!POV%d%c%d%c%d%c%d", dacNr, sep, s, sep, n, sep, dacArrayMaxIndex[dacNr-1]);
        Serial.println(out);
      } else 
      {
        Serial.println(povErrorString);
      }
    }

    /*
     * 
     *"POD" - Sends sequence of delay times for anaog overdrive staates specified in POV.
          Format: "PODn,s,o1,o2,on", where  
          - n=1-16 for DACS1-16         
          - s: position in the sequence to start inserting values. First position is 0.
          - o1, o2, etc... values (uInt32_t) to be consecutively  inserted in the list.
          Returns: "!PODn,s,q" where q is the number of values successfully  inserted in the internal buffer.
    */
    else if (command == "POD")
    {
      error = false;
      int n = 0;
      int s = 0;
      int dacNr = 0;
      unsigned int scp = 5;
      if (inputString[4] == sep) { dacNr = inputString.substring(3,4).toInt(); }
      else if (inputString[5] == sep){ dacNr = inputString.substring(3,5).toInt(); scp = 6; }
      else { error = true; }
      if (dacNr < 1 || dacNr > 16) { error = true; }
      unsigned int ecp = scp + 1;
      if (!error)
      {
        while (inputString[ecp - 1] != sep && ecp < inputString.length())
        {
          ecp++; 
        }
        if (ecp < inputString.length()) { s = inputString.substring(scp, ecp).toInt(); }
        else  {  error = true; }
        while (!error && ecp < inputString.length())
        {
          scp = ecp;
          ecp++;
          while (inputString[ecp - 1] != sep && ecp < inputString.length())
          {
            ecp++;
          }
          if ( (ecp - scp) > 1)
          {
            int val = inputString.substring(scp, ecp).toInt();
            if (val < 0 || val > 65535)
            {
              error = true;
            } else 
            {  
              podArray[n + s][dacNr-1] = val;
              n++;
              int index = n+s;
              if (index > dacArrayMaxIndex[dacNr-1])
              {
                dacArrayMaxIndex[dacNr-1] = index; 
              }
            }  
          }
        }     
      }
      
      if (!error)
      {
        char out[20];
        sprintf(out, "!POD%d%c%d%c%d%c%d", dacNr, sep, s, sep, n, sep, dacArrayMaxIndex[dacNr-1]);
        Serial.println(out);
      } else 
      {
        Serial.println(podErrorString);
      }
    }



    /*
    "BAO"  - Activates blanking mode of the analog output.  Output state will be coupled to the 
         state of the input trigger.  If input trigger is active, the DAC will be active (
         as set with SDA), if input trigger is inactive, the output will go (which may not be 0V, depending on the range).
         Format: "BAOn,s,t" 
          - n=1-16 for DACS1-16
          - s=0 or 1 where 0 stops and 1 starts balnking mode 
          - t translates state of the input pin to its activity for blanking.  If t = 0, 
              DAC  will be 0 when input trigger pin is low. t = 1: DAC will be active when input trigger is low. 
    */
    else if (command == "BAO")
    {
      error = false;
      int dacNr = 0;
      int scp = 5;
      if (inputString[4] == sep) { dacNr = inputString.substring(3,4).toInt(); }
      else if (inputString[5] == sep) { dacNr = inputString.substring(3,5).toInt(); scp = 6; }
      else { error = true; }
      if (dacNr < 1 || dacNr > 16){ error = true; }
      int state = inputString.substring(scp, scp+1).toInt();
      if (state < 0 || state > 1) { error = true; }
      if (inputString[scp+1] != sep) { error = true; }
      int mode = inputString.substring(scp+2).toInt();
      if (mode < 0 || mode > 1) { error = true; }
      if (!error)
      {
        dacBlanking[dacNr - 1] = state == 1;
        dacBlankOnLow[dacNr - 1] = mode == 0;
        setDacCheckBlanking(dacNr - 1);
        char out[20];
        sprintf(out, "!BAO%d%c%d%c%d", dacNr, sep, state, sep, mode);
        Serial.println(out);
      } else 
      {
        Serial.println(baoErrorString);
      }
    }

   
    // SDO
    // sets TTL outputs of pins1-8 and 9-16 in a single operation
    // Format: SDOn,o   
    // Where n=0 or 1.  0 address pins 1-8, 1 goes to pins 9-16
    // 0 is digital output bitmask, 0: all off, 1: pin 1 on, 2: pin 2 on, 3: pins 1&2 on, etc..  
    // Example: DO1,4  sets pin 3 high and pins 1,2, 4-8 low
    else if (command == "SDO")
    {
      byte pinGroup = atoi(&inputString[3]);
      if (pinGroup < 0 || pinGroup > 1)
      {
        Serial.println(sdoErrorString);
      } else 
      {
        int value = atoi(inputString.substring(5).c_str());
        if (value < 0 || value > 255) 
        {
          Serial.println(sdoErrorString);
        } else
        {
          Serial.print("!SDO");
          Serial.print(pinGroup);
          Serial.print(sep);
          Serial.println(value);
          pinGroupState[pinGroup] = value;          
          setPinGroupCheckBlanking(pinGroup);
        }
      }
    }

    // PDN   - 
    // Queries the number of digital output states that can be pre-programmed.
    //      Format: "PDNn".
    //      Returns: "!PDNn,q" where q is the maximum number of states that can be programmed
    else if (command == "PDN")
    {
      byte pinGroup = atoi(&inputString[3]);
      if (pinGroup < 0 || pinGroup > 1)
      {
        Serial.println(pdnErrorString);
      } else 
      {
        Serial.print("!PDN");
        Serial.print(pinGroup);
        Serial.print(sep);
        Serial.println(NR_DO_STATES);
      }
    }

    //"PDO"  - Sends sequence of digital output states to be used in triggered sequences.
    //     Format: "PDOn-s-o1-o2-on", where  
    //     - n=1 or 2 and directs the command to eitherpins1-8 or 9-16,         
    //     - s: position in the sequence to start inserting values. First position is 1.
    //     - o1, o2, etc... values to be consecutively  inserted in the list.
    //     Returns: "!PD0n,s,q" where q is the number of values successfully  inserted in the internal buffer.
    else if (command == "PDO")
    {
      error = false;
      int s = 0;
      int n = 0;
      int pinGroup = inputString.substring(3,4).toInt();
      if (pinGroup < 0 || pinGroup > 1)
      {
        error = true;
      }
      if (inputString[4] != sep)
      {
        error = true;
      }
      unsigned int scp = 5;
      unsigned int ecp = 6;
      if (!error)
      {
        while (inputString[ecp - 1] != sep && ecp < inputString.length())
        {
          ecp++; 
        }
        if (ecp < inputString.length())
        {
          s = inputString.substring(scp, ecp).toInt();          
        }
        else 
        {
          error = true;
        }
        while (!error && ecp < inputString.length())
        {
          scp = ecp;
          ecp++;
          while (inputString[ecp - 1] != sep && ecp < inputString.length())
          {
            ecp++;
          }
          if ( (ecp - scp) > 1)
          {
            int val = inputString.substring(scp, ecp).toInt();
            if (val < 0 || val > 255)
            {
              error = true;
            } else 
            {
              ttlArray[n + s][pinGroup] = (byte) val;
              n++;
              int index = n+s;
              if (index > ttlArrayMaxIndex[pinGroup])
              {
                ttlArrayMaxIndex[pinGroup] = index; 
              }
            }  
          }
        }     
      }
      
      if (!error)
      {
        char out[20];
        sprintf(out, "!PDO%d%c%d%c%d%c%d", pinGroup, sep, s, sep, n, sep, ttlArrayMaxIndex[pinGroup]);
        Serial.println(out);
      } else 
      {
        Serial.println(pdoErrorString);
      }
    }

    /*
     * "PDC"  - Clears the sequence of digital states
          Format: "PDCn", where n is the pingroup, 0=pins1-8, 1=pins9-16
     */
    else if (command == "PDC")
    {
      error = false;
      if (inputString.length() == 5)
      {
        int pinGroup = inputString.substring(3,4).toInt(); 
        if (pinGroup < 0 || pinGroup > 1) { error = true; }
        if (!error)
        {
          pinGroupSequencing[pinGroup] = false;
          ttlArrayIndex[pinGroup] = 0;
          ttlArrayMaxIndex[pinGroup] = 0;
          clearPDO(pinGroup);
          char out[20];
          sprintf(out, "!PDC%d", pinGroup);
          Serial.println(out);
        }
      } else 
      {
        error = true;
      }
      if (error)
      {
        Serial.println(pdcErrorString);
      }
    }

    /*
    "PDS"  - Starts and stops triggered transitions in digital output state as pre-loaded in PDO
          Format: "PDSn,s,t" where
          - n=0 or 1 and directs the command to either pins 1-8 or 9-16
          = s=0 or 1 where 0 stops and 1 starts triggered transitions 
          - t=0 or 1 and determines whether transition will happen on the falling (0) or rising (1) edge 
            of a pulse on the input pin 
    */
    else if (command == "PDS")
    {
      error = false;
      if (inputString.length() == 9)
      {
        int pinGroup = inputString.substring(3,4).toInt();
        if (pinGroup < 0 || pinGroup > 1) { error = true; }
        int state = inputString.substring(5,6).toInt();
        if (state < 0 || state > 1) { error = true; }
        int rising = inputString.substring(7,8).toInt();
        if (rising < 0 || rising > 1) { error = true; }
        if (!error)
        {
          pinGroupSequencing[pinGroup] = (boolean) state;
          pinGroupSequenceMode[pinGroup] = rising;
          if (state)
          {
            pinGroupStoredState[pinGroup] = pinGroupState[pinGroup];
            ttlArrayIndex[pinGroup] = 0; 
            if (!rising) 
            { // if we trigger on the falling edge, set initial state now, and advance counter here
              setPinGroup(pinGroup, ttlArray[ttlArrayIndex[pinGroup]][pinGroup]); // Check blanking?
              ttlArrayIndex[pinGroup]++;
            }
          } else
          {
            pinGroupState[pinGroup] = pinGroupStoredState[pinGroup];
          }
          char out[20];
          sprintf(out, "!PDS%d%c%d%c%d", pinGroup, sep, state, sep, rising);
          Serial.println(out);
        }
      } else 
      {
        error = true;
      }
      if (error)
      {
        Serial.println(pdsErrorString);
      }
    }
    
    /** 
     *   "BDO"  - Activates blanking mode of the digital output.  Output state will be coupled to the 
     *    state of the input trigger.  If input trigger is active, the pingroup will be active (
     *    as set with DO), if input trigger is inactive, the pingroup will go low.
     *    Format: "BDOn,s,t" where n is the pingroup (0 or 1), s switches blanking mode on (1)
     *    or off (0), and t sets the mode (0 blank on low, 1 blank on high)
     */
    else if (command == "BDO")
    {
      error = false;
      if (inputString.length() == 9)
      {
        int pinGroup = inputString.substring(3,4).toInt();
        if (pinGroup < 0 || pinGroup > 1) { error = true; }
        byte state = inputString.substring(5,6).toInt();
        if (state < 0 || state > 1) { error = true; }
        byte mode = inputString.substring(7,8).toInt();
        if (mode < 0 || mode > 1) {  error = true; }
        if (!error)
        {
          pinGroupBlanking[pinGroup] = state == 1;
          pinGroupBlankOnLow[pinGroup] = mode == 0;
          setPinGroupCheckBlanking(pinGroup);
          char out[20];
          sprintf(out, "!BDO%d%c%d%c%d", pinGroup, sep, state, sep, mode);
          Serial.println(out);
        }
      } else 
      {
        error = true; 
      }
      if (error)
      {
        Serial.println(bdoErrorString);
      }
    }

    /**
     * Sets voltage range of DACS
     */
    else if(command == "SAR")
    {  
      error = false;                                                      
      byte dacNum = inputString.substring(3).toInt();
      byte pp = 5;
      if(dacNum >9) 
      {
        pp=6;
      }
      byte rangeVal = inputString.substring(pp).toInt();
      if(rangeVal < 1 || rangeVal > 5) 
      {
        error = true;
      } //force to max range
      if(dacNum < 1 || dacNum > 16) 
      {
        error = true;
      } //confirm if input channel range is valid
      if(!error) //if range is OK perform command
      {
        Serial.print("!SAR"); //print recieve message to operator
        Serial.print(dacNum);
        Serial.print(sep);
        Serial.println(rangeVal);
        setDacRange(dacNum-1,rangeVal-1);
        // 0 the output
        int value = 0;
        if (rangeVal > 2) 
        { 
          value = 65535 / 2;
        }
        dacState[dacNum - 1] = value;
        setDac(dacNum - 1, value);  
      } else 
      {
        Serial.println(sarErrorString);
      }  
    }

    // Set Signal LED flag
    else if (command == "SSL") 
    {
      error = false;
      byte result = inputString.substring(3).toInt();;
      if (result == 0)
      {
        useSignalLEDs_ = false;
        digitalWrite(dacLed, 0);
        digitalWrite(ttlLed, 0);
        digitalWriteDirect(trigLed,0);
      }
      else if (result == 1)
      {
        useSignalLEDs_ = true;
        // TODO: make sure the LEDs are set correctly?
      }
      else error = true;
      if (!error) 
      {
        Serial.print("!SSL");
        Serial.println(result);
      } else
      {
        Serial.println(sslErrorString);
      }
    }
      
    //status commands
    else if(inputString == "STAT?\n")                     {debug();         }
    else if(inputString == "TEST?\n")                     {diagTest();      }
    else if(inputString == "CLEAR_ALL\n")                 {clearTable();    }
    else if(inputString.substring(0,9) == "CLEAR_DAC")    {clearDac();      }

    else 
    {
      Serial.println(generalErrorString);
    }
   
 
    clearSerial();
    mcp.digitalWrite(readyLed,HIGH);
  } //EXIT LOOP FOR SERIAL HERE
  

/*********************This block runs the high speed control interface *********************/

/****checks the acquisition order
 * mode 0 == channel first eg set ch1 stweep Z
 * mode 1 == Z first EG step Z then Ch1 Ch2 then Step Z ...
 */ 

/*
 while(trigArmed)
 { // just sit here and wait for the next command until armed is off,  which can only happen @ end of sequence
   unsigned long tStart = millis() + timeOut; //set timeout position 
   unsigned long tLed = 0;
  // focus commands = start, step, #loops,direction,slave,current step
  //if(program == 0) {inTrigger=true; } //force a first step 
  
  if( inTrigger ) 
  { //we recieved a trigger from our source
    //  and is mode 0, and is at 0 position OR
    // and is mode 1, and is at any position OR
    // if focus isn't enabled
 */   
    /*
     * When should a channel update be issued? When
     *  focus is ON, and mode is sweep per channel (0) AND F position is 0
     *  focus is ON, and mode is slave to channel (1)
     *  focus is off any time
     */
    
 //   boolean runUpdate = true;
    /*
    if( (focArray[1] != 0) && (focArray[4] == 0) ){ //if we are using the focus and focus will sweep through a single channel setting
      if( focArray[5] == 0 ) { runUpdate = true;} //AND if the focus is at position 0 (start of sweep)
    }
    
    if( (focArray[1] !=0) && (focArray[4] == 1)) { runUpdate = true; } // Case where channel is switching each Z plane
    if(focArray[1] == 0) {runUpdate=true;}                           //Case where no focus block used so update the channel
    */
  /*  
    //do DAC and TTL control stuff, not focus stuff though
    if(runUpdate) {
      byte walker=0;
      for(walker = 0 ; walker < 15 ; ++walker ){  //sets DACs 1-16 
        dac_write(10,0, DAC [walker], dacArray [program] [walker]); // Set DAC Lines
        digitalWriteDirect( ttl [walker] , ttlArray[program] [walker] ); //set TTL lines
      }
      digitalWriteDirect( ttl [walker] , ttlArray[program] [walker] ); //set 16th TTL line - 
    }
    ++program;
*/
  /* THIS MOVES AROUND THE Z FOCUS 
   * in this case, we assume a trigger was recieved, but we should only mess with focus stuff if it's on and if it's needed 
   * here we only want to update the focus position in the case that EITHER
   * Mode = 0 Channel 1 - Z 1, Z2, Z3
   * mode = 1 Z 1 - CH1, CH2, Z2, Ch1, Ch2 
   */
/*
    if( (focArray[1] != 0) && ( focArray[4]==0 )){ fastFocus(); }       // if any focus array is active, and MODE = SWEEP OVER CHANNEL
    if( (focArray[1] != 0) && ( focArray[4]==1 )){                      // in this case sweep is active  and MODE = STEP AFTER CHANNEL  
      if((program == maxProgram-1) && (focArray[5] <= focArray[2])) {fastFocus();}            
    }
    
    delay(delArray[program]);  //wait for specified delay          
    
    if(  focArray[1] == 0) {++program;}              //if not using focus at all
    if( (focArray[1] != 0) && (focArray[4] == 1) ) { //focus is used but in step mode
      ++program; 
      if( (program > maxProgram) && (focArray[5] != 0) ) { //because we are stepping the focus, program must be reset to 0 in this case we know the focus has not completed, so we can reset the main program array position
        program=0;
      }
    }
    */
  } //END OF TRIGGER RESPONSE

  /*
   inTrigger=false; //turn off trigger
   tStart = millis() + timeOut; //update timeout delta for next run
   
  //Done moving stuff, now wait for the next input
  while(!inTrigger){ //wait for next pulse
    if(millis() > tStart) {
      trigArmed=false;
      program = maxProgram+1; 
      Serial.println("Timeout Exceeded");
      allOff();
      break;
    } 
    //we hit the timeout so end the sequence   
    if(tLed < millis() ) 
    { 
      digitalWrite(readyLed,!digitalRead(readyLed));  
      tLed = millis() + 30;
    }
  }
 
  if(program > maxProgram) { //end and cleanup
    ++runCycles;
    if(runCycles == timeCycles) { //we are done
      trigArmed=false; 
      program=0;
      allOff();
      Serial.println("!SAFE");
      digitalWrite(readyLed,HIGH);
    }
   if(runCycles < timeCycles) {program = 0;}
  }
 } //close trigarmed
} //close main loop
*/




void allOff() 
{
  for(byte walker=0;walker<15;++walker)
  { //sets DACs 1-16                
    dac_write(10,0, DAC [walker], 0); // Set DAC Lines
  }
  setPinGroup(0,0);
  setPinGroup(1,0);     
}


void clearSerial()
{
  //STUFF TO CLEAN OUT THE SERIAL LINE
  inputString = "";     // clear the string:
  stringComplete = false;
}
  
/*PC DAC CONTROL*/
void setDac(byte dNum,int dVal)
{  
  dac_write(10,0, dNum, dVal); // Send dac_code
  //led indication
  if (useSignalLEDs_)
  {
    int dacSum = 0;
    for (byte d=0; d < 16; d++)
    {
      dacSum += dacState[d];
    }
    mcp.digitalWrite(dacLed, dacSum > 0);
  }
}

// sets the output state of the given pin number
void setTTL(byte t1, boolean t2)
{
  byte pin = t1 - 1;
  if(pin < 9) {
    digitalWriteFast(ttl[pin], t2);
    }
  if(pin > 8) {
    mcp.digitalWrite(ttl[pin], t2);
    }  
  if(t2)
  {
    bitSet(ttlState, pin);
  } else 
  {
    bitClear(ttlState, pin);
  }  
  if (useSignalLEDs_)
  {
    mcp.digitalWrite(ttlLed, ttlState > 0);
  }
}

void setDacCheckBlanking(byte dacNr)
{
  if (dacBlanking[dacNr])
  {
    triggerPinState = digitalReadFast(trig[0]);
    dacBlankOnLow[dacNr] == triggerPinState ? 
        setDac(dacNr, dacState[dacNr]) : setDac(dacNr, 0); 
  } else {
    setDac(dacNr, dacState[dacNr]);
  }
}


void setPinGroupCheckBlanking(byte pinGroup)
{
  if (pinGroupBlanking[pinGroup])
  {
    triggerPinState = digitalReadFast(trig[0]);
    pinGroupBlankOnLow[pinGroup] == triggerPinState ? 
        setPinGroup(pinGroup, pinGroupState[pinGroup]) : setPinGroup(pinGroup, 0); 
  } else {
    setPinGroup(pinGroup, pinGroupState[pinGroup]);
  }
}

inline void setPinGroup(byte, byte) __attribute__((always_inline));
// sets pins 1-8 (pinGroup 0) or 9-16 (pinGroup 1) according to the mask in value
inline void setPinGroup(byte pinGroup, byte value)
{
  byte adder = (pinGroup) * 8;
  for (byte b = 0; b < 8; b++)
  {
      if( b+adder < 9 ) {
        digitalWriteFast(ttl[b + adder], (((value) >> (b)) & 0x01) );
      }

      else if( b+adder > 8) {
        mcp.digitalWrite(ttl[b+adder],(((value) >> (b)) & 0x01));
      }
      
      //Serial.print("TTL " );
      //Serial.print(b + adder);
      //Serial.print(" , ");
      //Serial.println((((value) >> (b)) & 0x01));
      
  }
  if (pinGroup == 1) 
  {
    ttlState = (ttlState & 0xff00) | value;
  } else 
  {
    ttlState = (ttlState & 0x00ff) | (value << 8);
  }  
  if (useSignalLEDs_)
  {
    mcp.digitalWrite(ttlLed, ttlState > 0);
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  trigArmed = false;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

/*INTERRUPT CODE FOR TTL INPUT ***************/
/*
void sigIn()     //sigin is the input response line - this recieves the trigger input from an external source
{
  //if(!trigArmed) 
  //{
    digitalWrite(trigLed,!digitalRead(trigLed));
  //} 
  inTrigger=true; 
}
  
void configureTrigger(byte tOption) 
{
  trigMode = tOption; //assign input value to global
  switch (trigMode) {
  case 0:
    attachInterrupt(trig[0],sigIn,LOW);
    break;
  case 1:
    attachInterrupt(trig[0],sigIn,HIGH);
    break;
  case 2:
    attachInterrupt(trig[0],sigIn,RISING);
    break;
  case 3:
    attachInterrupt(trig[0],sigIn,FALLING);
    break;
  case 4:
    attachInterrupt(trig[0],sigIn,CHANGE);
    break;
  }
}
*/
  
void debug()
{
  if(debugT < millis() ) //if this is the first time debug has run, this will execute, otherwise has enough time elapsed?
  {  
    Serial.print("Input Trigger = ");
    Serial.println(digitalReadFast(trig[0]));
    //Serial.print(", OpMode = ");
    //Serial.println(opMode);
    
    // REPORT TTL    
    Serial.print("TTL: ");
    for(int i=0;i<16;++i) 
      {
        char sOut[100];
        if(i<9) {sprintf(sOut,"%d=%d,",i+1, digitalRead(ttl[i]));}
        else if(i>8) {sprintf(sOut,"%d=%d,",i+1, mcp.digitalRead(ttl[i]));}
        Serial.print(sOut);
      }
    Serial.println(""); 
    
    //REPORT DAC
    Serial.print("DAC:");
    for(int i=0;i<16;++i) 
    {
      char sOut[200];
      sprintf(sOut,"%d=%u,",i+1, dacState[i]);
      Serial.print(sOut); //used to print sOut
    }

    Serial.println();
    Serial.println("Digital output buffers:");
    for (int pg = 0; pg < 2; pg++)
    {
      if (pg == 0) Serial.print("Pins 1-8 buffer size 1-8: ");
      else if (pg == 1) Serial.print("Pins 9-16 buffer size: ");
      char sOut[6];
      sprintf(sOut, "%d", ttlArrayMaxIndex[pg]);
      Serial.println(sOut);  
      for (int i = 0; i < ttlArrayMaxIndex[pg]; i++) 
      {
        sprintf(sOut, "%u ", ttlArray[i][pg]);
        Serial.print(sOut);  
      }
      if (ttlArrayMaxIndex[pg] > 0) { Serial.println(); }
    }
    
    Serial.println("DAC buffers:");
    for (int dac = 0; dac < NR_DACS; dac++)
    {
      char sOut[25];
      sprintf(sOut, "DAC buffer size: %d", dacArrayMaxIndex[dac]);
      Serial.println(sOut);
      for (int i = 0; i < dacArrayMaxIndex[dac]; i++)
      {
        sprintf(sOut, "%u ", dacArray[i][dac]);
        Serial.print(sOut);
      }
      if (dacArrayMaxIndex[dac] > 0) { Serial.println(); }
    }
    
  }
  // send an empty line so that the receiver know we are done
  Serial.println("");
}
    
 /*
    //Report program arrays 
    if(opMode == 3)
      {
      Serial.println("Sequencer Programming Status");
     Serial.print("MaxProgram = ");
     Serial.println(maxProgram);
     Serial.print("PCHANNEL = ");
     Serial.println(pChannel);
     //report DACs
     Serial.println("PROG, DAC1, DAC2, DAC3, DAC4, DAC5, DAC6, DAC7, DAC8, DAC9,DAC10,DAC11,DAC12,DAC13,DAC14,DAC15,DAC16/FOCUS");
     for(int p=0;p<maxProgram+1;++p) //list all recorded programs
      {      
     char sOut[200];
     sprintf(sOut,"P:%2d,",p+1);
     Serial.print(sOut);
        for(byte nVal=0;nVal<16;++nVal)
        {
          sprintf(sOut,"%05u,",dacArray[p][nVal]);
          Serial.print(sOut);
        }
        Serial.println("");   
      }
     
     //Report TTL's 
     Serial.println("PROG, TTL1, TTL2, TTL3, TTL4, TTL5, TTL6, TTL7, TTL8, TTL9,TTL10,TTL11,TTL12,TTL13,TTL14,TTL15,TTL16");
     for(int p=0;p<maxProgram+1;++p) //list all recorded programs
      {      
     char sOut[200];
     sprintf(sOut,"P:%2d,",p+1);
     Serial.print(sOut);
        for(byte nVal=0;nVal<16;++nVal)
        {
          sprintf(sOut,"    %d,",ttlArray[p][nVal]);
          Serial.print(sOut);
        }
        Serial.println("");   
      }
      
      debugT = millis() + 500; // wait 500ms before the next report
      } 
    }
    */


void diagTest()
 {
        ///*use this to test all 8 DAC lines ***IF NEEDED**
  Serial.println("***** TRIGGERSCOPE QC TEST PROCEDURE - REQUIRES MULTIMETER OR OSCILLOSCOPE....*****");
  Serial.println("***** AFTER EACH TEST,TRANSMIT ANY CHARACTER TO BEGIN THE NEXT TEST           *****");
  Serial.println("***** TESTS TO BE PERFORMED:                                                  *****");
  Serial.println("***** TEST1: DAC +10V ALL LINES                                               *****");
  Serial.println("***** TEST2: DAC -10V ALL LINES                                               *****");
  Serial.println("***** TEST3: TTL 5V ALL LINES                                                 *****");
  Serial.println("***** TEST4: TRIG ALL LINES                                                   *****");
  Serial.println("***** TEST5: ALL LEDs                                                         *****");
  Serial.println("***** TX DATA TO CONTINUE....                                                 *****");
  while(Serial.available() == 0) { delay(10); } //wait for any input from the keyboard

  //TEST 1    
  clearSerial();
  for(int i=0;i<16;++i) { setDacRange(i,1); dac_write(10,0,i,65535);}
  Serial.println("*Test 1: DAC Output: Check all DAC pins 1-16, should = +10V - tx data to continue....");
  while(!Serial.available()) { delay(10); } //wait for any input from the keyboard

  //TEST 2
  clearSerial();
  for(int i=0;i<16;++i) { setDacRange(i,3); dac_write(10,0,i,0);} 
  Serial.println("*Test 2: DAC Output: Check all DAC pins 1-16, should = -10V - tx data to continue....");
  while(Serial.available() == 0) { delay(10); } //wait for any input from the keyboard
 
  //TEST 3
  clearSerial();
  for(int i=0;i<16;++i) { setDacRange(i,1); dac_write(10,0,i,0);}
  for(int i=0;i<16;++i) { digitalWriteDirect(ttl[i],1);}  
  Serial.println("*Test 3: TTL Output: Check all TTL pins 1-16, should = 5V - tx data to continue....");
  while(Serial.available() == 0) { delay(10); } //wait for any input from the keyboard

  //TEST 4
  clearSerial();
  for(int i=0;i<16;++i) { digitalWriteDirect(ttl[i],0);} 
  Serial.println("*Test 4: TRIG Input: Connect a jumper wire from TTL 1 to TRIG Line 2.");
  Serial.println("Test will continue once signal is detected or tx data is recieved.....");
  
  digitalWriteDirect(ttl[0],1);
  while(digitalRead(trig[0]) == 0 && Serial.available() == 0) { delay(10); }
  if(digitalRead(trig[0]) == 1) {Serial.println("Got 5V on Trig 1....PASSED");}
  else{Serial.println("No input detected, TRIG 1 FAILED - please retry this test...");}
  delay(100);
  Serial.println("Connect a jumper wire from TTL 1 to TRIG Line 2.");
  while(digitalRead(trig[1]) == 0 && Serial.available() == 0) { delay(10); }
  if(digitalRead(trig[1]) == 1) {Serial.println("Got 5V on Trig 2....PASSED");}
  else{Serial.println("No input detected, TRIG 2 FAILED - please retry this test...");}
  delay(100);
  Serial.println("Connect a jumper wire from TTL 1 to TRIG Line 3.");
  while(digitalRead(trig[2]) == 0 && Serial.available() == 0) { delay(10); }
  if(digitalRead(trig[2]) == 1) {Serial.println("Got 5V on Trig 3....PASSED");}
  else{Serial.println("No input detected, TRIG 3 FAILED - please retry this test...");}
  delay(100); 
  Serial.println("Connect a jumper wire from TTL 1 to TRIG Line 4.");
  while(digitalRead(trig[3]) == 0 && Serial.available() == 0) { delay(10); }
  if(digitalRead(trig[3]) == 1) {Serial.println("Got 5V on Trig 3....PASSED");}
  else{Serial.println("No input detected, TRIG 4 FAILED - please retry this test...");}
  delay(100); 
  digitalWriteDirect(ttl[0],0);

  digitalWrite(pwrLed,1);
  digitalWrite(dacLed,1);
  digitalWrite(ttlLed,1);
  digitalWrite(trigLed,1);
  digitalWrite(readyLed,1);
  
  Serial.println("*Test 5: Visually check all 5 lights work: POWER, READY, TTL, DAC, TRIG  - tx data to continue....");
  clearSerial();
  while(Serial.available() == 0) { delay(10); } //wait for any input from the keyboard

  Serial.println("------------TEST PROCEDURE COMPLETE-------------");
}

/**
 * This function converts the user's input with requests for analog blanking, sequenceing, pulse delay and pulse
 * duration into a list with timed events that can be executed sequentially with the indicated delays in between
 * Output of this protocol is stored in the "dacBlankEvent" variables
 */
void generateDacBlankEvents()
{
  /*
int    dacArray[NR_DAC_STATES][NR_DACS] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; // DACprogram list
uint8_t ttlArray[NR_DO_STATES][2] = {{0,0}}; // digital output states program list
int ttlArrayMaxIndex[2] = {0, 0}; // maintains the max index in the array that was set
int ttlArrayIndex[2] = {0, 0}; // keeps track of current position in the array
int dacArrayMaxIndex[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int dacArrayIndex[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t dacblankDelay[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t dacblankDuration[NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

bool dacBlanking[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
bool dacBlankOnLow[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
bool dacSequencing[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
byte dacSequenceMode[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// data structures to be assembled from blanking settings above that have a time-ordered sequence of events
int dacBlankEventsNr = 0;
// there can be a delay and a duration for each blanking event
uint32_t dacBlankEventNextWait[2 * NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t dacBlankEventPinNr[2 * NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// 0 : off, 1: set normal state, 2: set value from dacArray
uint8_t dacBlankEventState[2 * NR_DACS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  */

  // note: this should probably be duplicated for both trigger directions, ignore now for simplicity
  
  int nrDacsInUse = 0;
  int dacsUsed [NR_DACS] =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for (int i = 0; i < NR_DACS; i++) {
    if (dacBlanking[i]) { 
      dacsUsed[nrDacsInUse] = i;
      nrDacsInUse++;
    }
  }
  for (int dac = 0; dac < nrDacsInUse; dac++) {
    if (dacBlankDelay[dac] == 0) {
      dacBlankEventNextWait[dacBlankEventsNr] = 0;
      dacBlankEventPinNr[dacBlankEventsNr] = dac;
      dacBlankEventState[dacBlankEventsNr] = dacSequencing[dac] ? 2 : 1;
      dacBlankEventsNr++;
    }
  }
  
}


void clearTable()
{
  for(byte i=0;i<16;++i) //all 16 channels
  {
    for(int n=0;n<NR_DAC_STATES; ++n) //all program lines
    {
      dacArray[n][i] = 0; //clear dac
    }
  }
  for (byte i=0; i < 2; i++) 
  {
    clearPDO(i);
  }
  Serial.println("!CLEAR_ALL"); 
}

void clearDac()
{
  byte offSet = 10;
  char instring[15] = {}; //create a string to hold char ascii for later conversion to integer value
  for(byte sl=0;sl<inputString.length()-offSet;++sl)
  { //figure out length of string and calc # characters which (should be) numbers for DAC
  instring[sl] = inputString[sl+offSet]; //assign 7th and farther numbers to char table
  //Serial.print(fstring[sl]);
  }
  byte inLine = atoi(instring); //convert char table to useable integer for DAC level
  inLine = inLine - 1;
  for(byte i = 0 ; i<50;++i)
    {
    dacArray[i][inLine] = 0;  
    }
  Serial.print("!CLEAR_DAC,"); //print recieve message to operator
  Serial.println(inLine+1);
  }

inline void clearPDO(byte bank)
{
  for(int  i = 0 ; i < NR_DO_STATES; i++)
  {
    ttlArray[i][bank] = 0;  
  }
  ttlArrayMaxIndex[bank] = 0;
}

inline void clearPAO(int dacNrZeroBased)
{
  for (int i=0; i < NR_DAC_STATES; i++)
  {
    dacArray[i][dacNrZeroBased] = 0;
  }
  dacArrayMaxIndex[dacNrZeroBased] = 0;
}


inline void clearPOD(int dacNrZeroBased)
{
  for (int i=0; i < NR_DAC_STATES; i++)
  {
    podArray[i][dacNrZeroBased] = 0; 
  }
  dacArrayMaxIndex[dacNrZeroBased] = 0;
}
inline void clearPOV(int dacNrZeroBased)
{
  for (int i=0; i < NR_DAC_STATES; i++)
  {
    povArray[i][dacNrZeroBased] = 0; 
  }
  dacArrayMaxIndex[dacNrZeroBased] = 0;
}

void clearDelay()
  {
  for(byte i = 0 ; i<50;++i)
  {
    delArray[i]= 0;  
  }
  Serial.println("!CLEAR_DELAY"); //print recieve message to operator
}


void setDacRange(byte dacLine, byte range)
{
    /*dacLine 0 indexed   
     * range 0-5 corresponds to the following:
        SPAN_0_TO_5V             0x0000
        SPAN_0_TO_10V            0x0001
        SPAN_PLUS_MINUS_5V       0x0002
        SPAN_PLUS_MINUS_10V      0x0003
        SPAN_PLUS_MINUS_2V5      0x0004
     */
  dac_write(10,1,dacLine,range); //issue span command
  dac_write(10,2,0,0); //issue update all lines command
}

void speedtest() {
  
  while(Serial.available() == 0) {
    for(volatile int i=10000;i<40000;i=i+1000) {
      for(volatile int f=10000;f<40000;f=f+10){
        dac_write(10,0, 11, f); // Set DAC Lines
      }
    dac_write(10,0, 10, i); // Set DAC Lines
    }
  }
}

int8_t dac_write(uint8_t cs, byte command, uint8_t dac_address, uint16_t dac_code) {
// Write the 16-bit dac_code 
  /*
  Serial.print(" DW=");
  Serial.print( dac_address);
  Serial.print(",");
  Serial.println(dac_code);
  */
  static uint8_t last_data_array[4];
  uint8_t data_array[4], rx_array[4];
  int8_t ret;
  LT_union_int16_2bytes data;

  data.LT_int16 = dac_code;                              // Copy DAC code
  data_array[3] = 0;                                     // Only required for 32 byte readback transaction
  if(command == 0) { data_array[2] = 0x30 | dac_address;}            // Build command / address byte
  if(command == 1) { data_array[2] = 0x60 | dac_address;}            // span dac
  if(command == 2) { data_array[2] = 0xA0 | dac_address;}
  // ***NOT SURE WHY BUT THIS MUST BE OFF! data_array[2] = 0x30 | dac_address;             // Build command / address byte
  data_array[1] = data.LT_byte[1];                       // MS Byte
  data_array[0] = data.LT_byte[0];                       // LS Byte
/*
#define  LTC2668_CMD_WRITE_N              0x00  //!< Write to input register n
#define  LTC2668_CMD_UPDATE_N             0x10  //!< Update (power up) DAC register n
#define  LTC2668_CMD_WRITE_N_UPDATE_ALL   0x20  //!< Write to input register n, update (power-up) all
#define  LTC2668_CMD_WRITE_N_UPDATE_N     0x30  //!< Write to input register n, update (power-up) 
#define  LTC2668_CMD_POWER_DOWN_N         0x40  //!< Power down n
#define  LTC2668_CMD_POWER_DOWN_ALL       0x50  //!< Power down chip (all DAC's, MUX and reference)
#define  LTC2668_CMD_SPAN                 0x60  //!< Write span to dac n
#define  LTC2668_CMD_CONFIG               0x70  //!< Configure reference / toggle
#define  LTC2668_CMD_WRITE_ALL            0x80  //!< Write to all input registers
#define  LTC2668_CMD_UPDATE_ALL           0x90  //!< Update all DACs
#define  LTC2668_CMD_WRITE_ALL_UPDATE_ALL 0xA0  //!< Write to all input reg, update all DACs
#define  LTC2668_CMD_MUX                  0xB0  //!< Select MUX channel (controlled by 5 LSbs in data word)
#define  LTC2668_CMD_TOGGLE_SEL           0xC0  //!< Select which DACs can be toggled (via toggle pin or global toggle bit)
#define  LTC2668_CMD_GLOBAL_TOGGLE        0xD0  //!< Software toggle control via global toggle bit
#define  LTC2668_CMD_SPAN_ALL             0xE0  //!< Set span for all DACs
#define  LTC2668_CMD_NO_OPERATION         0xF0  //!< No operation
*/


  spi_transfer_block(cs, data_array, rx_array, (uint8_t) 4);
  // Compare data read back to data that was sent the previous time this function was called
  if ((rx_array[2] == last_data_array[2]) && (rx_array[1] == last_data_array[1]) && (rx_array[0] == last_data_array[0]))
  {
    ret = 0;
  }
  else
  {
    ret = 1;
  }

  last_data_array[0] = data_array[0]; // Copy data array to a static array to compare
  last_data_array[1] = data_array[1]; // the next time the function is called
  last_data_array[2] = data_array[2];

  return(ret);
}

void spi_transfer_block(uint8_t cs_pin, uint8_t *tx, uint8_t *rx, uint8_t length)
{
  int8_t i;
  output_low(cs_pin);                 //! 1) Pull CS low

  for (i=(length-1);  i >= 0; i--)
    rx[i] = SPI.transfer(tx[i]);    //! 2) Read and send byte array

  output_high(cs_pin);                //! 3) Pull CS high
}

inline void digitalWriteDirect(int, boolean) __attribute__((always_inline));

void digitalWriteDirect(int pin, boolean val){
    if(pin < 9) {digitalWriteFast(pin,val);}
    else if(pin>8) {mcp.digitalWrite(pin,val);}
}

/*
inline int digitalReadDirect(int) __attribute__((always_inline));

int digitalReadDirect(int pin){
  return !!(g_APinDescription[pin].pPort -> PIO_PDSR & g_APinDescription[pin].ulPin);
}

inline int digitalReadOutputPin(int) __attribute__((always_inline));

int digitalReadOutputPin(int pin){
  return !!(g_APinDescription[pin].pPort -> PIO_ODSR & g_APinDescription[pin].ulPin);
}
*/


  
/*******************LICENSING INFO**************

 * Copyright (c) 2018, Advanced Research Consulting 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * 
 * 
 *******************/