#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_
/* radio 802.15.4 conf */
#define RF2XX_CHANNEL 11
#define RF2XX_LEDS_ON

#undef NETSTACK_CONF_MAC
#define NETSTACK_CONF_MAC csma_driver

#endif /* PROJECT_CONF_H_ */

