#include "taskgraph/task/MakeDirectory.h"

#include <boost/filesystem.hpp>

namespace taskgraph
{
namespace task
{

void MakeDirectory::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    if (m_dir_path.empty()) {
        return;
    }

    try {
        if (boost::filesystem::exists(m_dir_path)) {
            boost::filesystem::remove_all(m_dir_path);
        }

        boost::filesystem::create_directory(m_dir_path);
    } catch (boost::filesystem::filesystem_error const & e) {
        printf("%s\n", e.what());
    }

}

}
}