#ifndef PARAM_INFO
#error "You must define PARAM_INFO macro before include this file"
#endif

PARAM_INFO(DirPath,  std::string, dir_path,  m_dir_path,  ())
PARAM_INFO(FilePath, std::string, file_path, m_file_path, ())
