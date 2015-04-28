#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_
/* radio 802.15.4 conf */
#define RF2XX_CHANNEL 11
#define RF2XX_LEDS_ON
#define RF2XX_TX_POWER PHY_POWER_5dBm // power max.
/*
* Channels: default=11, max=26, min=11.
* TX power: default=0dBm, max=5dBm, min=m30dBm. (see openlab/net/phy.h)
*/

#undef NETSTACK_CONF_MAC
#define NETSTACK_CONF_MAC csma_driver

#undef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC nullrdc_driver

#endif /* PROJECT_CONF_H_ */
