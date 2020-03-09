#pragma once

#include "taskgraph/typedef.h"

namespace taskgraph
{

class TaskHelper
{
public:
    static TaskPtr GetInputTask(const Task& task, size_t idx);
    static ParamPtr GetInputParam(const Task& task, size_t idx);

}; // TaskHelper

}