#ifndef PARAM_INFO
#error "You must define PARAM_INFO macro before include this file"
#endif

PARAM_INFO(Filepath, String, filepath, m_filepath, ())

PARAM_INFO(TileSize,   Int, tile_size,   m_tile_size,   (0))
PARAM_INFO(BorderSize, Int, border_size, m_border_size, (0))
