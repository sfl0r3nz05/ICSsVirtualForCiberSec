#set +x

# default path to be used in connection profile files
ABSPATH?=$(shell dirname $(shell dirname $(shell dirname ${PWD})))

WHICHOS := $(shell uname)

start:
	./scripts/start-icsnetwork.sh

stop:
	./scripts/stop-icsnetwork.sh

destroy:
	./scripts/destroy-icsnetwork.sh

ifeq ($(WHICHOS),Darwin)
	rm *-e
endif
	export ABSPATH=${ABSPATH}