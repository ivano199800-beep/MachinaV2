    #pragma once
    #include <iostream>
    #include <vector>
    using SIGNAL = unsigned char;

    namespace machinaV2 {    
        SIGNAL PMOS(SIGNAL source , SIGNAL gate) {
            SIGNAL drain = (!(gate >> 7)) ? ((source > 1) ?  source - 1 : 0) : 0;
            #ifdef LOG_
            std::cout << "P-MOS\n" << 
            "source: " << std::hex << (int)source << '\n' <<
            "control: " << std::hex << (int)gate << '\n' << 
            "drain: " << std::hex << (int)drain << '\n';
            #endif
            return drain;
        }
        SIGNAL NMOS(SIGNAL source , SIGNAL gate) {
            SIGNAL drain = ((gate >> 7)) ? ((source > 1) ?  source - 1 : 0) : 0;
            #ifdef LOG_
            std::cout << "N-MOS\n" <<
            "source: " << std::hex << (int)source << '\n' <<
            "control: " << std::hex << (int)gate << '\n' << 
            "drain: " << std::hex << (int)drain << '\n';
            #endif
            return drain;
        }
        void PMOS(SIGNAL source , SIGNAL gate , SIGNAL *drain) {
            *drain = (!(gate >> 7)) ? ((source > 1) ?  source - 1 : 0) : 0;
            #ifdef LOG_
            std::cout << "P-MOS\n" << 
            "source: " << std::hex << (int)source << '\n' <<
            "control: " << std::hex << (int)gate << '\n' << 
            "drain: " << std::hex << (int)drain << '\n';
            #endif
        }
        void NMOS(SIGNAL source , SIGNAL gate , SIGNAL* drain) {
            *drain = ((gate >> 7)) ? ((source > 1) ?  source - 1 : 0) : 0;
            #ifdef LOG_
            std::cout << "N-MOS\n" <<
            "source: " << std::hex << (int)source << '\n' <<
            "control: " << std::hex << (int)gate << '\n' << 
            "drain: " << std::hex << (int)drain << '\n';
            #endif
        }
        using CMOS = struct {
            SIGNAL* drain;
            SIGNAL* source;
            SIGNAL* gate;
            bool invert;
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
        void tick() {
            if (!commited) return;
            for (auto& g : internal_gates) {
                // Access internal_wires by index
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
            void wire(size_t gate_index , SIGNAL* drain , SIGNAL* gate , SIGNAL* source) {
                if (commited) return;
                // TODO add later
            }

        };

    }