#pragma once

#include "taskgraph/Task.h"

#include <SM_Vector.h>
#include <primitive/Bitmap.h>

namespace taskgraph
{
namespace task
{

class SplitImage : public Task
{
public:
    SplitImage()
    {
        m_imports = {
            {{ ParamType::Image, "in" }},
        };
        m_exports = {
            {{ ParamType::ImageArray, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

private:
    void Split(std::vector<std::shared_ptr<prim::Bitmap<short>>>& dst,
        const prim::Bitmap<short>& src) const;

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/SplitImage.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // SplitImage

}
}