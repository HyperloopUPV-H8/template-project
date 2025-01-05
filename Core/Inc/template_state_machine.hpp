#pragma once
#include "ST-LIB.hpp"
using namespace std::chrono_literals;

class GeneratedStateMachine{

    public:
    %FUNCTION_HEADERS%
    %STATE_DEFINITION%
    %TRANSITION_DEFINITION%
    %ACTION_DEFINITION%
    
};

