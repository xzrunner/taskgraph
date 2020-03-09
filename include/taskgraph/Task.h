#pragma once

#include "taskgraph/typedef.h"
#include "taskgraph/ParamType.h"

#include <dag/Node.h>

namespace taskgraph
{

class Task : public dag::Node<ParamType>
{
public:
    Task() {}

    auto& GetAllValues() const { return m_vals; }

protected:
    std::vector<ParamPtr> m_vals;

    RTTR_ENABLE(dag::Node<ParamType>)

}; // Task

}