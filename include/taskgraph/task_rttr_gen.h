#define XSTR(s) STR(s)
#define STR(s) #s

#ifndef PARM_TASK_TYPE
#error "You must define PARM_TASK_TYPE macro before include this file"
#endif

#ifndef PARM_TASK_NAME
#error "You must define PARM_TASK_NAME macro before include this file"
#endif

#ifndef PARM_FILEPATH_PARM
#define PARM_FILEPATH_PARM taskgraph/task/##PARM_TASK_TYPE##.parm.h
#endif

#define RTTR_NAME taskgraph::##PARM_TASK_NAME

rttr::registration::class_<taskgraph::task::PARM_TASK_TYPE>(XSTR(RTTR_NAME))
.constructor<>()
#define PARM_FILEPATH XSTR(PARM_FILEPATH_PARM)
#define PARM_NODE_CLASS taskgraph::task::##PARM_TASK_TYPE
#include <dag/rttr_prop_gen.h>
#undef PARM_FILEPATH
#undef PARM_NODE_CLASS
;

#undef PARM_TASK_NAME
#undef PARM_TASK_TYPE
#undef PARM_FILEPATH_PARM
