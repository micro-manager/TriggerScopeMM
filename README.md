# Triggerscope
Micro-Manager-specific firmware for the Triggerscope.

The Triggerscope (https://advancedresearch-consulting.com/product/triggerscope-4/) 
is an Arduino-based device build and sold by "Advanced Research Consulting" 
(https://advancedresearch-consulting.com/) that provides analog and digital outputs.  

This firmware - in combination with the Micro-Manager "TriggerscopeMM" device adapter, 
allows for control of 16 analog and 16 digital outputs.  Outputs can 
transition between settings triggered by a Trigger input 
signal at micro-second time scales.  For full documentation
of the use of this firmware, see: https://micro-manager.org/wiki/TriggerScopeMM

# Firmware versions
TriggerScope version 3 boards (serial numbers 1932-1970) must use the TriggerScope_V3 firmware.

TriggerScope version 4 boards (serial numbers 1971-2117) must use the TriggerScope_V4 firmware.

TriggerScope version 4B boards (serial numbers 2118 and later) must use the TriggerScope_V4 firmware.

An extension of the firmware which allows overdrive pulses to be applied at the beginning of the analog signal is also available for V4 and V4B boards.