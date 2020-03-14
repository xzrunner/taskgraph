#pragma once

#include "taskgraph/Task.h"

namespace taskgraph
{
namespace task
{

class FileCompress : public Task
{
public:
    FileCompress()
    {
        m_imports = {
            {{ PT_FILE, "in" }},
        };
        m_exports = {
            {{ PT_FILE, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    static void Compress(char** dst, size_t* dst_len, const char* src, size_t src_len);

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/FileCompress.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // FileCompress

}
}