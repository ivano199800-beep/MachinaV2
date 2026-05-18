#include <iostream>
#include "machinaV2.hpp"
#include <windows.h>

bool Tick(DWORD tps) {
    Sleep(1000 / tps);
    return true;
}

struct GraphDevice : ivn::machinaV2::device {
    GraphDevice(SIGNAL* inputA, SIGNAL* inputB, SIGNAL* output) {
        auto wa = addWire();
        auto wb = addWire();
        auto wout = addWire();
        if (!wa || !wb || !wout) return;

        map(inputA, *wa);
        map(inputB, *wb);
        map(output, *wout);

        addGate(*wout, *wb, *wa, false); // NMOS pass when gate is high
        commit();
    }

    void setup(const std::string& format, const std::vector<std::any>& args) override {
        (void)format;
        (void)args;
    }
};

int main() {
    SIGNAL inputA = 0;
    SIGNAL inputB = 0;
    SIGNAL output = 0;

    GraphDevice device(&inputA, &inputB, &output);

    int step = 0;
    while (Tick(1)) {
        inputA = (step % 2 == 0) ? 0xFF : 0x00;
        inputB = 0x80; // gate high

        device.tick();

        std::cout << "step=" << step
                  << " A=" << (inputA ? 1 : 0)
                  << " B=" << (inputB ? 1 : 0)
                  << " out=" << (output ? 1 : 0)
                  << std::endl;
        ++step;
    }

}