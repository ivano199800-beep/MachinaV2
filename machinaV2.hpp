#include <cstdint>
#include <vector>
#include <map>

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
                std::vector<cmos::SIGNAL> internal_wires;
                std::vector<cmos::SIGNAL*> interface_wires;
                std::vector<cmos::transistor> internal_transistors;
                std::map<idx_t , idx_t> interface_mappings;
            public:
                idx_t addWire() {}
                idx_t addTransistor() {}
                void bindTransistor(idx_t transistor , idx_t internal__wire , cmos::transistor::pin pin) {}
                void mapWire(idx_t internal_wire  , idx_t interface_wire) {}
                void evaluate(unsigned long long flags) {}
        };
    }
}