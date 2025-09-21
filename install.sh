sudo apt-get update
sudo apt install gcc-aarch64-linux-gnu
sudo apt install g++-aarch64-linux-gnu

git clone https://github.com/brgl/libgpiod.git lib/libgpiod
sh lib/libgpiod/autogen.sh CC=aarch64-linux-gnu-gcc --enable-tools --host=aarch64-linux-gnu

git clone https://github.com/tagciccone/SIO.git lib/SIO