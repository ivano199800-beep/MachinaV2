#pragma once
#include <set>
#include <map>
#include <vector>
#include <string>
namespace ivn {
    class argument {
        // only for -flag --option value ungrouped
        public:
        std::set<std::string> flags;
        std::map<std::string , std::string> options;
        std::vector<std::string> ungrouped;
        argument(char** argv) {
            while (*argv) {
                char* arg = *argv;
                if (arg[0] == '-' && arg[1] == '-') {
                    if (argv[1]) options[arg + 2] = argv[1]; 
                    else flags.insert(arg + 2);
                    argv++;
                } else if (arg[0] == '-') {
                    flags.insert(arg + 1);
                } else {
                    ungrouped.push_back(arg);
                }
                argv++;
            }
        }
    };
}