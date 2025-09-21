#include "lib/SIO/inputhub.h"
#include "lib/SIO/outputhub.h"

// #include "gpio_bindings.h"

#include <fstream>

void setRevLeft(bool r) {
    std::cout<< "FIRING " << r << std::endl;
    // setReverse(r, LEFT);
}

int main() {
    // init_pins();

    gpiod_api_version();
    gpiod_chip_open("gpiochip0");

    InputHub ihub;
    OutputHub ohub;

    std::ifstream f("/proc/bus/input/devices");

    std::string line;
    bool fi = false;
    std::string event;
    while (std::getline(f, line)) {
        if (!fi && line.find("Xbox") != std::string::npos) {
            fi = true;
        } else if (fi && line.find("Handlers") != std::string::npos) {
            auto r = line.find("event");
            event = line.substr(r, 6);
            break;
        }
    } 

    f.close();

    ihub.makeReadThread(event, XBOX);

    ohub.addAction(
        action(
            ihub.getConsumable(1, 304),
            setRevLeft
        )
    );

    std::cout << "Running..." << std::endl;
    
    while (true) {
        ohub.exec();
    }

    return 0;
}