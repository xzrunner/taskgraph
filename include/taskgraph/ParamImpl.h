#pragma once

#include "taskgraph/Param.h"

#include <memory>

namespace taskgraph
{

class PathParam : public Param
{
public:
    explicit PathParam(const std::vector<sm::vec3>& path)
        : m_path(path) {}

    virtual ParamType Type() const override {
        return ParamType::Path;
    }

    auto& GetPath() const { return m_path; }

private:
    std::vector<sm::vec3> m_path;

}; // PathParam

}