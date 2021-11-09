# Triggerscope
Micro-Manager-specific firmware for the Triggerscope.

The [Triggerscope 3](http://arc.austinblanco.com/product/triggerscope-3/) 
is an Arduino-based device build and sold by "Advanced Research Consulting" 
(https://arc.austinblanco.com/) that provides analog and digital outputs.  

This firmware - in combination with the Micro-Manager "TriggerscopeMM" device adapter, 
allows for control of 16 analog and 16 digital outputs.  Outputs can 
transition between settings triggered by a Trigger input 
signal at micro-second time scales.  For full documentation
of the use of this firmare, see: https://micro-manager.org/wiki/TriggerScopeMM

To install this firmware, you download and install the [Arduino IDE](https://www.arduino.cc/en/software). Then power your TriggerScope, connect the USB cable to your computer, and open the file TriggerScope_V3/TriggerScope_V3.ino in the [Arduino IDE](https://www.arduino.cc/en/software). Select the port under which your device appears (Tools > Port), and select the Arduino Due Programmin port (Tools > Board). Press the "verify" button, and - if compilation succeeds - press the Upload button.

Some timing measurements using the "blanking" mode for TTL1-8 in Micro-Manager: It takes about 10-13 micro-seconds for the TTL output to respond to a change in the input trigger.  Adding sequences to DACs or other outputs will likely increase this delay.
