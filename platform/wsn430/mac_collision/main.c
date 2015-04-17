#include "contiki.h"
#include "random.h"
#include "dev/leds.h"
#include <stdio.h>
#include <stdlib.h>
#include "net/rime.h"
#include "energest.h"
#include "dev/serial-line.h"
#include "lib/memb.h"
#include "lib/list.h"

#ifdef IOTLAB_M3
#include "packet.h"
//#include "dev/light-sensor.h"
//#include "dev/pressure-sensor.h"
//#include "pressure_light.h"
#else
//#include "ds1722.h"
//#include "lib/sensors.h"
//#include "temperature.h"
#endif

/*---------------------------------------------------------------------------*/

#define PHY_MAX_TX_LENGTH 16
#define CHANNEL 11
#define MAX_NEIGHBORS 50

char *ptr;
static struct abc_conn abc;
volatile int8_t print_help = 1;
/*This is the structure of broadcast messages. */
struct broadcast_message {
uint8_t seqno;
};

/* This structure holds information about energy consumption*/
struct energy_time {
  long cpu;
  long lpm;
  long transmit;
  long listen;
  long consumption_CPU;
  long consumption_LPM;
  long consumption_TX;
  long consumption_RX;
};

/*This structure holds information about neighbors */
struct neighbor {
  rimeaddr_t addr ;

   /* Each broadcast packet contains a sequence number (seqno). The ->last_seqno field holds the last sequenuce number we saw from this neighbor. */
  uint8_t last_seqno;

   /* The ->avg_gap contains the average seqno gap that we have seen from this neighbor */
   uint32_t avg_seqno_gap;

  struct neighbor *next;
};
struct neighbor *n;

extern process_event_t serial_line_event_message;
static struct energy_time last;
static struct energy_time diff;

static void abc_recv(struct broadcast_conn *c);

/*These hold the broadcast and unicast structures*/

static struct unicast_conn unicast;
/*---------------------------------------------------------------------------*/

PROCESS(broadcast_process, "Broadcast process");
PROCESS(unicast_process, "Unicast process");

AUTOSTART_PROCESSES(&broadcast_process,&unicast_process);
/*---------------------------------------------------------------------------*/
/* Conversion energy-time values on mW values to M3 and WSN430 */

#ifdef IOTLAB_M3
static void energy_consumption_M3(){

	int Vcc = 3;

  diff.consumption_CPU = (diff.cpu /CLOCK_SECOND) * 0.4 * Vcc;
  diff.consumption_LPM = (diff.lpm /CLOCK_SECOND) * 0.000002 * Vcc;
  diff.consumption_TX = (diff.transmit /CLOCK_SECOND) * 14 * Vcc;
  diff.consumption_RX = (diff.listen /CLOCK_SECOND) * 12.3 * Vcc;
}

#else

static void energy_consumption_WSN430 () {

   	int Vcc = 3;

  diff.consumption_CPU = (diff.cpu /CLOCK_SECOND) * 0.000330 * Vcc;
  diff.consumption_LPM = (diff.lpm /CLOCK_SECOND) * 0.00002 * Vcc;
  diff.consumption_TX = (diff.transmit /CLOCK_SECOND) * 17.4 * Vcc;
  diff.consumption_RX = (diff.listen /CLOCK_SECOND) * 18.8 * Vcc;
}

#endif

/*---------------------------------------------------------------------------*/
/*This function is called for every incoming broadcast packet for the source node, it shows the energy values */

static void abc_recv(struct broadcast_conn *c)
{
	struct energy_time *incoming= (struct energy_time *)packetbuf_dataptr();
	printf(" Energy consumption (Time): CPU: %lu LPM: %lu TRANSMIT: %lu LISTEN: %lu \n", incoming->cpu, incoming->lpm,incoming->transmit, incoming->listen);
	printf(" Energy consumption (mW): CPU: %lu LPM: %lu TRANSMIT: %lu LISTEN: %lu \n",incoming->consumption_CPU,incoming->consumption_LPM,incoming->consumption_TX,incoming->consumption_RX);
}

/*---------------------------------------------------------------------------*/
/*This function is called for every incoming broadcast packet */

static void broadcast_recv(struct broadcast_conn *c,const rimeaddr_t * from)
{

 
	
	uint8_t seqno_gap;     
        struct broadcast_message *m;
        
	m = packetbuf_dataptr();
 
	rimeaddr_copy(&n->addr,from);
	
        printf("adresse  %d.%d: ",from->u8[0], from->u8[1]);
        printf("adresse  %d.%d: ",n->addr.u8[0],n->addr.u8[1]);

 
	   printf("adresse  %d.%d: ",n->addr.u8[0],n->addr.u8[1]);
printf(" broadcast message received from %d.%d: '%s'\n",from->u8[0], from->u8[1],(char *)packetbuf_dataptr());

} 
   
static const struct broadcast_callbacks broadcast_callbacks = {broadcast_recv,abc_recv};
static struct broadcast_conn broadcast; 

/*---------------------------------------------------------------------------*/
/*This function is called for every incoming unicast packet */
static void recv_uc(struct unicast_conn *c, const rimeaddr_t *from)
{
   printf(" unicast message received %d.%d: '%s'\n",from->u8[0], from->u8[1], (char *)packetbuf_dataptr());

}
static const struct unicast_callbacks unicast_callbacks = {recv_uc};

