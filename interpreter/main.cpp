#include "../machinaV2.hpp"
#include "CLIparser.hpp"
#include <iostream>
#include <print>
#include <string>
#include <map>
#include <sstream>
using idx_t = unsigned long long;



// TODO complete teardown and refactor of this class
class interpreter {
    public:
        std::vector<idx_t>  index_stack;
        std::map<std::string,idx_t> string_ids;
        ivn::machinaV2::chip chip;
	
	bool terminateIFin(const std::string_view format , char c) {
		for (char ch : format) 
		if (ch == c) return false;
		return true;
	}
	void ParseLine(const std::string& line) {
		std::vector<std::string> tokens;
		for (char ch : line) 
		if (ch == ';') return;
		for (idx_t i = 0 ; i < line.size() ; i++) {
			if (!terminateIFin("\n\t " , line[i])) continue;
			if (!terminateIFin("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_" , std::toupper(line[i]))) {
				tokens.push_back("");
				while (
					!terminateIFin("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_" , std::toupper(line[i])) &&
					i < line.size()
				) {
					std::string& tk = tokens.back();
					tk.push_back(std::toupper(line[i]));
					i++;
				}
			}

		}
		if (tokens[0] == "NEW") {
			if (tokens[1] == "WIRE") {
				
			} else if (tokens[1] == "PMOS") {

			} else if (tokens[1] == "NMOS") {

			} else {
				throw std::runtime_error("BAD SOURCE CODE");
				return;
			}
		} else if (tokens[0] == "POP") {
					
		} else if (tokens[0] == "PUSH") {
	
		} else if (tokens[0] == "LINK") {

		} else if (tokens[0] == "MAP") {

		} else if (tokens[0] == "LOCK") {

		} else {
			chip.commit();
		}
	}
};
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
	
