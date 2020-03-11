#pragma once

#include "taskgraph/Task.h"
#include "taskgraph/ParamType.h"

#include <SM_Vector.h>

namespace taskgraph
{
namespace task
{

class WriteImage : public Task
{
public:
    enum class Type
    {
        PNG,
        HGT,
    };

public:
    WriteImage()
    {
        m_imports = {
            {{ PT_FILE, "in" }},
        };
        m_exports = {
            {{ PT_IMAGE, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/WriteImage.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // WriteImage

}
}