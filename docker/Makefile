# This Makefile helps extract the docker syntax from the user into a Makefile interface
# Reference: https://nasa.github.io/trick/howto_guides/How-To-Containerize-Trick-with-Docker.html

HERE:= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
TOP := $(abspath $(HERE)/..)/
UNAME := $(shell uname)
MYUID := $(shell id -u ${USER})
MYGID := $(shell id -g ${USER})
MYNAME := $(shell whoami)
LMYNAME := $(shell echo $(MYNAME) | tr A-Z a-z)

.PHONY: build build build-trick build-trick-base run run-trick

build-trick-base:
	docker build -t trick-$(LMYNAME):base -f Dockerfile .

build build-trick: build-trick-base
	docker build --build-arg myuser=$(LMYNAME) \
	--build-arg myuid=$(MYUID) --build-arg mygid=$(MYGID) \
	-t trick-$(LMYNAME)-img -f Dockerfile.trick_user .

# TODO: 
# els ifeq ($(OS),Windows_NT)
HOST_IPS := $(shell ipconfig | grep "IPv4" | cut -d ':' -f 2 | cut -d ' ' -f 2 )
HOST_IP := $(shell echo ${HOST_IPS} | cut -d ' ' -f 1)
run run-trick: build-trick
	docker run --privileged \
	--interactive \
	--tty \
	-e DISPLAY="$(HOST_IP):0.0" \
	-dit \
	--name trick-$(LMYNAME)-container \
	trick-$(LMYNAME)-img

start:
	docker start trick-$(LMYNAME)-container && \
	docker exec --privileged -it -e DISPLAY="$(HOST_IP):0.0" trick-$(LMYNAME)-container //bin/bash -c "su $(LMYNAME)"

hello:
	echo "Printed This"
