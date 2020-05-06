# Wireless Networks Lab - IoT

In this lab you are going to learn how to deploy an experiment on a remote IoT testbed, the [FIT-IoT LAB](https://www.iot-lab.info/).
You are going to deploy [ContikiMAC](http://dunkels.com/adam/dunkels11contikimac.pdf) and [802.15.4-TSCH](http://www.simonduquennoy.net/papers/duquennoy17tsch.pdf) on an [M3 open node](https://www.iot-lab.info/hardware/m3/), analyze their packets and compare the performance.

You will hand in a small report with a screenshot/figure of each step and a brief explanation of what is it about (it can be in french).

<!-- The first 3 sections of this assignment are based on the [tutorials](https://www.iot-lab.info/tutorials/) available on the FIT-IoT LAB website and a workshop of the Ph.D. summer school ResCom 2019. -->
This assignment is based on the [tutorials](https://www.iot-lab.info/tutorials/) available on the FIT-IoT LAB website.

All the tutorials must be done in the Strasbourg site (not in Grenoble!).

# Grading system

## Deliverables
Every point must include a screenshot/figure and a brief explanation
- Authentication in the webportal showing that your accounted is correctly logged in
- Access through ssh to the Strasbourg site
- Your first experiment collecting sensor data, communication working
- First tutorial monitor power consumption
- First tutorial monitor radio signal
- ContikiMAC communication working
- TSCH communication working
- Power consumption comparison between ContikiMAC and TSCH
- Wireshark packet analysis
- Source code (project-conf-*.h, node.c)
- Communication in the leaderboard network
- Your team rank in the global leaderboards ([ContikiMAC](https://drive.google.com/file/d/1DRjdNB97H6NGtvY83zxyvSgVBfsDX99B/view?usp=sharing) and [TSCH](https://drive.google.com/file/d/1NMQGJutBAqL0IUB6WoJ5QQgXBRnFGKYo/view?usp=sharing))
- Monitoring radio signal in all 802.15.4 channels simultaneously with a single node

The quality of the figures and explanations for each point will determine the grade.

# 1 - Authentication Settings
- Make teams of 2 students each and decide a name for your team
- Get your temporary login / password (ask me by private message, telling me the name of the members of the team)
- [Log into the Webportal](https://www.iot-lab.info/testbed/)
- [Configure Your SSH Access](https://www.iot-lab.info/tutorials/ssh-access) in the Webportal

# 2 - First Experiment
- [Create a New Experiment with M3 nodes and the Web Portal](https://www.iot-lab.info/tutorials/submit-experiment-m3-web/)

# 3 - Monitoring
*NOTE: in order to remotely plot monitoring results, we use X11 forwarding inside SSH tunnel: \
For Linux Users: ready to go! \
For Mac Users: [install XQuartz](https://www.xquartz.org/) \
For Windows Users: [install Xming](https://sourceforge.net/projects/xming/) , [see tutorial with Putty](https://quick-tutoriel.com/comment-utiliser-loption-x11-forwarding-sous-putty/)*

If you have errors plotting in the following steps, in general, it's because X11 forwarding is not working properly. Make sure it is correctly installed or log out and in again of your ssh session (and make sure you use the option -X).

<!-- NOTE: the 'last' folder in .iot-lab/ corresponds to the last experiment deployed (even if it is still running) -->

- [Monitor power consumption](https://www.iot-lab.info/tutorials/monitoring-consumption-m3/)
- [Monitor radio signal](https://www.iot-lab.info/tutorials/monitoring-radio-m3/)
  - NOTE: go directly to step 4 and do not recompile firmware. You will all use channel 11, so you are going to see the activity of your classmates
- [Sniff packets and analyze them in Wireshark](https://www.iot-lab.info/tutorials/monitoring-sniffer-m3/)
  - IMPORTANT: We just want to monitor 2 nodes for 10 minutes and we don't care about the node ID. So modify the steps 6 and 7 of this tutorial with:
    - 10 minutes
    - Add 1 M3 nodes with the same firmware
    - Add 1 M3 node with the same firmware and the sniffer profile (sniff_11)

    Then, make sure that you use the sniffer node ID in step 12 and 13, and the other node ID in step 14.

# 4 - Deploying ContikiMAC and TSCH with Contiki OS
<!-- - [Get and compile firmware for M3 nodes](https://www.iot-lab.info/tutorials/contiki-compilation/) -->
<!-- - [Get and compile firmware for M3 nodes](networking-with-contiki.md) -->
- [Get and compile the firmware for this TP](compile-this-tp.md)

Now that you have some experience on the IoT-LAB, follow the next steps on your own:
- Deploy ContikiMAC on 2 nodes (1 source and 1 sink) for 10 minutes
  - Use the following channel: trailing number in your iotlab user + 10 (ex: for stras2019wl8, channel: 18). What can happen if all the teams stay in the same channel?
    - You will need to analyze the example source code for this
    - Re-compile the firmware and use these binary files: `source-contikimac.iotlab-m3` and `sink-contikimac.iotlab-m3`
  - Monitor the power consumption on the source node (Period = 8244 µs; Average = 4)
  - Sniff packets on the sink in the corresponding channel
- Deploy 802.15.4-TSCH on 2 nodes for 10 minutes
  - Use the following PAN ID: trailing number in your iotlab user + 10 (ex: for stras2019wl8, PAN ID: 18). What can happen if all the teams stay in the same PAN ID?
    - You will need to analyze the example source code for this
    - Re-compile the firmware and use these binary files: `source-tsch.iotlab-m3` and `sink-tsch.iotlab-m3`
  - Monitor the power consumption on the source node (Period = 8244 µs; Average = 4)
  - Sniff packets on the sink in. Choose only 1 channel to sniff, and make sure it is used by TSCH.
- Compare the results. What differences do you notice in the power consumption between the two protocols? Explain the cause of that difference
- Analyze them in Wireshark for both cases . Find your team packets, other teams packets, regular data packets, acknowledgments and beacons.
- Deploy 1 source node with each protocol and connect them to the leaderboard network and count your delivered packets:
  - Setup ContikiMAC with the following parameters:
    - PAN ID: 0xF00D
    - Channel: 22
  - Setup TSCH with the following parameters:
    - PAN ID: 0xC0DE
  - Edit the code so that you send **your team name** in the packet **payload**.
  - Have a look at the **leaderboards** for [ContikiMAC](https://drive.google.com/file/d/1DRjdNB97H6NGtvY83zxyvSgVBfsDX99B/view?usp=sharing) and [TSCH](https://drive.google.com/file/d/1NMQGJutBAqL0IUB6WoJ5QQgXBRnFGKYo/view?usp=sharing)!
- Monitor the radio signal for all the channels at the same time during 2 minutes using a single node (maximize your plot figure to see the results better)

---------
---------

# Useful commands

## Connect to the serial port of a node
```
nc m3-<ID> 20000
```

## Aggregate the serial port of all nodes in the experiment in a single terminal
```
serial_aggregator
```

## Submit an experiment with the CLI
```
iotlab-experiment submit -n <EXPERIMENT NAME> -d <DURATION IN MINS> -l <# OF NODES>,archi=m3:at86rf231+site=<SITE>+mobile=0,<FIRMWARE FILE>,<MONITOR PROFILE NAME>
```

## Sniff packets
NOTE: A sniffer profile has to be loaded in this node
```
sniffer_aggregator -l <SITE>,m3,<ID> -o <OUTPUT PCAP FILE>
```
<!-- 
## Compile ContikiOS for M3 open node platform
```
make clean && make TARGET=iotlab-m3
``` -->

## Disable 6LoWPAN protocol in Wireshark
The default network layer in ContikiOS is RIME. This protocol is not supported in Wireshark, and it gets confused with 6LoWPAN. We can remove the network protocol analysis in Wireshark by disabling 6LoWPAN:
- Go to Analyze/Enabled protocols...
- Uncheck 6LoWPAN