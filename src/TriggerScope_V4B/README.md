# Triggerscope
Micro-Manager-specific firmware for the Triggerscope.

The [Triggerscope 4](http://arc.austinblanco.com/product/triggerscope-4/) 
is an Arduino-based device build and sold by "Advanced Research Consulting" 
(https://arc.austinblanco.com/) that provides analog and digital outputs.  

This firmware - in combination with the Micro-Manager "TriggerscopeMM" device adapter, 
allows for control of 16 analog and 16 digital outputs.  Outputs can 
transition between settings triggered by a Trigger input 
signal at micro-second time scales.  For full documentation
of the use of this firmare, see: https://micro-manager.org/wiki/TriggerScopeMM

To install this firmware, you will first need to download and install the [TeensyDuino package](https://www.pjrc.com/teensy/td_download.html), and the  [Arduino IDE](https://www.arduino.cc/en/software). Then power your TriggerScope, connect the USB cable to your computer, and open the file TriggerScope_613MM/TriggerScope_613MM.ino in the [Arduino IDE](https://www.arduino.cc/en/software). Select the port under which your device appears (Tools > Port), and select the Teensy 4.1 (Tools > Board). Press the "verify" button, and - if compilation succeeds - press the Upload button.
