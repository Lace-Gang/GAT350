#include "Framebuffer.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Image.h"

//#include <iostream>

Framebuffer::Framebuffer(const Renderer& renderer, int width, int height)
{
	m_width = width;
	m_height = height;
	m_pitch = width * sizeof(color_t);

	m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (m_texture == nullptr)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}
	m_buffer.resize(m_width * m_height);
}

Framebuffer::~Framebuffer()
{
	SDL_DestroyTexture(m_texture);
}

void Framebuffer::Update(const Renderer& renderer)
{	
	//creating the texture because it was being destroyed somewhere
	m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
	SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), m_pitch);
}

void Framebuffer::Clear(const color_t& color)
{
	std::fill(m_buffer.begin(), m_buffer.end(), color);
}



void Framebuffer::DrawPoint(int x, int y, const color_t& color)
{
	color_t& dest = m_buffer[x + y * m_width];

	dest = ColorBlend(color, dest);
}

void Framebuffer::DrawPointClip(int x, int y, const color_t& color)
{
	if (x >= m_width || x < 0 || y >= m_height || y < 0) return;

	color_t& dest = m_buffer[x + y * m_width];
	dest = ColorBlend(color, dest);
}



void Framebuffer::DrawRect(int x, int y, int w, int h, const color_t& color)
{
	if ((x + w) >= m_width || x < 0 || (y + h) >= m_height || y < 0) return;
	//if ((x + w) <= 0 && x < 0 && (y + h) >= 0 && y < 0) return;
	//if ((x + w) >= m_width && x > m_width && (y + h) >= m_height && y > m_height) return;


	//if (x < 0 && (x + w) > 0) x = 0;
	//if (y < 0 && (y + h) > 0 ) y = 0;

	for (int i = y; i <= (y + h); i++)
	{
		//if (i >= m_height) continue;
		for (int j = x; j <= (x + w); j++)
		{
			//if (j >= m_width) continue;
			m_buffer[i + j * m_width] = color;
		}
	}
}

void Framebuffer::DrawLineSlope(int x1, int y1, int x2, int y2, const color_t& color)
{
	//going to use slope intercept form: y= mx + b
	
	//slope
	int dx = x2 - x1; //run
	int dy = y2 - y1; //rise

	if (dx == 0)
	{
		if (y1 > y2) std::swap(y1, y2);
		for (int y = y1; y < y2; y++)
		{
			m_buffer[x1 + y * m_width] = color;

		}
	}
	else {
		float m = dy / (float)dx;
		//b = y-intercept
		float b = y1 - (m * x1);
		
		if (std::abs(dx) > std::abs(dy))
		{
			for (int x = x1; x <= x2; x++)
			{
				int y = (int)round((m * x) + b);
				m_buffer[x + y * m_width] = color;
			}
		}
		else { //rise > run
			for (int y = y1; y <= y2; y++)
			{
				int x = (int)round((y - b) /m);
				m_buffer[x + y * m_width] = color;
			}
		}
		
	}
}

