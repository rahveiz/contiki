# MAC Collision test
=======================

## MAC Collision test on CC2420 and CC1101 nodes
----------------------

This project contains a radio collision test using differents MAC layer.

- NullMAC layer
- CSMA layer
- Default Contiki layer: ContikiMAC

<<<<<<< HEAD
When receiving the character 'h', print the help.

When receiving the character 'b', sends a broadcast message at maximal power.
The report message written on the serial link contains:
=======
Behaviour:

- When receiving the character 'h', print the help.
- When receiving the character 'b', sends a broadcast message at maximal power.
>>>>>>> 58472ea5be2119784716ed4b1b4038226eee741b

Energy consumption (in time):
- LPC
- CPU
- LISTEN
- TRANSMIT

<<<<<<< HEAD
```
"150.112;broadcast message received from:",12.124,"ping".
```

When receiving the broadcast message, send a unicast message.
The report message written on the serial link contains:

```
"12.124;unicast message received from:",150.112,"pong".
=======
### Command for WSN430 CC2420 using nullmac protocol:
 make TARGET=wsn430 RADIO=WITH_CC2420 NET_CONF=nullmac
 
### Command for WSN430 CC2420 using CSMA protocol: 
 make TARGET=wsn430 RADIO=WITH_CC2420 NET_CONF=csma

If the MAC protocol used is Default protocol, it is no necessary to specify the NET_CONF configuration 

## Serial reporting

When receiving the broadcast message:
Example:
```
150.112;broadcast message received from:,174.124,"ping".
```
When receiving the broadcast message, send a unicast message.
Example:
```
174.124;unicast message received from:150.112,"pong".
>>>>>>> 58472ea5be2119784716ed4b1b4038226eee741b
```



