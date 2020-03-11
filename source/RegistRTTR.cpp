#define EXE_FILEPATH "taskgraph/task_include_gen.h"
#include "taskgraph/task_regist_cfg.h"
#undef EXE_FILEPATH

#include "taskgraph/Task.h"
//#include "taskgraph/task/WriteImage.h"

#include <rttr/registration>

#define REGIST_ENUM_ITEM(type, name, label) \
    rttr::value(name, type),                \
    rttr::metadata(type, label)             \

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

rttr::registration::enumeration<taskgraph::task::WriteImage::Type>("task_write_img_type")
(
    REGIST_ENUM_ITEM(taskgraph::task::WriteImage::Type::PNG, "png", "PNG"),
    REGIST_ENUM_ITEM(taskgraph::task::WriteImage::Type::HGT, "hgt", "HGT")
);

}

namespace taskgraph
{

void regist_rttr()
{
}

}