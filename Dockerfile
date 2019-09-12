FROM ubuntu

# Setup environment
RUN apt-get update
RUN apt-get install -y \
    libboost-dev \
    libtool \
    git \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    cmake \
    build-essential \
    libusb-1.0 \
    udev

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
RUN ./etc/udev/rules.d /etc/udev/ \
    && udevadm control --reload-rules \
    && udevadm trigger

# Start bash when entering the container.
ENTRYPOINT [ "bash" ]
