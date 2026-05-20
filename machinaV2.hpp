#include <cstdint>
#include <vector>
#include <map>
#include <optional>
namespace ivn {
    using idx_t = size_t;
    namespace machinaV2 {
        namespace cmos {
            using SIGNAL = uint8_t;
            constexpr char nmos = 0;
            constexpr char pmos = 1;
            static inline SIGNAL evaluate(char type , SIGNAL source , SIGNAL control) {
                return ((type ^ control) & source);
            }
            using transistor = struct {
                enum class pin : uint8_t {
                    source,
                    control,
                    drain
                };
                idx_t source , control , drain;
                char type;
                bool modified;
            };
        }
        class chip {
            private:
                std::vector<cmos::SIGNAL> internal_wires = {0};
                std::vector<cmos::SIGNAL*> interface_wires = {0};
                std::vector<cmos::transistor> internal_transistors = {{0}};
                std::map<idx_t , idx_t> interface_mappings;
            public:
                idx_t addWire() {
                    internal_wires.push_back(0);
                    return internal_wires.size()- 1;
                }
                idx_t addTransistor(char type) {
                    internal_transistors.push_back((cmos::transistor){.type = type & 1});
                    return internal_transistors.size() - 1;
                }
                void bindTransistor(idx_t transistor , idx_t internal_wire , cmos::transistor::pin pin) {
                    auto & t = internal_transistors[transistor];
                    switch (pin) {
                        case cmos::transistor::pin::control:
                            t.control = internal_wire;
                            break;
                        case cmos::transistor::pin::drain:
                            t.drain = internal_wire;
                            break;
                        case cmos::transistor::pin::source:
                            t.source = internal_wire;
                            break;
                        default:
                            break;
                    }
                    return;
                }
                void mapWire(idx_t internal_wire  , idx_t interface_wire) {
                    interface_mappings[internal_wire] = interface_wire;
                }
                void pull_mapped(idx_t internal_wire) {
                    idx_t mw = interface_mappings[internal_wire];
                    auto m = interface_wires[mw];
                    if (!m) return;
                    internal_wires[internal_wire] = *m;
                }
                void push_mapped(idx_t internal_wire) {
                    idx_t mw = interface_mappings[internal_wire];
                    auto m = interface_wires[mw];
                    if (!m) return;
                    *m = internal_wires[internal_wire];
                }
                void evaluate(unsigned long long flags) {

                }
        };
    }
}