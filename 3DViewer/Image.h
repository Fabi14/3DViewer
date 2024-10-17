#pragma once
#include <string>

struct Image
{
	Image(const std::string& filename, bool flip = true);
	~Image();

	unsigned char* m_buffer{};
	int m_width{};
	int m_height{};
	int m_bitsPerPixel{};
};
