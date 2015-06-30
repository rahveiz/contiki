# MAC Collision test
=======================

## MAC Collision test on CC2420 and CC1101 nodes
----------------------

This project contains a radio collision test using differents MAC layer.

- NullMAC layer
- CSMA layer
- Default Contiki layer: ContikiMAC

When receiving the character 'h', print the help.

When receiving the character 'b', sends a broadcast message at maximal power.
The report message written on the serial link contains:

Energy consumption (in time):
- LPC
- CPU
- LISTEN
- TRANSMIT

```
"150.112;broadcast message received from:",12.124,"ping".
```

When receiving the broadcast message, send a unicast message.
The report message written on the serial link contains:

```
"12.124;unicast message received from:",150.112,"pong".
```



