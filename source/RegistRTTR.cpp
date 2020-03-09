#define EXE_FILEPATH "taskgraph/task_include_gen.h"
#include "taskgraph/task_regist_cfg.h"
#undef EXE_FILEPATH

#include "taskgraph/Task.h"

#include <rttr/registration>

RTTR_REGISTRATION
{

// base

rttr::registration::class_<dag::Node<taskgraph::ParamType>::Port>("taskgraph::Task::Port")
	.property("var", &dag::Node<taskgraph::ParamType>::Port::var)
;

rttr::registration::class_<taskgraph::Task>("taskgraph::Task")
	.method("GetImports", &taskgraph::Task::GetImports)
	.method("GetExports", &taskgraph::Task::GetExports)
;

#define EXE_FILEPATH "taskgraph/task_rttr_gen.h"
#include "taskgraph/task_regist_cfg.h"
#undef EXE_FILEPATH

}

namespace taskgraph
{

void regist_rttr()
{
}

}