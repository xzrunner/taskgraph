#pragma once

#include "taskgraph/Task.h"

namespace taskgraph
{
namespace task
{

class FilePattern : public Task
{
public:
    FilePattern()
    {
        m_exports = {
            {{ PT_FILE, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/FilePattern.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // FilePattern

}
}