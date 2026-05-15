#include <iostream> 
#include <windows.h>
#define a
bool Clock(DWORD ms) {
    Sleep(ms);
    return true;
}

int main() {
    char s = 0;
    while (Clock(70)) std::cout << (int)s++ << std::endl;
}