void Framebuffer::DrawLine(int x1, int y1, int x2, int y2, const color_t& color)
{
	//Bresenham's Line Algorithm'

	int dx = x2 - x1;
	int dy = y2 - y1;

	//check for steep line
	bool steep = (std::abs(dy) > std::abs(dx));

	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	//ensure left to right drawing
	if(x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	//recalculate deltas
	dx = x2 - x1;
	dy = std::abs(y2 - y1);

	//set error term and y step direction
	int error = dx / 2;
	int ystep = (y1 < y2) ? 1 : -1; //so tempted to make this a short

	//draw line points
	for (int x = x1, y = y1; x <= x2; x++)
	{
		(steep) ? DrawPointClip(y, x, color) : DrawPointClip(x, y, color);

		//update error term
		error -= dy;

		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void Framebuffer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x3, y3, color);
	DrawLine(x3, y3, x1, y1, color);
}

void Framebuffer::DrawCircle(int xc, int yc, int r, const color_t& color)
{
	int x;
	int y;
	int d = 3 - (2 * r);

	x = 0;
	y = r;

	if (d > 0)
	{
		(x + 1, y - 1);
	}
	else {
		(x + 1, y);
	}

	DrawCirclePoints(xc, yc, x, y, color);

	while (x <= y)
	{
		if (d < 0)
		{
			d = d + (4 * x) + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
		DrawCirclePoints(xc, yc, x, y, color);
	}
}

void Framebuffer::DrawCirclePoints(int xc, int yc, int x, int y, const color_t& color)
{
	DrawPoint(xc + x, yc + y, color);
	DrawPoint(xc - x, yc + y, color);
	DrawPoint(xc + x, yc - y, color);
	DrawPoint(xc - x, yc - y, color);
	DrawPoint(xc + y, yc + x, color);
	DrawPoint(xc - y, yc + x, color);
	DrawPoint(xc + y, yc - x, color);
	DrawPoint(xc - y, yc - x, color);
}



void Framebuffer::DrawLinearCurve(int x1, int y1, int x2, int y2, const color_t& color)
{
	float dt = 1 / 10.f;
	float t1 = 0;
	for (int i = 0; i < 10; i++)
	{
		int sx1 = Lerp(x1, x2, t1);
		int sy1 = Lerp(y1, y2, t1);

		float t2 = t1 + dt;
		
		int sx2 = Lerp(x1, x2, t2);
		int sy2 = Lerp(y1, y2, t2);
		t1 += dt;
		
		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

void Framebuffer::DrawQuadraticCurve(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color)
{
	float dt = 1.0f / 100;
	float t1 = 0;
	for (int i = 0; i < 100; i++)
	{
		int sx1, sy1;

		QuadraticPoint(x1, y1, x2, y2, x3, y3, t1, sx1, sy1);

		float t2 = t1 + dt;
		int sx2, sy2;


		QuadraticPoint(x1, y1, x2, y2, x3, y3, t2, sx2, sy2);

		t1 += dt;

		DrawLine(sx1, sy1, sx2, sy2, color);
	}
}

void Framebuffer::DrawCubicCurve(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, const color_t& color)
{
	float dt = 1.0f / 100;
	float t1 = 0;

	float one_minus_t = 1 - t1;

	for (int i = 0; i < 100; i++)
	{

		int sx1, sy1;

		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t1, sx1, sy1);

		float t2 = t1 + dt;
		int sx2, sy2;


		CubicPoint(x1, y1, x2, y2, x3, y3, x4, y4, t2, sx2, sy2);

		t1 += dt;

		DrawLine(sx1, sy1, sx2, sy2, color);

	}


	//x = (int)(a1 * x1 + b1 * x2 + c1 * x3);
	//y = (int)(a1 * y1 + b1 * y2 + c1 * y3);


}

void Framebuffer::DrawImage(int x, int y, const Image& image)
{
	// check if off-screen
	//<look at DrawRect for example, use image width and height>
	if (y + image.m_height < 0 || x + image.m_width < 0 || y >= m_height || x >= m_width) return;

	
	// iterate through image y
	for (int iy = 0; iy < image.m_height; iy++)
	{
		// set screen y 
		int sy = y + iy;
		// check if off-screen, don't draw if off-screen
		//if (<check if screen y is off - screen>) < skip rest of loop > ;
		if (sy >= m_height || sy <= 0) continue;

		// iterate through image x
		for (int ix = 0; ix < image.m_width; ix++)
		{
			// set screen x
			int sx = x + ix;
			// check if off-screen, don't draw if off-screen
			if (sx >= m_width || sx <= 0) continue;

			// get image pixel color
			color_t color = image.m_buffer[ix + (iy * image.m_width)];
			//color_t color = image.m_buffer[<calculate image index with image x and image y>];
			// check alpha, if 0 don't draw
			if (color.a == 0) continue;
			// set buffer to color
			DrawPoint(sx, sy, color);

			//m_buffer[sx + sy * m_width] = color;
		}
	}
}
