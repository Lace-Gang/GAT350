#include "Rasterizer.h"
#include "Framebuffer.h"

namespace Rasterizer
{
	void Triangle(Framebuffer& framebuffer,
		const glm::vec2& p0,
		const glm::vec2& p1,
		const glm::vec2& p2,
		const vertex_output_t& v0,
		const vertex_output_t& v1,
		const vertex_output_t& v2)
	{
		// compute bounding box	
		int xmin = (int)std::max<float>(0, std::min({ std::floor(p0.x), std::floor(p1.x), std::floor(p2.x) }));
		int xmax = (int)std::min<float>((float)framebuffer.m_width - 1, std::max({ std::floor(p0.x), std::floor(p1.x), std::floor(p2.x) }));
		int ymin = (int)std::max<float>(0, std::min({ std::floor(p0.y), std::floor(p1.y), std::floor(p2.y) }));
		int ymax = (int)std::min<float>((float)framebuffer.m_height - 1, std::max({ std::floor(p0.y), std::floor(p1.y), std::floor(p2.y) }));

		for (int y = ymin; y <= ymax; ++y)
		{
			for (int x = xmin; x <= xmax; ++x)
			{
				glm::vec2 p{ x, y };

				// compute barycentric coordinates

				// this gives us twice the signed area of the whole triangle using the cross product
				float area = cross(p1 - p0, p2 - p0);
				// the sign tells us triangle winding (clockwise/counterclockwise)
				//if (std::abs(area) < std::numeric_limits<float>::epsilon()) return; //if area is zero, the program will crash at the next line, so we check for that
				//if (area <= 0) return;

				// area of subtriangles divided by total area
				float w0 = cross(p1 - p, p2 - p) / area;	// area of subtriangle opposite to v0
				float w1 = cross(p2 - p, p0 - p) / area;	// area of subtriangle opposite to v1
				float w2 = 1.0f - w0 - w1;					// area of subtriangle opposite to v2




				if (w0 >= 0 && w1 >= 0 && w2 >= 0)
				{
					// interpolate vertex attributes
					color3_t color = w0 * v0.color + w1 * v1.color + w2 * v2.color;
					//float z = <use v0, v1 and v2 position.z, interpolate using w0, w1 and w2 like color above>
					float z = w0 * v0.position.z + w1 * v1.position.z + w2 * v2.position.z;

					if (CheckDepth(framebuffer, p, z))
					{
						WriteDepth(framebuffer, p, z);
					}
					else
					{
						continue;
					}
					//We also have the ZBuffer (Depth Buffer)
					//Depth Buffer is how we will make sure that objects behind other objects are not rendered over top of those objects


					// create fragment shader input
					fragment_input_t fragment;
					fragment.color = color4_t{ color, 1 };

					// call fragment shader
					color4_t output_color = FragmentShader::Process(fragment);
					framebuffer.DrawPoint(x, y, ColorConvert(output_color));
				}
			}
		}
	}

	bool CheckDepth(Framebuffer& framebuffer, const glm::vec2& position, float z)
	{
		//int x = position.x;
		//int y = position.y;
		//int w = framebuffer.m_width;
		//int please = x + (y * w);

		//return (z < framebuffer.GetDepth()[<get index using position.x, position.y and the framebuffer width>]);
		//return (z < (framebuffer.GetDepth())->at(please));
		return (z < (framebuffer.GetDepth())->at(position.x + (position.y * framebuffer.m_width)));
	}

	void WriteDepth(Framebuffer& framebuffer, const glm::vec2& position, float z)
	{
		//framebuffer.GetDepth()[<get index using position.x, position.y and the framebuffer width>] = z;
		framebuffer.GetDepth()->at(position.x + (position.y * framebuffer.m_width)) = z;
	}

}
