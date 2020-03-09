#define XSTR(s) STR(s)
#define STR(s) #s

#ifndef PARM_TASK_TYPE
#error "You must define PARM_TASK_TYPE macro before include this file"
#endif

#ifndef PARM_FILEPATH_H
#define PARM_FILEPATH_H taskgraph/task/##PARM_TASK_TYPE##.h
#endif

#include XSTR(PARM_FILEPATH_H)

#undef PARM_TASK_NAME
#undef PARM_TASK_TYPE
#undef PARM_FILEPATH_H
