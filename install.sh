# TODO yeah let's just learn make lol
sudo apt-get update
sudo apt-get install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu

#sudo apt-get install autoconf-archive libtool autotools-dev pkg-config gawk

#git clone https://github.com/brgl/libgpiod.git lib/libgpiod
#sh lib/libgpiod/autogen.sh CC=aarch64-linux-gnu-gcc --enable-tools --host=aarch64-linux-gnu
#make -C lib/libgpiod/
#sudo make install -C lib/libgpiod/

git clone https://github.com/WiringPi/WiringPi.git lib/wiringpi
cd lib/wiringpi || exit
./build

cd ../..

git clone https://github.com/tagciccone/SIO.git lib/SIO