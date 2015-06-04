# MAC Collision test
=======================

## MAC Collision test on CC2420 and CC1101 nodes
----------------------


**This project contains a radio collision test using differents MAC layer**

- NullMAC layer
- CSMA layer
- Default Contiki layer: ContikiMAC

When receiving the character 'h', print the help.
When receiving the character 'b', sends a broadcast message at maximal power.

The report message written on the serial link contains:

- Energy consumption (in time):
        -LPC
        -CPU
        -LISTEN
        -TRANSMIT

-"dest;broadcast message received from:",source,"ping".

When receiving the broadcast message, send a unicast message.

The report message written on the serial link contains:

-"dest;unicast message received from:",source,"pong".




