#include "inputhub.h"
#include "outputhub.h"
int main() {
    InputHub ihub;
    OutputHub ohub;

    // TODO read thread

    // TODO add actions

    std::cout << "Running..." << std::endl;
    
    while (true) {
        ohub.exec();
    }

    return 0;
}