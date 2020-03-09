#include "taskgraph/task/WriteImage.h"
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

void WriteImage::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    if (m_filepath.empty()) {
        return;
    }

    auto prev_param = TaskHelper::GetInputParam(*this, 0);
    if (!prev_param) {
        return;
    }

    assert(prev_param->Type() == ParamType::ImageArray);
    auto imgs = std::static_pointer_cast<ImageArrayParam>(prev_param)->GetAllImages();
    if (imgs.empty()) {
        return;
    }

    auto dir = boost::filesystem::path(m_filepath).parent_path();
    auto name = boost::filesystem::path(m_filepath).stem().string();
    switch (m_type)
    {
    case Type::PNG:

        break;

    case Type::HGT:
        for (size_t i = 0, n = imgs.size(); i < n; ++i)
        {
            auto& vals = imgs[i]->GetValues();
            if (vals.empty()) {
                continue;
            }

            auto filename = name + ".hgt" + std::to_string(i);
            auto filepath = boost::filesystem::absolute(filename, dir).string();

            std::ofstream fout(filepath.c_str(), std::ios::binary);
            fout.write(reinterpret_cast<const char*>(vals.data()), vals.size() * sizeof(vals[0]));
            fout.close();
        }
        break;
    }
}

}
}