#include "../machinaV2.hpp"
#include "CLIparser.hpp"
#include <iostream>
#include <print>
int main(int c, char** argv) {
    ivn::argument arg(argv + 1);
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
    //std::println("test");
    //use arg
}
	