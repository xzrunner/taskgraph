#pragma once

#include "taskgraph/ParamType.h"

namespace taskgraph
{

class Param
{
public:
    virtual ParamType Type() const = 0;

}; // Param

}