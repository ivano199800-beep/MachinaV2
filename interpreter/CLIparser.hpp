    #pragma once
    #include <set>
    #include <map>
    #include <vector>
    #include <string>
    namespace ivn {
        class argument {
            // only for -flag --option value positional
            // --option -flag is not going to be handled
            public:
            std::set<std::string> flags;
            std::map<std::string , std::string> options;
            std::vector<std::string> positional;
            argument(char** argv) {
                while (*argv) {
                    char* arg = *argv;
                    if (arg[0] == '-' && arg[1] == '-') {
                        if (argv[1]) options[arg + 2] = argv[1]; 
                        else return; // flags.insert(arg + 2);
                        argv++;
                    } else if (arg[0] == '-') {
                        flags.insert(arg + 1);
                    } else {
                        positional.push_back(arg);
                    }
                    argv++;
                }
            }
            bool flagExists(const std::string& flag) {
                
                return false;
            }
            std::optional<std::string> checkOption(const std::string& option) {
                return std::nullopt;
            }
            std::optional<std::string> getPositional(size_t index) {
                return std::nullopt;
            }
        };
    }