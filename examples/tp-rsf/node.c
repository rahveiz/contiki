/*
 * Copyright (c) 2020, University of Strasbourg.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         TP-RSF
 * \author
 *         Sebastian L. Sampayo <sampayo@unistra.fr>
 */

#include "contiki.h"
#include "contiki-net.h"
#include "net/rime/rime.h"
#include <stdio.h>
#ifdef WITH_TSCH
#include "net/netstack.h"
#include "net/mac/tsch/tsch.h"
#endif

/* Setup */
#define SINK_ID 1
#define PACKET_PERIOD (10 * CLOCK_SECOND)

/* Logging */
#ifdef LEADERBOARD_SINK
#define PRINTTEAM(...) printf(__VA_ARGS__)
#define PRINTF(...) 
#else
#define PRINTTEAM(...)
#define PRINTF(...) printf(__VA_ARGS__)
#endif

/*---------------------------------------------------------------------------*/
static void sent_uc(struct unicast_conn *c, int status, int num_tx);
static void recv_uc(struct unicast_conn *c, const linkaddr_t *from);
/*---------------------------------------------------------------------------*/
PROCESS(example_unicast_process, "TP-RSF");
AUTOSTART_PROCESSES(&example_unicast_process);
/*---------------------------------------------------------------------------*/
static const struct unicast_callbacks unicast_callbacks = {recv_uc, sent_uc};
static struct unicast_conn uc;
/*---------------------------------------------------------------------------*/
/* Callback for packet reception */
static void
recv_uc(struct unicast_conn *c, const linkaddr_t *from)
{
  int msg_len = packetbuf_datalen();
  char *msg = (char *)packetbuf_dataptr();
  msg[msg_len] = '\0'; /* fix for tsch */

  PRINTF("unicast message received from %d.%d (%02x:%02x): '%s'\n",
	 from->u8[0], from->u8[1], from->u8[0], from->u8[1], msg);

  PRINTTEAM("%s,%02x:%02x\n", msg, from->u8[0], from->u8[1]);
}
/*---------------------------------------------------------------------------*/
/* Callback for packet transmission */
static void
sent_uc(struct unicast_conn *c, int status, int num_tx)
{
  const linkaddr_t *dest = packetbuf_addr(PACKETBUF_ADDR_RECEIVER);
  if(linkaddr_cmp(dest, &linkaddr_null)) {
    return;
  }

  int channel;
  NETSTACK_RADIO.get_value(RADIO_PARAM_CHANNEL, &channel);

  PRINTF("unicast message sent to %d.%d (%02x:%02x): status %d num_tx %d, on ch %d\n",
    dest->u8[0], dest->u8[1], dest->u8[0], dest->u8[1], 
    status, num_tx, channel);
}
/*---------------------------------------------------------------------------*/
/* Helper function: Convert from uint16_t to linkaddr_t */
static void
uint16tolinkaddr(linkaddr_t *dest, const uint16_t src)
{
  dest->u8[0] = 0xff & (src >> 8);
  dest->u8[1] = 0xff & (src);
}
/*---------------------------------------------------------------------------*/
/* Main process. 
 * Setup sink and tsch and send a packet periodically 
 * (depending on the project configuration) */
PROCESS_THREAD(example_unicast_process, ev, data)
{
  PROCESS_EXITHANDLER(unicast_close(&uc);)
    
  PROCESS_BEGIN();
  linkaddr_t sink_addr;
  uint16tolinkaddr(&sink_addr, SINK_ID);

#ifdef SINK
  /* Set static rime address */
  linkaddr_copy(&linkaddr_node_addr, &sink_addr);
  PRINTF("I'm the SINK!\n");
#endif

#ifdef WITH_TSCH
  /* Enable/disable TSCH coordinator */
  int is_coordinator = linkaddr_cmp(&sink_addr, &linkaddr_node_addr);
  tsch_set_coordinator(is_coordinator);
  NETSTACK_MAC.on();
#endif

  /* Open unicast rime port and set callbacks */
  unicast_open(&uc, 100, &unicast_callbacks);

  PRINTF("Network stack (LLSEC, MAC, RDC): %s, %s, %s\n",
        NETSTACK_LLSEC.name, NETSTACK_MAC.name, NETSTACK_RDC.name
  );

  /* Main loop */
  while(1) {
    static struct etimer et;
    etimer_set(&et, PACKET_PERIOD);
    
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

#ifndef SINK /* I'm the Source */
    linkaddr_t dest_addr;
    uint16tolinkaddr(&dest_addr, SINK_ID);
    packetbuf_copyfrom("Hello", 5);
    unicast_send(&uc, &dest_addr);
#endif
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
