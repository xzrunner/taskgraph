#include "taskgraph/task/ReadImage.h"
#include "taskgraph/ParamImpl.h"
#include "taskgraph/TaskHelper.h"

#include <gimg_import.h>
#include <gimg_typedef.h>
#include <gis/ElevationLoader.h>

#include <boost/filesystem.hpp>

namespace taskgraph
{
namespace task
{

void ReadImage::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    std::string filepath;

    auto prev_param = TaskHelper::GetInputParam(*this, 0);
    if (prev_param)
    {
        assert(prev_param->Type() == PT_FILE);
        filepath = std::static_pointer_cast<FileParam>(prev_param)->GetFilepath();
    }
    else
    {
        filepath = m_filepath;
    }

    if (filepath.empty()) {
        return;
    }

    std::shared_ptr<Image> img = nullptr;

    auto ext = boost::filesystem::extension(filepath);
    std::transform(ext.begin(), ext.end(), ext.begin(), tolower);

    if (ext == ".hgt")
    {
        size_t width, height;
        std::vector<int16_t> vals;
        if (gis::ElevationLoader::Load(filepath, width, height, vals))
        {
            img = std::make_shared<Image>(width, height, 1);
            auto pixels = img->bmp.GetPixels();
            for (size_t i = 0, n = vals.size(); i < n; ++i) {
                pixels[i] = vals[i];
            }
        }
    }
    else
    {
        int width, height, format;
        uint8_t* pixels = gimg_import(filepath.c_str(), &width, &height, &format);
        if (pixels)
        {
            int channels = 0;
            switch (format)
            {
            case GPF_ALPHA:
            case GPF_LUMINANCE:
            case GPF_LUMINANCE_ALPHA:
                channels = 1;
                break;
            case GPF_RGB:
                channels = 3;
                break;
            case GPF_RGBA8:
                channels = 4;
                break;
            default:
                assert(0);
            }

            img = std::make_shared<Image>(width, height, channels);
            auto vals = img->bmp.GetPixels();
            for (size_t i = 0, n = width * height * channels; i < n; ++i) {
                vals[i] = pixels[i];
            }
        }
    }

    if (img) {
        m_vals.resize(1);
        m_vals[0] = std::make_shared<ImageParam>(img);
    }
}

}
}