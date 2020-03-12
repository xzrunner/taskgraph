#pragma once

#include "taskgraph/Task.h"

#include <SM_Vector.h>

namespace taskgraph
{
namespace task
{

class MakeDirectory : public Task
{
public:
    MakeDirectory()
    {
        m_exports = {
            {{ PT_ANY, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/MakeDirectory.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // MakeDirectory

}
}