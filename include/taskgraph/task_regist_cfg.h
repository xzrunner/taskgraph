#ifndef EXE_FILEPATH
#error "You must define EXE_FILEPATH macro before include this file"
#endif

// file

#define PARM_TASK_TYPE FileCompress
#define PARM_TASK_NAME file_compress
#include EXE_FILEPATH

#define PARM_TASK_TYPE FilePattern
#define PARM_TASK_NAME file_pattern
#include EXE_FILEPATH

#define PARM_TASK_TYPE FileRemove
#define PARM_TASK_NAME file_remove
#include EXE_FILEPATH

#define PARM_TASK_TYPE FileUncompress
#define PARM_TASK_NAME file_uncompress
#include EXE_FILEPATH

#define PARM_TASK_TYPE MakeDirectory
#define PARM_TASK_NAME make_dir
#include EXE_FILEPATH

// io

#define PARM_TASK_TYPE BuildVTex
#define PARM_TASK_NAME build_vtex
#include EXE_FILEPATH

#define PARM_TASK_TYPE ReadImage
#define PARM_TASK_NAME read_img
#include EXE_FILEPATH

#define PARM_TASK_TYPE WriteImage
#define PARM_TASK_NAME write_img
#include EXE_FILEPATH

// image

#define PARM_TASK_TYPE CropImage
#define PARM_TASK_NAME crop_img
#include EXE_FILEPATH

#define PARM_TASK_TYPE Mipmap
#define PARM_TASK_NAME mipmap
#include EXE_FILEPATH

#define PARM_TASK_TYPE SplitImage
#define PARM_TASK_NAME split_img
#include EXE_FILEPATH

// tools

#define PARM_TASK_TYPE Group
#define PARM_TASK_NAME group
#include EXE_FILEPATH
