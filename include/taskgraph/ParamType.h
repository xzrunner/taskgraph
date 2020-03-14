#pragma once

namespace taskgraph
{

enum ParamType
{
    PT_ANY = 0,

    PT_FILE        = 0x0001,
    PT_BUFFER      = 0x0002,

    PT_IMAGE       = 0x0010,
    PT_IMAGE_ARRAY = 0x0020,
};

}