#pragma once

#include "taskgraph/Task.h"

#include <SM_Vector.h>

namespace taskgraph
{

struct Image;

namespace task
{

class BuildVTex : public Task
{
public:
    BuildVTex()
    {
        m_imports = {
            {{ PT_IMAGE, "in" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/BuildVTex.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // BuildVTex

}
}