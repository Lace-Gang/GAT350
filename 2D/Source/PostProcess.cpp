#include "PostProcess.h"

#include "MathUtils.h"
#include <algorithm>
#include <cmath>

//using lambda functions for all of these

void PostProcess::Invert(std::vector<color_t>& buffer)
{
	//for (auto& color : buffer) 
	//{
	//	color.r = 255 - color.r;
	//	color.g = 255 - color.g;
	//	color.b = 255 - color.b;
	//}

	//modern version:
	std::for_each(buffer.begin(), buffer.end(), [](auto& color)
		{
			color.r = 255 - color.r;
			color.g = 255 - color.g;
			color.b = 255 - color.b;
		});
}

void PostProcess::Monochrome(std::vector<color_t>& buffer)
{
	std::for_each(buffer.begin(), buffer.end(), [](auto& color)
		{
			uint8_t average = (uint8_t)((color.r + color.g + color.b) / 3); //of static-case<uint8_t>

			color.r = average;
			color.g = average;
			color.b = average;
		});
}

void PostProcess::ColorBalance(std::vector<color_t>& buffer, int ro, int go, int bo)
{
	std::for_each(buffer.begin(), buffer.end(), [ro, go, bo](auto& color)
		{
			color.r = (uint8_t)(Clamp(color.r + ro, 0, 255));
			color.g = (uint8_t)(Clamp(color.g + go, 0, 255));
			color.b = (uint8_t)(Clamp(color.b + bo, 0, 255));
		});
}

void PostProcess::Brightness(std::vector<color_t>& buffer, int brightness)
{
	std::for_each(buffer.begin(), buffer.end(), [brightness](auto& color)
		{
			color.r = (uint8_t)(Clamp(color.r + brightness, 0, 255));
			color.g = (uint8_t)(Clamp(color.g + brightness, 0, 255));
			color.b = (uint8_t)(Clamp(color.b + brightness, 0, 255));
		});
}


void PostProcess::Noise(std::vector<color_t>& buffer, uint8_t noise)
{
	std::for_each(buffer.begin(), buffer.end(), [noise](auto& color)
		{
			color.r = (uint8_t)(Clamp(color.r + rand() % noise - rand() % noise, 0, 255));
			color.g = (uint8_t)(Clamp(color.g + rand() % noise - rand() % noise, 0, 255));
			color.b = (uint8_t)(Clamp(color.b + rand() % noise - rand() % noise, 0, 255));
		});
}

void PostProcess::Threshold(std::vector<color_t>& buffer, uint8_t threshold)
{
	std::for_each(buffer.begin(), buffer.end(), [threshold](auto& color)
		{
			uint8_t average = (uint8_t)((color.r + color.g + color.b) / 3); //of static-case<uint8_t>
			uint8_t pixelValue = (average < threshold) ? 0 : 255;

			color.r = pixelValue;
			color.g = pixelValue;
			color.b = pixelValue;
		});
}

void PostProcess::Posterize(std::vector<color_t>& buffer, uint8_t levels)
{
	int level = 255 / levels;

	std::for_each(buffer.begin(), buffer.end(), [level](auto& color)
		{
			color.r = (color.r/level) * level;
			color.g = (color.g/level) * level;
			color.b = (color.b/level) * level;
		});
}

void PostProcess::BoxBlur(std::vector<color_t>& buffer, int width, int height)
{
	std::vector<color_t> source = buffer;

	//k for kernel
	//if we were pressed for memory, we'd use int8_t instead of int
	int k[3][3] =
	{
		{1, 1, 1},
		{1, 1, 1},
		{1, 1, 1}
	};


	for (int i = 0; i < buffer.size(); i++)
	{
		// % 5 : 1 2 3 4 5 6 7 8 9 10
		// = 	 1 2 3 4 0 1 2 3 4 0 
		int x = i % width;
		int y = i / width;

		//skip if out of range
		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int r = 0;
		int g = 0;
		int b = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				//x and y are the place, and then ix and iy are the displacement from the pixel we're changing to the one we're sampling
				color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
				int weight = k[iy][ix]; //row then column

				r += pixel.r * weight;
				g += pixel.g * weight;
				b += pixel.b * weight;
			}
		}
		
		color_t& color = buffer[i];
		color.r = static_cast<uint8_t>(r / 9);
		color.g = static_cast<uint8_t>(g / 9);
		color.b = static_cast<uint8_t>(b / 9);
	}
}

