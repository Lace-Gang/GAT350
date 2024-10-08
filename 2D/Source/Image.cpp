#include "Image.h"

#include<string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


bool Image::Load(const std::string& filename)
{
	
	// load image getting the width and height (pass 4 for the last parameter to create RGBA image)
	int channels;
	uint8_t* data = stbi_load(filename.c_str(), &m_width, &m_height, &channels, 4);
	if (data == nullptr)
	//if (!data)
	{
		std::cerr << "Error loading image: " << filename << std::endl;
		return false;
	}

	// resize the image buffer to the number of pixels in the image
	m_buffer.resize(m_width * m_height );

	// copy the image data into the buffer, !!takes in number of bytes to copy!! 
	//std::cout << &m_width << " " << std::endl;
	//std::cout << &m_height << " " << std::endl;
	//std::cout << &data << " " << std::endl;
	std::memcpy(m_buffer.data(), data, m_width * m_height * sizeof(color_t));
	//std::memcpy(m_buffer.data(), data, m_width * m_height * sizeof data); 
	// https://en.cppreference.com/w/cpp/string/byte/memcpy

	// free the image data
	stbi_image_free(data);

	return true;
}
