QnxSignalsToVolts
=================

The fabulous QNX implementation for providing rough indication of voltage from a signal generator
This is a project for an Embedded Real Time Systems course @ RIT.

Implements an embedded, real-time stand-alone system to provide a rough 
indication of voltage using servo motors. This QNX implementation reads the input wave from the signal generator
and coverts it to a voltage value. It sends this to the Freescale implementation, which will move the servos
motors to indicate the voltage the board received.
