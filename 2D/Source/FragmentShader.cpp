#include "FragmentShader.h"

color4_t FragmentShader::Process(const fragment_input_t& fragment)
{
	//return color4_t{ 1, 0, 0, 1 };
	//we can do effects up here if we want

	return fragment.color;
}


