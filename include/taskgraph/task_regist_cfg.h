#ifndef EXE_FILEPATH
#error "You must define EXE_FILEPATH macro before include this file"
#endif

// io

#define PARM_TASK_TYPE ReadImage
#define PARM_TASK_NAME read_image
#include EXE_FILEPATH

#define PARM_TASK_TYPE WriteImage
#define PARM_TASK_NAME write_image
#include EXE_FILEPATH

// image

#define PARM_TASK_TYPE Mipmap
#define PARM_TASK_NAME mipmap
#include EXE_FILEPATH