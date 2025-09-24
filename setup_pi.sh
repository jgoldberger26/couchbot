sudo apt-get update

sudo apt-get install autoconf-archive libtool autotools-dev pkg-config gawk

git clone https://github.com/brgl/libgpiod.git lib/libgpiod
sh lib/libgpiod/autogen.sh --enable-tools 
make -C lib/libgpiod/
sudo make install -C lib/libgpiod/


git clone https://github.com/tagciccone/SIO.git lib/SIO