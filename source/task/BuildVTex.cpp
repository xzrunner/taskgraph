#include "taskgraph/task/BuildVTex.h"
#include "taskgraph/task/Mipmap.h"
#include "taskgraph/task/SplitImage.h"
#include "taskgraph/ParamImpl.h"
#include "taskgraph/TaskHelper.h"

#include <fstream>
#include <algorithm>

namespace taskgraph
{
namespace task
{

void BuildVTex::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    if (m_filepath.empty()) {
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

    std::ofstream fout(m_filepath.c_str(), std::ios::binary);
    if (fout.fail()) {
        return;
    }

    // header 16 byte
    const uint32_t w = img->bmp.Width(); 
    fout.write(reinterpret_cast<const char*>(&w), sizeof(w));
    const uint32_t h = img->bmp.Height();
    fout.write(reinterpret_cast<const char*>(&h), sizeof(h));
    const uint16_t tile_sz = m_tile_size;
    fout.write(reinterpret_cast<const char*>(&tile_sz), sizeof(tile_sz));
    const uint16_t border_sz = m_border_size;
    fout.write(reinterpret_cast<const char*>(&border_sz), sizeof(border_sz));
    const uint16_t channels = static_cast<uint16_t>(img->bmp.Channels());
    fout.write(reinterpret_cast<const char*>(&channels), sizeof(channels));
    const uint16_t bytes = 2;
    fout.write(reinterpret_cast<const char*>(&bytes), sizeof(bytes));

    // mipmap
    std::vector<std::shared_ptr<Image>> mipmaps;
    const size_t max = static_cast<size_t>(std::min(std::log2(w), std::log2(h)));
    size_t levels = std::min(levels, static_cast<size_t>(std::log2(std::min(w, h) / m_tile_size)));
    Mipmap::Build(mipmaps, img, levels);

    // split and output
    auto page_size = m_tile_size + 2 * m_border_size;
    auto tile_size = page_size * page_size * channels * bytes;
    uint8_t* tile_buf = new uint8_t[tile_size];
    for (auto map : mipmaps)
    {
        std::vector<std::shared_ptr<Image>> imgs;
        SplitImage::Split(imgs, *map, m_tile_size, m_tile_size, false);
        for (auto sub_img : imgs)
        {
            auto& bmp = sub_img->bmp;
            auto src = bmp.GetPixels();
            for (size_t i = 0, n = bmp.Width() * bmp.Height() * bmp.Channels(); i < n; ++i) {
                assert(src[i] <= 0xff && src[i] >= 0);
                tile_buf[i] = static_cast<uint8_t>(src[i]);
            }
            fout.write(reinterpret_cast<const char*>(tile_buf), tile_size);
        }
    }
    delete[] tile_buf;

    fout.close();
}

}
}