void PostProcess::GaussianBlur(std::vector<color_t>& buffer, int width, int height)
{
	std::vector<color_t> source = buffer;

	int k[3][3] =
	{
		{1, 2, 1},
		{2, 4, 2},
		{1, 2, 1}
	};


	for (int i = 0; i < buffer.size(); i++)
	{
		// % 5 : 1 2 3 4 5 6 7 8 9 10
		// = 	 1 2 3 4 0 1 2 3 4 0 
		int x = i % width;
		int y = i / width;

		//skip if out of range
		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int r = 0;
		int g = 0;
		int b = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				//x and y are the place, and then ix and iy are the displacement from the pixel we're changing to the one we're sampling
				color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
				int weight = k[iy][ix]; //row then column

				r += pixel.r * weight;
				g += pixel.g * weight;
				b += pixel.b * weight;
			}
		}

		color_t& color = buffer[i];
		color.r = static_cast<uint8_t>(r / 16);
		color.g = static_cast<uint8_t>(g / 16);
		color.b = static_cast<uint8_t>(b / 16);
	}
}

void PostProcess::Sharpen(std::vector<color_t>& buffer, int width, int height)
{
	std::vector<color_t> source = buffer;

	int k[3][3] =
	{
		{0, -1, 0},
		{-1, 5, -1},
		{0, -1, 0}
	};


	for (int i = 0; i < buffer.size(); i++)
	{
		// % 5 : 1 2 3 4 5 6 7 8 9 10
		// = 	 1 2 3 4 0 1 2 3 4 0 
		int x = i % width;
		int y = i / width;

		//skip if out of range
		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int r = 0;
		int g = 0;
		int b = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				//x and y are the place, and then ix and iy are the displacement from the pixel we're changing to the one we're sampling
				color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
				int weight = k[iy][ix]; //row then column

				r += pixel.r * weight;
				g += pixel.g * weight;
				b += pixel.b * weight;
			}
		}

		color_t& color = buffer[i];
		color.r = static_cast<uint8_t>(Clamp(r, 0, 255));
		color.g = static_cast<uint8_t>(Clamp(g, 0, 255));
		color.b = static_cast<uint8_t>(Clamp(b, 0, 255));
	}
}

void PostProcess::Edge(std::vector<color_t>& buffer, int width, int height, int threshold)
{
	std::vector<color_t> source = buffer;

	
	int hk[3][3] =
	{
		{1, 0, -1},
		{2, 0, -2},
		{1, 0, -1}
	};
	
	int vk[3][3] =
	{
		{-1, -2, 11},
		{0, 0, 0},
		{1, 2, 1}
	};


	for (int i = 0; i < buffer.size(); i++)
	{
		// % 5 : 1 2 3 4 5 6 7 8 9 10
		// = 	 1 2 3 4 0 1 2 3 4 0 
		int x = i % width;
		int y = i / width;

		//skip if out of range
		if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

		int h = 0;
		int v = 0;

		for (int iy = 0; iy < 3; iy++)
		{
			for (int ix = 0; ix < 3; ix++)
			{
				//x and y are the place, and then ix and iy are the displacement from the pixel we're changing to the one we're sampling
				color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];

				h += pixel.r * hk[iy][ix];
				v += pixel.r * vk[iy][ix];
			}
		}

		int m = std::sqrt((h * h + v * v));
		m = (m >= threshold) ? m : 0;
		uint8_t c = Clamp(m, 0, 255);

		color_t& color = buffer[i];
		color.r = c;
		color.g = c;
		color.b = c;
	}
}
