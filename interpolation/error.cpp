#include "error.h"

void error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}
