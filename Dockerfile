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


# Copy the heartrate repo files into the container.
COPY . /app
WORKDIR /app

# TODO: Setup USB mount so the board can be flashed.

# Get build tools.
RUN git clone https://github.com/texane/stlink \
    && cd stlink \
    && make release \
    && make debug \
    && cd build/Release \
    && make install DESTDIR=$HOME \
    && cd ../../

# Do the rule stuff.
#RUN cp etc/udev/rules.d /etc/udev/ \
#    && udevadm control --reload-rules \
#    && udevadm trigger

#RUN /user/bin/bash

# Start bash when entering the container.
#ENTRYPOINT [ "bash" ]
