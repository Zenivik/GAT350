#pragma once
#include "ColorBuffer.h"

#include <fstream>
	
class Image
{
public:
	friend class Framebuffer;

	Image() = default;
	Image(const std::string& filename, uint8_t alpha = 255);

	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip();

public:
	ColorBuffer colorBuffer;

		
};
