#include <iostream>
#include <vector>
#include "Signal.h"
#include "Signal.cpp"

using namespace Prog2;

int main() {
    using namespace Prog2;
    try {
        std::cout << "Enter status and duration" << std::endl;
        int a = getNum<int>(0, 1);
        int b = getNum<int>(0);
        Segment c(a , b);
        c.Format();
        std::vector<int> e;
        std::string d = getBinline();
        std::cout << d << std::endl;
    } catch (const std::exception& e) {
        return 1;
    }
    return 0;
}