#include "lib/SIO/inputhub.h"
#include "lib/SIO/outputhub.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <fstream>

#include "KRBC-15MOS.h"
#include <yaml-cpp/yaml.h>

int initPins() {
    if (wiringPiSetupPinType(WPI_PIN_BCM) < 0) { 
        // Failed, return an error
        return -1;
    }
    return 0;
}

std::string getEvent() {
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

    return event;
}

std::map<std::string, Motor_Config> getConfigs() {
    YAML::Node n = YAML::LoadFile("config.yaml");

    return n["MotorControllers"].as<std::map<std::string, Motor_Config> >();
}

int main() {
    // Init pin system
    if (initPins() < 0) { 
        // Failed, return an error
        std::cerr << "wiringPi setup failed!" << std::endl;
        return -1;
    }

    // Init Motor controllers
    
    std::map<std::string, Motor_Config> configs = getConfigs();

    KRBC_15MOS left(configs["Left"]);
    KRBC_15MOS right(configs["Right"]);

    // Init I/0
    InputHub ihub;
    OutputHub ohub;

    ihub.makeReadThread(getEvent(), XBOX);

    ohub.addAction(
        action(
            ihub.getConsumable(1, 304),
            [&left] (bool b) {left.reverse(b);}
        )
    );

    std::cout << "Running..." << std::endl;
    
    // Main loop
    while (true) {
        ohub.exec();
    }

    return 0;
}