#pragma once

#include <memory>

namespace taskgraph
{

class Task;
using TaskPtr = std::shared_ptr<Task>;

class Param;
using ParamPtr = std::shared_ptr<Param>;

}