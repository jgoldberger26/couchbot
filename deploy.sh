# To get the compliler on linux: sudo apt-get install g++-arm-linux-gnueabihf
# you can get it on windows too, but idk how. get ready to learn WSL buddy

## TODO: Actually fix this damn script


arm-linux-gnueabihf-g++ main.cpp gpio_bindings.c -o CouchControl.out -lpigpio
# ssh rpirobo@192.168.1.2 "mkdir ~/CouchControl"
scp CouchControl.out rpirobo@192.168.1.2:~/CouchControl/CouchControl.out