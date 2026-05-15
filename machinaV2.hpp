    #pragma once
    //#define LOG_
    #include <stdint.h>
    #include <iostream>
    #include <vector>
    #include <map>
    #include <any>
    using SIGNAL = unsigned char;

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
            *drain = (!(gate >> 7)) ? ((source > 1) ?  source - 1 : 0) : 0;
            #ifdef LOG_
            std::cout << "P-MOS\n" << 
            "source: " << std::hex << (int)source << '\n' <<
            "control: " << std::hex << (int)gate << '\n' << 
            "drain: " << std::hex << (int)*drain << '\n';
            #endif
        }
        void NMOS(SIGNAL source , SIGNAL gate , SIGNAL* drain) {
            *drain = ((gate >> 7)) ? ((source > 1) ?  source - 1 : 0) : 0;
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
            void updateInterface() {

            }
            void tick() {
                if (!commited) return;
                // WIP this is temporary
                for (auto& g : internal_gates) {
                    this->updateInterface();
                    if (g.invert) PMOS(internal_wires[g.source], internal_wires[g.gate], &internal_wires[g.drain]);
                    else NMOS(internal_wires[g.source], internal_wires[g.gate], &internal_wires[g.drain]);
                }
            }
            void commit() {
                if (commited) return;
                commited = true;
            }
            void map(SIGNAL* interface , size_t internal_index) {
                if (commited) return;
                // now working on this
            }
            void wire(size_t gate_index , cmos_pin pin , size_t internal_index) {
                if (commited) return;
                // TODO LATER
            }
            virtual void setup(const std::string& format , const std::vector<std::any>& args) = 0;
        };

    }
