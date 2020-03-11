#pragma once

#include "taskgraph/Task.h"

#include <SM_Vector.h>
#include <primitive/Bitmap.h>

namespace taskgraph
{
namespace task
{

class CropImage : public Task
{
public:
    CropImage()
    {
        m_imports = {
            {{ PT_IMAGE | PT_IMAGE_ARRAY, "in" }},
        };
        m_exports = {
            {{ PT_IMAGE_ARRAY, "out" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    static std::shared_ptr<prim::Bitmap<short>>
        Cropping(const prim::Bitmap<short>& img, size_t x, size_t y , size_t w, size_t h);

    RTTR_ENABLE(Task)

#define PARM_FILEPATH "taskgraph/task/CropImage.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // CropImage

}
}