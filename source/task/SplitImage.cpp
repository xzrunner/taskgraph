#include "taskgraph/task/SplitImage.h"
#include "taskgraph/task/CropImage.h"
#include "taskgraph/ParamImpl.h"
#include "taskgraph/TaskHelper.h"

namespace taskgraph
{
namespace task
{

void SplitImage::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    auto prev_param = TaskHelper::GetInputParam(*this, 0);
    if (!prev_param) {
        return;
    }

    std::vector<std::shared_ptr<Image>> dst;

    auto type = prev_param->Type();
    switch (type)
    {
    case PT_IMAGE:
    {
        auto img = std::static_pointer_cast<ImageParam>(prev_param)->GetImage();
        if (img) {
            Split(dst, *img);
        }
    }
        break;
    case PT_IMAGE_ARRAY:
    {
        auto& imgs = std::static_pointer_cast<ImageArrayParam>(prev_param)->GetAllImages();
        for (auto& img : imgs) {
            Split(dst, *img);
        }
    }
        break;
    }

    if (!dst.empty())
    {
        m_vals.resize(1);
        m_vals[0] = std::make_shared<ImageArrayParam>(dst);
    }
}

void SplitImage::Split(std::vector<std::shared_ptr<Image>>& dst,
                       const Image& src) const
{
    size_t w = src.bmp.Width();
    size_t h = src.bmp.Height();
    if (w == 0 || h == 0) {
        return;
    }

    size_t sw = 0, sh = 0;
    if (m_tile_num_x > 0 && m_tile_num_y > 0)
    {
        sw = static_cast<size_t>(std::ceil(static_cast<float>(w) / m_tile_num_x));
        sh = static_cast<size_t>(std::ceil(static_cast<float>(h) / m_tile_num_y));
    }
    else if (m_tile_w > 0 && m_tile_h > 0)
    {
        sw = m_tile_w;
        sh = m_tile_h;
    }

    if (sw == 0 || sh == 0) {
        return;
    }

    for (size_t x = 0; x < w; x += sw) {
        for (size_t y = 0; y < h; y += sh) {
            auto img = CropImage::Cropping(src, x, y, sw, sh);
            if (!img) {
                continue;
            }
            img->name = std::to_string(x) + "_" + std::to_string(y)
                + "_" + std::to_string(sw) + "_" + std::to_string(sh);
            dst.push_back(img);
        }
    }
}

}
}