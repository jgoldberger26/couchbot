sudo apt-get update
sudo apt install -y build-essential gcc-arm-linux-gnueabihf
sudo apt install -y build-essential g++-arm-linux-gnueabihf

# git clone https://github.com/joan2937/pigpio.git lib/pigpio
git clone https://github.com/brgl/libgpiod.git lib/libgpiod

# make CROSS_PREFIX=arm-linux-gnueabihf- -C lib/pigpio
# sudo make CROSS_PREFIX=arm-linux-gnueabihf- install -C lib/pigpio

git clone https://github.com/tagciccone/SIO.git lib/SIO