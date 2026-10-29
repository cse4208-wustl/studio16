#ifndef PRINTIT_H
#define PRINTIT_H

#include <ostream>

// Base template: inserts its argument into the stream, followed by a newline.
template <typename T>
void printit(std::ostream& os, const T& t) {
    os << t << std::endl;
}

#endif // PRINTIT_H
