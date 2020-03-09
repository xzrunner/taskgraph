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

}