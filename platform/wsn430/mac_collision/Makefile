CONTIKI_PROJECT = main

ifdef NET_CONF

CFLAGS += "-DNETSTACK_CONF_H=netstack-conf-$(NET_CONF).h"
CFLAGS+=-DPROJECT_CONF_H=\"project-conf-$(NET_CONF).h\"

else

NET_CONF = default_mac

endif

all: clean $(CONTIKI_PROJECT) 
	mv $(CONTIKI_PROJECT).$(TARGET) $(CONTIKI_PROJECT)_$(NET_CONF).$(TARGET)

PROJECT_SOURCEFILES +=temperature.c

CONTIKI = ../../..
include $(CONTIKI)/Makefile.include








