    #pragma once
    //#define LOG_
    #include <stdint.h>
    #include <iostream>
    #include <vector>
    #include <map>
    #include <any>
    using SIGNAL = unsigned char;
    #define WIP std::cout << "WIP" << std::endl;
    namespace machinaV2 {    
        SIGNAL PMOS(SIGNAL source , SIGNAL gate) {
            SIGNAL drain = (!(gate >> 7)) ? ((source > 1) ?  source : 0) : 0;
            #ifdef LOG_
            std::cout << "P-MOS\n" << 
            "source: " << std::hex << (int)source << '\n' <<
            "control: " << std::hex << (int)gate << '\n' << 
            "drain: " << std::hex << (int)drain << '\n';
            #endif
            return drain;
        }
        SIGNAL NMOS(SIGNAL source , SIGNAL gate) {
            SIGNAL drain = ((gate >> 7)) ? ((source > 1) ?  source : 0) : 0;
            #ifdef LOG_
            std::cout << "N-MOS\n" <<
            "source: " << std::hex << (int)source << '\n' <<
            "control: " << std::hex << (int)gate << '\n' << 
            "drain: " << std::hex << (int)drain << '\n';
            #endif
            return drain;
        }
        void PMOS(SIGNAL source , SIGNAL gate , SIGNAL *drain) {
            *drain = (!(gate >> 7)) ? ((source > 1) ?  source : 0) : 0;
            #ifdef LOG_
            std::cout << "P-MOS\n" << 
            "source: " << std::hex << (int)source << '\n' <<
            "control: " << std::hex << (int)gate << '\n' << 
            "drain: " << std::hex << (int)*drain << '\n';
            #endif
        }
        void NMOS(SIGNAL source , SIGNAL gate , SIGNAL* drain) {
            *drain = ((gate >> 7)) ? ((source > 1) ?  source : 0) : 0;
            #ifdef LOG_
            std::cout << "N-MOS\n" <<
            "source: " << std::hex << (int)source << '\n' <<
            "control: " << std::hex << (int)gate << '\n' << 
            "drain: " << std::hex << (int)*drain << '\n';
            #endif
        }
        enum class cmos_pin : uint8_t {
            drain,
            control,
            source  
        };
        class device {
            using Gate = struct {
            size_t drain, source , gate;
            bool invert;
            };
            std::vector<SIGNAL> internal_wires;
            std::vector<Gate> internal_gates;
            bool commited = false;
            public:
            std::vector<SIGNAL*> interface_wires;
            std::map<size_t , SIGNAL*> wire_mapping;
            void updateInterface(size_t wire_index) {
                if (!wire_mapping.count(wire_index)) return;
                // currently working on this
                *(wire_mapping[wire_index]) = internal_wires[wire_index]; 
            }
            void tick() {
                if (!commited) return;
                WIP
                // temporary behavior
                for (auto& g : internal_gates) {
                    this->updateInterface(g.source);
                    this->updateInterface(g.drain);
                    this->updateInterface(g.gate);
                    if (g.invert) 
                    PMOS(internal_wires[g.source], internal_wires[g.gate], &internal_wires[g.drain]);
                    else 
                    NMOS(internal_wires[g.source], internal_wires[g.gate], &internal_wires[g.drain]);
                }
            }
            void commit() {
                if (commited) return;
                commited = true;
            }
            void map(SIGNAL* interface , size_t internal_index) {
                if (commited) return;
                if (internal_wires.size() < internal_index) return;
                wire_mapping[internal_index] = interface;
            }
            void wire(size_t gate_index , cmos_pin pin , size_t internal_index) {
                WIP
                if (commited) return;
                // TODO LATER
                if (gate_index > internal_gates.size()) return;
                if (internal_index > internal_wires.size()) return;

                internal_gates[gate_index];
            }
            size_t addGate(size_t drain , size_t control , size_t source ,bool isN) {
                if (commited) return 0;
                Gate g;
                g.invert = isN;
                g.drain = drain;
                g.gate = control;
                g.source = source;
                internal_gates.push_back(g);
                return internal_gates.size() - 1;
            }
            virtual void setup(const std::string& format , const std::vector<std::any>& args) = 0;
        };

    }
