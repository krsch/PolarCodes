#pragma once
#include <cfenv>

struct FEExcept {
    fenv_t state;
    FEExcept(int newstate = FE_INVALID) {
#ifndef _WIN32
        feholdexcept(&state);
        feenableexcept(newstate);
#endif
    }
    ~FEExcept() {
        fesetenv(&state);
    }
};
