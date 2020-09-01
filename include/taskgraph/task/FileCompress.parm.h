#ifndef PARAM_INFO
#error "You must define PARAM_INFO macro before include this file"
#endif

PARAM_INFO(InputFilepath,  std::string, input_filepath,  m_input_filepath,  ())
PARAM_INFO(OutputFilepath, std::string, output_filepath, m_output_filepath, ())