/*---------------------------------------------------------------------------*/

/* This function sends a broadcast message */

static void broadcast_message() {

	   int ret, Vcc = 3;
	   static uint8_t seqno;
	   struct broadcast_message msg;
           rimeaddr_t addr;
/*Inizialize leds and  M3 nodes configuration */
       
	    leds_init();

#ifdef IOTLAB_M3

       //    config_light();
         //  config_pressure();
#endif

           /* Energy consumption start */                                                                 
           last.cpu = energest_type_time(ENERGEST_TYPE_CPU);
           last.lpm=energest_type_time(ENERGEST_TYPE_LPM);
           last.transmit = energest_type_time(ENERGEST_TYPE_TRANSMIT);
           last.listen = energest_type_time(ENERGEST_TYPE_LISTEN);
          
	   /* Send a broadcast message */
	   msg.seqno = seqno;


           packetbuf_copyfrom("hello",6);
           ret = broadcast_send(&broadcast);
           seqno++;
         printf("rimeaddr_node_addr = [%u, %u]\n", rimeaddr_node_addr.u8[0],
rimeaddr_node_addr.u8[1]);
           if (ret!=0){
                  printf("broadcast message sent \n");
                  leds_on(LEDS_GREEN);
                        }
           else {
                  printf("broadcast message not sent!\n");
                  leds_on(LEDS_RED);
                        }

           /* Energy consumption diff */
		
           diff.cpu = energest_type_time(ENERGEST_TYPE_CPU) - last.cpu;
           diff.lpm = energest_type_time(ENERGEST_TYPE_LPM) - last.lpm;
           diff.transmit = energest_type_time(ENERGEST_TYPE_TRANSMIT) -last.transmit;
           diff.listen = energest_type_time(ENERGEST_TYPE_LISTEN) - last.listen;


#ifdef IOTLAB_M3

           energy_consumption_M3();

#else
           energy_consumption_WSN430();
#endif
	 
 }

/*---------------------------------------------------------------------------*/
/* This function sends a unicast message to nodes on the list */

static void unicast_message ( ) {
  int val = 0;
        
        int randn,i;

        /* Pick the source addr and send a unicast message to it. */

        printf("sending unicast to %d.%d\n",n->addr.u8[0],n->addr.u8[1]);
        packetbuf_copyfrom("Hi!",3);

        val = unicast_send(&unicast,&n->addr);
        printf("%d.%d:", n->addr.u8[0],n->addr.u8[1]);
	 if (val!=0){
                printf(" unicast message sent \n");
                leds_on(LEDS_GREEN);
        }
        else {
                printf(" unicast message not sent \n");
                leds_on(LEDS_RED);
        }
    
  }


/*---------------------------------------------------------------------------*/
/* This function prints the help to the users*/

static void print_usage()
{
	printf("\n\nContiki program\n");
	printf("Type command\n");
	printf("\th:\tprint this help\n");
	printf("\tb:\tsend a broadcast message\n");

	if (print_help)
	printf("\n Type Enter to stop printing this help\n");

}


/*---------------------------------------------------------------------------*/
/*Broadcast process */

PROCESS_THREAD(broadcast_process, ev, data)
{
  	PROCESS_EXITHANDLER(broadcast_close(&broadcast);)
 
        PROCESS_BEGIN();

	static struct etimer et;
        int ret;
        
	broadcast_open(&broadcast,129, &broadcast_callbacks);
//        print_usage();         
 	      
         /* Send a broadcast message every 2-4 seconds */
        etimer_set(&et, CLOCK_SECOND * 4 + random_rand() % (CLOCK_SECOND * 4));
        
	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
       
  //      while(1){

	/*Check the character on the serial line */
    //    PROCESS_WAIT_EVENT_UNTIL (ev == serial_line_event_message);	
             
      // if (ev ==serial_line_event_message ){   
       
    /*   	printf(" %s\n", (char *)data);        
       	const char *c = (char *)data; 

       	switch(*c){

           case 'b':
                broadcast_message();
                print_help = 0;  
           break;

           case '\n':
                printf("\ncmd > ");
		print_usage();
           break;
        
 	   case 'h':
                print_usage();
                print_help = 1;
           break;
}

	}
}*/
             broadcast_message();	

	PROCESS_END();
}

/*---------------------------------------------------------------------------*/
/* Unicast process */

PROCESS_THREAD(unicast_process,ev,data)    
{

	PROCESS_EXITHANDLER(unicast_close(&unicast);)
	PROCESS_BEGIN();

	unicast_open(&unicast, 146,&unicast_callbacks);
 	static struct etimer et;

	/*Send a unicast message every 8 seconds */

      //  PROCESS_WAIT_EVENT_UNTIL (ev == serial_line_event_message);
        etimer_set(&et, CLOCK_SECOND * 8 + random_rand() % (CLOCK_SECOND * 8));
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
       
  //      while(1){
        
	/*Check the character on the serial line */
//	PROCESS_WAIT_EVENT_UNTIL (ev == serial_line_event_message);
    //    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
      		
	  	unicast_message();
//}
	PROCESS_END();

}
