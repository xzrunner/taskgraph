#ifndef PARAM_INFO
#error "You must define PARAM_INFO macro before include this file"
#endif

PARAM_INFO(Filepath, String, filepath, m_filepath, ())
PARAM_INFO(Type, taskgraph::task::WriteImage::Type, type, m_type, ())
