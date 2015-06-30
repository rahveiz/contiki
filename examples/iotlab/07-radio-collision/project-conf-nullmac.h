#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_
/* radio 802.15.4 conf */
#define RF2XX_CHANNEL 11
#define RF2XX_LEDS_ON
#define RF2XX_TX_POWER PHY_POWER_3dBm // power max on M3 nodes

#undef NETSTACK_CONF_MAC
#define NETSTACK_CONF_MAC nullmac_driver

#undef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC nullrdc_driver

#endif /* PROJECT_CONF_H_ */
