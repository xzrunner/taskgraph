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

    assert(prev_param->Type() == PT_IMAGE);
    auto img = std::static_pointer_cast<ImageParam>(prev_param)->GetImage();
    if (!img) {
        return;
    }

    const int w = img->bmp.Width();
    const int h = img->bmp.Height();

    const size_t max = static_cast<size_t>(std::min(std::log2(w), std::log2(h)));
    size_t levels = std::min(max, static_cast<size_t>(m_levels));
    if (m_min_size != 0) {
        levels = std::min(levels, static_cast<size_t>(std::log2(std::min(w, h) / m_min_size)));
    }

    std::vector<std::shared_ptr<Image>> imgs;
    Build(imgs, img, levels);

    assert(!imgs.empty());
    m_vals.resize(1);
    m_vals[0] = std::make_shared<ImageArrayParam>(imgs);
}

void Mipmap::Build(std::vector<std::shared_ptr<Image>>& dst,
                   const std::shared_ptr<Image>& src, size_t levels)
{
    const int w = src->bmp.Width();
    const int h = src->bmp.Height();
    const int channels = src->bmp.Channels();

    dst.resize(levels + 1);
    //dst[0] = std::make_shared<Image>(w, h, channels);;
    //if (dst[0]->bmp.GetPixels()) {
    //    memcpy(dst[0]->bmp.GetPixels(), src->bmp.GetPixels(), w * h * channels * sizeof(src->bmp.GetPixels()[0]));
    //}
    dst[0] = src;   // fixme

    std::shared_ptr<Image> prev = src;
    for (size_t i = 0; i < levels; ++i)
    {
        assert(prev);
        const int prev_w = prev->bmp.Width();
        const int prev_h = prev->bmp.Height();
        const int curr_w = prev_w % 2 ? (prev_w + 1) / 2 : prev_w / 2;
        const int curr_h = prev_h % 2 ? (prev_h + 1) / 2 : prev_h / 2;

        auto src_p = prev->bmp.GetPixels();
        auto curr = std::make_shared<Image>(curr_w, curr_h, channels);
        auto dst_p = curr->bmp.GetPixels();

        for (int y = 0; y < curr_h; ++y) {
            for (int x = 0; x < curr_w; ++x) {
                for (int c = 0; c < channels; ++c) {
                    dst_p[(y * curr_w + x) * channels + c] =
                        src_p[(y * 2 * prev_w + x * 2) * channels + c];
                }
            }
        }

        dst[i + 1] = curr;
        prev = curr;
    }
}

}
}