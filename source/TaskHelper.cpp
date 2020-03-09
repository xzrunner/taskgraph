#include "taskgraph/TaskHelper.h"
#include "taskgraph/Task.h"

#include <dag/Utility.h>

namespace taskgraph
{

TaskPtr TaskHelper::GetInputTask(const Task& task, size_t idx)
{
    auto prev = dag::Utility::GetInputNode(task, idx);
    return prev ? std::static_pointer_cast<Task>(prev) : nullptr;
}

ParamPtr TaskHelper::GetInputParam(const Task& task, size_t idx)
{
    auto& imports = task.GetImports();
    if (idx < 0 || idx >= imports.size()) {
        return nullptr;
    }

    auto& conns = imports[idx].conns;
    if (conns.empty()) {
        return nullptr;
    }

    assert(imports[idx].conns.size() == 1);
    auto& conn = imports[idx].conns[0];
    auto in_task = conn.node.lock();
    assert(in_task->get_type().is_derived_from<Task>());
    auto& vals = std::static_pointer_cast<Task>(in_task)->GetAllValues();
    return conn.idx < static_cast<int>(vals.size()) ? vals[conn.idx] : nullptr;
}

}