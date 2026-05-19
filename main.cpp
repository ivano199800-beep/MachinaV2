#include <cstdlib>
#include <iostream>
#include "machinaV2.hpp"
#include <windows.h>
#include "interpreter/CLIparser.hpp"
bool Tick(DWORD tps) {
    Sleep(1000 / tps);
    return true;
}


int main(int argument_count , char** argument_vector) {
    ivn::argument arg(argument_vector + 1);
    std::cout << "flags\n";
    for (auto& flag : arg.flags) {
        std::cout << '\t' << flag << '\n';
    }
    std::cout << "options" << '\n';
    for (auto& pair : arg.options) {
        std::cout << '\t' << pair.first << " -> " << pair.second << '\n';
    }
    std::cout << "ungrouped" << '\n';
    for (auto& element : arg.positional) {
        std::cout << '\t' << element << "\n";
    }
    while (Tick(std::rand() % 145)) std::cout << "tick\n";
    return 0;
}