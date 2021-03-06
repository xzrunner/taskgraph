#pragma once

#include "taskgraph/Task.h"

#include <SM_Vector.h>

namespace taskgraph
{

struct Image;

namespace task
{

class Mipmap : public Task
{
public:
    Mipmap()
    {
        m_imports = {
            {{ PT_IMAGE, "in" }},
        };
        m_exports = {
            {{ PT_IMAGE_ARRAY, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    static void Build(std::vector<std::shared_ptr<Image>>& dst,
        const std::shared_ptr<Image>& src, size_t levels);

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/Mipmap.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Mipmap

}
}