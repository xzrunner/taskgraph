#pragma once

#include "taskgraph/Task.h"

#include <SM_Vector.h>

namespace taskgraph
{
namespace task
{

class Group : public Task
{
public:
    enum class Type
    {
        Parallel,
        Sequence,
    };

public:
    Group()
    {
        m_imports = {
            {{ PT_ANY, "in0" }},
            {{ PT_ANY, "in1" }},
            {{ PT_ANY, "in2" }},
        };
        m_exports = {
            {{ PT_ANY, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/Group.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Group

}
}