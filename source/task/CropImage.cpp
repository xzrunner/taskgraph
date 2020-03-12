#include "taskgraph/task/CropImage.h"
#include "taskgraph/ParamImpl.h"
#include "taskgraph/TaskHelper.h"

namespace taskgraph
{
namespace task
{

void CropImage::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    if (m_w <= 0 || m_h <= 0) {
        return;
    }

    auto prev_param = TaskHelper::GetInputParam(*this, 0);
    if (!prev_param) {
        return;
    }

    std::vector<std::shared_ptr<Image>> images;

    auto type = prev_param->Type();
    switch (type)
    {
    case PT_IMAGE:
    {
        auto img = std::static_pointer_cast<ImageParam>(prev_param)->GetImage();
        if (img) {
            auto sub = Cropping(*img, m_x, m_y, m_w, m_h);
            if (sub) {
                images.push_back(sub);
            }
        }
    }
        break;
    case PT_IMAGE_ARRAY:
    {
        auto& imgs = std::static_pointer_cast<ImageArrayParam>(prev_param)->GetAllImages();
        for (auto& img : imgs) {
            auto sub = Cropping(*img, m_x, m_y, m_w, m_h);
            if (sub) {
                images.push_back(sub);
            }
        }
    }
        break;
    }

    if (!images.empty())
    {
        m_vals.resize(1);
        m_vals[0] = std::make_shared<ImageArrayParam>(images);
    }
}

std::shared_ptr<Image>
CropImage::Cropping(const Image& img, size_t sub_x, size_t sub_y, size_t sub_w, size_t sub_h)
{
    auto w = img.bmp.Width();
    auto h = img.bmp.Height();
    auto c = img.bmp.Channels();
    if (sub_x >= static_cast<int>(w) ||
        sub_y >= static_cast<int>(h)) {
        return nullptr;
    }

    auto src_pixels = img.bmp.GetPixels();

    size_t min_x = sub_x;
    size_t min_y = sub_y;
    size_t max_x = std::min(min_x + sub_w, w);
    size_t max_y = std::min(min_y + sub_h, h);

    auto ret = std::make_shared<Image>(max_x - min_x, max_y - min_y, c);
    auto dst_pixels = ret->bmp.GetPixels();

    auto sw = max_x - min_x;
    auto sh = max_y - min_y;
    for (size_t y = min_y; y < max_y; ++y) {
        for (size_t x = min_x; x < max_x; ++x) {
            for (size_t i = 0; i < c; ++i) {
                auto s_idx = (y * w + x) * c + i;
                auto d_idx = ((y - min_y) * sw + x - min_x) * c + i;
                dst_pixels[d_idx] = src_pixels[s_idx];
            }
        }
    }

    return ret;
}

}
}