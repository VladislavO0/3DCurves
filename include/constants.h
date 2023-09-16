/// constants.h - contains symbolic constants

#ifndef CONSTANT_H
#define CONSTANT_H

#include <cstddef>

///namespace for constants
namespace constants
{
    const double PI = 3.14159265;
    const double d = PI / 360; //step for T value
    const double T = 2*PI; // max value t parameter
    const size_t res = static_cast<size_t> (T / d); // for reserve values in vector
}
#endif
