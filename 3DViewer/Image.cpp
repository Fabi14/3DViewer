#include "Image.h"
#include <stb_image.h>


Image::Image(const std::string& filename, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	m_buffer = stbi_load(filename.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);
}

Image::~Image()
{
	stbi_image_free(m_buffer);
}
