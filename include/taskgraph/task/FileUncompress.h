#pragma once

#include "taskgraph/Task.h"

namespace taskgraph
{
namespace task
{

class FileUncompress : public Task
{
public:
    FileUncompress()
    {
        m_imports = {
            {{ PT_FILE, "in" }},
        };
        m_exports = {
            {{ PT_BUFFER, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    static int Uncompress(unsigned char* dst, size_t* dst_len, const unsigned char* src, 
        size_t* src_len, const unsigned char* props, size_t props_sz);

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/FileUncompress.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // FileUncompress

}
}