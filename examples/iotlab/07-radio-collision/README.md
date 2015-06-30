# MAC Collision Test

Illustrates radio collision using different MAC layers, specified at compiling:

- NullMAC layer
- CSMA layer
- Default Contiki layer (ContikiMAC)

Behaviour:

  - When receiving the character 'h', print the help.
  - When receiving the character 'b', sends a broadcast message at maximal power.
  - When receiving a broadcast message, prints a report on its serial link and answer with a unicast message.

## Serial reporting
When sending the broadcast message, prints the Energy consumption (in time):
- LPC
- CPU
- LISTEN
- TRANSMIT
```
TODO : example
```

When receiving the broadcast message:
```
150.112;broadcast message received from:,174.124,"ping".
```
When sending the unicast message:
```
174.124;unicast message received from:150.112,"pong".
```

## Build firmware
Compile for WSN430 CC1101 using nullmac protocol:
```
make TARGET=wsn430 RADIO=WITH_CC1101 NET_CONF=nullmac
``` 
Compile for WSN430 CC2420 using CSMA protocol:
```
make TARGET=wsn430 RADIO=WITH_CC2420 NET_CONF=csma
```
If `NET_CONF` is not specified the MAC protocol used is ContikiMAC.

