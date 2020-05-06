# Select the role of the node passing the ROLE variable to the make command
# Options available: sink, source
# Examples:
# For the sink:
# $ make ROLE=sink
# For the source:
# $ make ROLE=source
# 
# Select the protocol passing the PROTOCOL variable to the make command
# Options available: contikimac, tsch
# Examples
# For ContikiMAC:
# $ make PROTOCOL=contikimac
# For TSCH:
# $ make protocol=tsch
#
# Predefined options:
# make tp-rsf
# compiles everything for the students of the TP

CONTIKI_PROJECT = node
CONTIKI = ../..

all: $(CONTIKI_PROJECT) rename

# Common config (prior to Makefile.include)
CONTIKI_WITH_RIME = 1

# Default arguments
ROLE ?= source
PROTOCOL ?= contikimac
LEADERBOARD_SINK ?= 0

# Sink argument
ARG_ROLE_SINK = sink

# Protocol specific config
PROJECT_CONF=project-conf-$(PROTOCOL).h
ifneq ("$(wildcard $(PROJECT_CONF))","")
	CFLAGS += -DPROJECT_CONF_H=\"$(PROJECT_CONF)\"
endif

ifneq ("$(wildcard $(CONTIKI)/core/net/mac/$(PROTOCOL))","")
	MODULES += core/net/mac/$(PROTOCOL)
endif

ifeq ($(ROLE),$(ARG_ROLE_SINK))
	DEFINES += SINK
endif

ifeq ($(LEADERBOARD_SINK),1)
	DEFINES += LEADERBOARD_SINK
endif

include $(CONTIKI)/Makefile.include

# Handle binary output filename (precondition: Makefile.include)
BINARY_FILENAME_DEFAULT = $(CONTIKI_PROJECT).$(TARGET)
OUTPUT_FILENAME = $(ROLE)-$(PROTOCOL).$(TARGET)

# Rename binary file
rename:
	mv $(BINARY_FILENAME_DEFAULT) $(OUTPUT_FILENAME)
	echo

test: tp-rsf

tp-rsf:
	make clean
	make ROLE=sink PROTOCOL=contikimac
	make clean
	make ROLE=source PROTOCOL=contikimac
	make clean
	make ROLE=sink PROTOCOL=tsch
	make clean
	make ROLE=source PROTOCOL=tsch
	make clean

tsch:
	make clean
	make ROLE=sink PROTOCOL=tsch
	make clean
	make ROLE=source PROTOCOL=tsch
	make clean

tp-sinks:
	make clean
	make ROLE=sink PROTOCOL=contikimac LEADERBOARD_SINK=1
	make clean
	make ROLE=sink PROTOCOL=tsch LEADERBOARD_SINK=1
	make clean
	mv sink-contikimac.iotlab-m3 tp-sink-contikimac.iotlab-m3
	mv sink-tsch.iotlab-m3 tp-sink-tsch.iotlab-m3

tp-instructor: tp-rsf tp-sinks