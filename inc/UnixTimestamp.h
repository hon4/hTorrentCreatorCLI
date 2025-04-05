#include <iostream>
#include <ctime>

int GetUnixTimestamp() {
    return static_cast<int>(std::time(NULL));
}