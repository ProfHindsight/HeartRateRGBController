<<<<<<< HEAD
# HeartRateRGBController
This is a heart rate controller utilizing the STM32F030K6T6

## Installation Instructions
```bash
sudo apt-get install libboost-dev libtool git gcc-arm-none-eabi libnewlib-arm-none-eabi cmake build-essential libusb-1.0
wget -qO - https://download.sublimetext.com/sublimehq-pub.gpg | sudo apt-key add -
echo "deb https://download.sublimetext.com/ apt/stable/" | sudo tee /etc/apt/sources.list.d/sublime-text.list
sudo apt-get update
sudo apt-get install sublime-text
cd ~/Documents
git clone https://github.com/texane/stlink
cd stlink
make release
make debug
cd build/Release;make install DESTDIR=$HOME
cd ../..
cp etc/udev/rules.d /etc/udev/
sudo udevadm control --reload-rules
sudo udevadm trigger
cd ~/Documents/stm32f0-discover-basic-template
chmod +x program-board.sh
```
=======
# HeartRateRGBController
This is a heart rate controller utilizing the STM32F030K6T6

## Installation Instructions
Run the powershell script to start the build container

## Building the binary
Change to the /home/root directory where the Makefile resides  
Run make .

## Deploying the binary
Use a windows tool such as STM32 ST-Link Utility to flash the binary to the target
>>>>>>> 60ff28874df96004a0f3dfdb30da627ef987cf48
