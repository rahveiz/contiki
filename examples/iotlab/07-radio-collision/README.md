# MAC Collision test
=======================

## MAC Collision test on CC2420 and CC1101 nodes
----------------------

This project contains a radio collision test using differents MAC layer.

- NullMAC layer
- CSMA layer
- Default Contiki layer: ContikiMAC

Behaviour:

- When receiving the character 'h', print the help.
- When receiving the character 'b', sends a broadcast message at maximal power.

Energy consumption (in time):
- LPC
- CPU
- LISTEN
- TRANSMIT

## Serial reporting

When receiving the broadcast message:
Example:
```
"150.112;broadcast message received from:",174.124,"ping".
```
When receiving the broadcast message, send a unicast message.
Example:
```
"174.124;unicast message received from:",150.112,"pong".
```



