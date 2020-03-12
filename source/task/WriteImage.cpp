#include "taskgraph/task/WriteImage.h"
#include "taskgraph/ParamImpl.h"
#include "taskgraph/TaskHelper.h"

#include <gimg_import.h>
#include <gimg_export.h>
#include <gimg_typedef.h>
#include <gis/ElevationLoader.h>

#include <boost/filesystem.hpp>

#define FORCE_OUTPUT_JPG

namespace taskgraph
{
namespace task
{

void WriteImage::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    if (m_filepath.empty()) {
        return;
    }

    auto prev_param = TaskHelper::GetInputParam(*this, 0);
    if (!prev_param) {
        return;
    }

    assert(prev_param->Type() == PT_IMAGE_ARRAY);
    auto imgs = std::static_pointer_cast<ImageArrayParam>(prev_param)->GetAllImages();
    if (imgs.empty()) {
        return;
    }

    auto dir = boost::filesystem::path(m_filepath).parent_path();
    auto name = boost::filesystem::path(m_filepath).stem().string();
    switch (m_type)
    {
    case Type::PNG:
        for (size_t i = 0, n = imgs.size(); i < n; ++i)
        {
            auto& img = imgs[i];
            auto& bmp = img->bmp;
            auto w = bmp.Width();
            auto h = bmp.Height();
            auto c = bmp.Channels();
            if (w == 0 || h == 0 || c == 0) {
                continue;
            }

            std::string filename = name;
            if (!img->name.empty()) {
                filename += "_" + img->name;
            } else {
                filename += "_" + std::to_string(i);
            }
#ifdef FORCE_OUTPUT_JPG
            filename += ".jpg";
#else
            filename += ".png";
#endif // FORCE_OUTPUT_JPG
            auto filepath = boost::filesystem::absolute(filename, dir).string();

            auto vals = bmp.GetPixels();
            GIMG_PIXEL_FORMAT fmt;
            switch (c)
            {
            case 1:
                fmt = GPF_RED;
                break;
            case 3:
                fmt = GPF_RGB;
                break;
            case 4:
#ifdef FORCE_OUTPUT_JPG
                fmt = GPF_RGB;
#else
                fmt = GPF_RGBA8;
#endif // FORCE_OUTPUT_JPG
                break;
            default:
                continue;
            }

            std::vector<uint8_t> pixels;
#ifdef FORCE_OUTPUT_JPG
            if (c == 4)
            {
                pixels.resize(w * h * c);
                for (size_t i = 0, n = w * h; i < n; ++i) {
                    for (size_t j = 0; j < 3; ++j) {
                        pixels[i * 3 + j] = static_cast<uint8_t>(vals[i * 4 + j]);
                    }
                }
            }
            else
            {
#endif // FORCE_OUTPUT_JPG
                pixels.resize(w * h * c);
                for (size_t i = 0, n = pixels.size(); i < n; ++i) {
                    pixels[i] = static_cast<uint8_t>(vals[i]);
                }
#ifdef FORCE_OUTPUT_JPG
            }
#endif // FORCE_OUTPUT_JPG
            gimg_export(filepath.c_str(), pixels.data(), w, h, fmt, 0);
        }
        break;

    case Type::HGT:
        for (size_t i = 0, n = imgs.size(); i < n; ++i)
        {
            auto& bmp = imgs[i]->bmp;
            auto w = bmp.Width();
            auto h = bmp.Height();
            auto c = bmp.Channels();
            if (w == 0 || h == 0 || c == 0) {
                continue;
            }
            auto vals = bmp.GetPixels();

            auto filename = name + ".hgt" + std::to_string(i);
            auto filepath = boost::filesystem::absolute(filename, dir).string();

            std::ofstream fout(filepath.c_str(), std::ios::binary);
            fout.write(reinterpret_cast<const char*>(vals), w * h * c * sizeof(vals[0]));
            fout.close();
        }
        break;
    }
}

}
}