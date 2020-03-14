#include "taskgraph/task/FilePattern.h"
#include "taskgraph/ParamImpl.h"

namespace taskgraph
{
namespace task
{

void FilePattern::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    if (m_file_path.empty()) {
        return;
    }

    m_vals.resize(1);
    m_vals[0] = std::make_shared<FileParam>(m_file_path);
}

}
}