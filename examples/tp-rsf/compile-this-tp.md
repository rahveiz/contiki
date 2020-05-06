# Compile the firmware for this TP

1. Setup your environment

```bash
<you>@<yourcomputer>~$ ssh <login>@<site>.iot-lab.info
<login>@<site>~$ git clone https://github.com/iot-lab/openlab.git
<login>@<site>~$ git clone https://github.com/iot-lab/contiki.git
```

2. The example for this TP is located in `contiki/examples/tp-RSF/`. View and analyze the source code
```bash
<login>@<site>~$ cd contiki/examples/tp-RSF/
<login>@<site>:~/contiki/examples/tp-RSF/$ less node.c
less project-conf-contikimac.h
less project-conf-tsch.h
```

3. Compile the example
```bash
<you>@<yourcomputer>~$ ssh <login>@<site>.iot-lab.info
<login>@<site>~$ cd contiki/examples/tp-rsf
<login>@<site>:~/contiki/examples/tp-rsf$ make tp-rsf
```

4. You should have 4 new binary files:
```
<login>@<site>:~/contiki/examples/tp-rsf$ ls
...
source-contikimac.iotlab-m3
sink-contikimac.iotlab-m3
source-tsch.iotlab-m3
sink-tsch.iotlab-m3
...
```

5. Download the firmware to your local computer
```bash
<you>@<yourcomputer>~$ scp <login>@<site>.iot-lab.info:~/contiki/examples/tp-rsf/*-m3 .
```
