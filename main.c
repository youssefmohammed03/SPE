#include <stdio.h>
#include "profiler.h"

// Helper to simulate work
void do_work(int ms) {
    #ifdef _WIN32
    Sleep(ms);
    #else
    usleep(ms * 1000);
    #endif
}

void function_C() {
    FUNC_ENTER;
    printf("  Inside Function C (Working...)\n");
    do_work(100); // Sleep 100ms
    FUNC_EXIT;
}

void function_B() {
    FUNC_ENTER;
    printf(" Inside Function B (Calling C)\n");
    do_work(50);
    function_C();
    FUNC_EXIT;
}

void function_A() {
    FUNC_ENTER;
    printf("Inside Function A (Calling B)\n");
    do_work(50);
    function_B();
    FUNC_EXIT;
}

int main() {
    PROFILE_START;
    FUNC_ENTER;

    printf("Program Start...\n");

    function_A();

    function_C();

    printf("Program End.\n");

    FUNC_EXIT;
    PROFILE_END;
    return 0;
}