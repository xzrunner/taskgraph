#include "taskgraph/task/FileRemove.h"
#include "taskgraph/ParamImpl.h"
#include "taskgraph/TaskHelper.h"

#include <boost/filesystem.hpp>

namespace taskgraph
{
namespace task
{

void FileRemove::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    auto prev_param = TaskHelper::GetInputParam(*this, 0);
    if (prev_param) 
    {
        assert(prev_param->Type() == PT_FILE);
        auto filepath = std::static_pointer_cast<FileParam>(prev_param)->GetFilepath();
        boost::filesystem::remove(filepath);

        return;
    }

    if (!m_dir_path.empty() && boost::filesystem::exists(m_dir_path)) {
        for (boost::filesystem::directory_iterator end_dir_it, it(m_dir_path); it != end_dir_it; ++it) {
            boost::filesystem::remove_all(it->path());
        }
    }
}

}
}