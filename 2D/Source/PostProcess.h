#pragma once

#include "Framebuffer.h"

namespace PostProcess
{
	void Invert(std::vector<color_t>& buffer); //want to work on the m_buffer itself. (& is more modern C++ than * for this)
	void Monochrome(std::vector<color_t>& buffer);
	void Brightness(std::vector<color_t>& buffer, int brightness);
	void ColorBalance(std::vector<color_t>& buffer, int ro, int go, int bo);
	void Noise(std::vector<color_t>& buffer, uint8_t noise);
	void Threshold(std::vector<color_t>& buffer, uint8_t threshold);
	void Posterize(std::vector<color_t>& buffer, uint8_t levels);
	void Alpha(std::vector<color_t>& buffer, uint8_t alpha);

	void BoxBlur(std::vector<color_t>& buffer, int width, int height);
	void GaussianBlur(std::vector<color_t>& buffer, int width, int height);
	void Sharpen(std::vector<color_t>& buffer, int width, int height);
	void Edge(std::vector<color_t>& buffer, int width, int height, int threshold);
	void Emboss(std::vector<color_t>& buffer, int width, int height);


	void Halfboss(std::vector<color_t>& buffer, int width, int height);
	void LSD(std::vector<color_t>& buffer, int width, int height);

}