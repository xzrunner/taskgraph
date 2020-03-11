#pragma once

namespace taskgraph
{

enum ParamType
{
    Any = 0,

    File       = 0x0001,
    Image      = 0x0002,
    ImageArray = 0x0004,
};

}