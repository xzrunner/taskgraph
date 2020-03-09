#include "taskgraph/task/Mipmap.h"
#include "taskgraph/ParamImpl.h"
#include "taskgraph/TaskHelper.h"

namespace taskgraph
{
namespace task
{

void Mipmap::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    if (m_levels == 0) {
        return;
    }

    auto prev_param = TaskHelper::GetInputParam(*this, 0);
    if (!prev_param) {
        return;
    }

    assert(prev_param->Type() == ParamType::Image);
    auto img = std::static_pointer_cast<ImageParam>(prev_param)->GetImage();
    if (!img) {
        return;
    }

    std::vector<std::shared_ptr<prim::Bitmap<short>>> imgs;

    const int w = img->Width();
    const int h = img->Height();

    const int max = static_cast<int>(std::min(std::log2(w), std::log2(h)));
    const int levels = std::min(max, m_levels);
    imgs.resize(levels);

    const int band = img->Channels();

    std::shared_ptr<prim::Bitmap<short>> prev = img;
    for (int i = 0; i < levels; ++i)
    {
        assert(prev);
        const int prev_w = prev->Width();
        const int prev_h = prev->Height();
        const int curr_w = prev_w % 2 ? (prev_w + 1) / 2 : prev_w / 2;
        const int curr_h = prev_h % 2 ? (prev_h + 1) / 2 : prev_h / 2;

        auto& src = prev->GetValues();
        std::vector<short> dst(curr_w * curr_h * band);
        for (int y = 0; y < curr_h; ++y) {
            for (int x = 0; x < curr_w; ++x) {
                for (int b = 0; b < band; ++b) {
                    dst[y * curr_w + x + b] = src[y * 2 * prev_w + x * 2 + b];
                }
            }
        }

        auto curr = std::make_shared<prim::Bitmap<short>>(curr_w, curr_h, band);
        curr->SetValues(dst);
        imgs[i] = curr;
        prev = curr;
    }

    assert(!imgs.empty());
    m_vals.resize(1);
    m_vals[0] = std::make_shared<ImageArrayParam>(imgs);
}

}
}