# HeartRateRGBController  
This is a heart rate controller utilizing the STM32F030K6T6    

### Installation Instructions
sudo apt-get install libboost-dev libtool git gcc-arm-none-eabi libnewlib-arm-none-eabi cmake build-essential libusb-1.0   
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
