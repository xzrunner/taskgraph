#pragma once

#include "taskgraph/Task.h"

#include <SM_Vector.h>

namespace taskgraph
{
namespace task
{

class FileRemove : public Task
{
public:
    FileRemove()
    {
        m_imports = {
            {{ PT_FILE, "in" }},
        };
        m_exports = {
            {{ PT_ANY, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/FileRemove.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // FileRemove

}
}