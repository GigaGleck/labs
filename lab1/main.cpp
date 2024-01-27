#include <iostream>
#include <vector>
#include "Prog1.h"
#include "Prog1.cpp"

using namespace Prog1;

int main() {
    using namespace Prog1;
    try {
        Matrix matrix = input();
        std::vector<int> Result = result(matrix);
        output("Entered matrix", matrix);
        vectoroutput("Received vector", Result);
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}