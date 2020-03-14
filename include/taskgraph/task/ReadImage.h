#pragma once

#include "taskgraph/Task.h"
#include "taskgraph/ParamType.h"

#include <SM_Vector.h>

namespace taskgraph
{
namespace task
{

class ReadImage : public Task
{
public:
    ReadImage()
    {
        m_imports = {
            {{ PT_FILE | PT_BUFFER, "in" }},
        };
        m_exports = {
            {{ PT_IMAGE, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/ReadImage.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // ReadImage

}
}