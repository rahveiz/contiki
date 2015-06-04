
CONTIKI_PROJECT = mac_collision

ifdef NET_CONF


CFLAGS+=-DPROJECT_CONF_H=\"project-conf-$(NET_CONF).h\"

else

NET_CONF = default_mac

endif


all:  $(CONTIKI_PROJECT)
	mv $(CONTIKI_PROJECT).$(TARGET) $(CONTIKI_PROJECT)_$(NET_CONF).$(TARGET) 

PROJECT_SOURCEFILES +=pressure_light.c

CONTIKI = ../../..
include $(CONTIKI)/Makefile.include
