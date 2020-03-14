#pragma once

#include "taskgraph/Task.h"

#include <SM_Vector.h>

namespace taskgraph
{

struct Image;

namespace task
{

class SplitImage : public Task
{
public:
    SplitImage()
    {
        m_imports = {
            {{ PT_IMAGE, "in" }},
        };
        m_exports = {
            {{ PT_IMAGE_ARRAY, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    static void Split(std::vector<std::shared_ptr<Image>>& dst,
        const Image& src, size_t tile_w, size_t tile_h, bool trim);

private:
    void Split(std::vector<std::shared_ptr<Image>>& dst,
        const Image& src) const;

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/SplitImage.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // SplitImage

}
}