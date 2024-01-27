#ifndef OOPPROG1_PROG1_H
#define OOPPROG1_PROG1_H

#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <stdexcept>

namespace Prog1 {
    
    struct Line {
        std::vector<int> elements;
    };

    struct Matrix {
        std::vector<Line> lines;
    };

    Matrix input();
    void output(const char *msg, const Matrix &matrix);
    std::vector<int> result(const Matrix &matrix);
    void vectoroutput(const char *msg, std::vector<int> res);
}

#endif //OOPPROG1_PROG1_H
