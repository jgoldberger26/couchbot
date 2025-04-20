#include "lib/SIO/inputhub.h"
#include "lib/SIO/outputhub.h"

#include "gpio_bindings.h"

void setRevLeft(bool r) {
    std::cout<< "FIRING " << r << std::endl;
    setReverse(r, LEFT);
}

int main() {
    init_pins();

    InputHub ihub;
    OutputHub ohub;

    ihub.makeReadThread("event2", XBOX);

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