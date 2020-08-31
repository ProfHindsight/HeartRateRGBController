FROM ubuntu

ARG DEBIAN_FRONTEND=noninteractive

# Setup environment
RUN apt-get update
RUN apt-get install -y libboost-dev
RUN apt-get install -y libtool
RUN apt-get install -y git
RUN apt-get install -y gcc-arm-none-eabi
RUN apt-get install -y libnewlib-arm-none-eabi
RUN apt-get install -y cmake
RUN apt-get install -y build-essential
RUN apt-get install -y libusb-1.0
RUN apt-get install -y udev

#RUN /user/bin/bash

# Start bash when entering the container.
#ENTRYPOINT [ "bash" ]
