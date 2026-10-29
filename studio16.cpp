#include <iostream>
#include <string>

#include "printit.h"

const int SUCCESS = 0;

int main() {
    std::string s("hello");
    const char* cp = "pointer";
    int i = 42;
    int* ip = &i;

    printit(std::cout, s);
    printit(std::cout, "literal");
    printit(std::cout, cp);
    printit(std::cout, i);
    printit(std::cout, ip);

    return SUCCESS;
}
