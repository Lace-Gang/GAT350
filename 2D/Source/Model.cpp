#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include "VertexShader.h"
#include "Shader.h"


//void Model::Draw(Framebuffer& framebuffer, const glm::mat4& model, const Camera& camera)
void Model::Draw()
{
	Shader::Draw(m_vb);
	/*
	for (int i = 0; i < m_vb.size(); i += 3)
	{
		//convert point from model space to world space

		//vertex_t p1 = model * glm::vec4{ m_vb[i + 0], 1 };	
		//vertex_t p2 = model * glm::vec4{ m_vb[i + 1], 1 };	
		//vertex_t p3 = model * glm::vec4{ m_vb[i + 2], 1 };
		
		vertex_t p1 = model * glm::vec4{ m_vb[i + 0], 1 };
		vertex_t p2 = model * glm::vec4{ m_vb[i + 1], 1 };
		vertex_t p3 = model * glm::vec4{ m_vb[i + 2], 1 };

		//convert point from world space to view space

		p1 = camera.modelToView(p1);
		p2 = camera.modelToView(p2);
		p3 = camera.modelToView(p3);

		//convert point from view space to projection space
		//p1 = camera.ViewToProjection(p1);
		//p2 = camera.ViewToProjection(p2);
		//p3 = camera.ViewToProjection(p3);

		//convert point from view space to projection space

		glm::ivec2 s1 = camera.ViewToScreen(p1);
		glm::ivec2 s2 = camera.ViewToScreen(p2);
		glm::ivec2 s3 = camera.ViewToScreen(p3);

		if (s1.x == -1 || s1.y == -1 || s2.x == -1 || s2.y == -1 || s3.x == -1 || s3.y == -1)
		{
			continue;
		}

		framebuffer.DrawTriangle(s1.x, s1.y, s2.x, s2.y, s3.x, s3.y, ColorConvert(m_color));
	}
	*/
}

bool Model::Load(const std::string& filename)
{
	
		// open file using ifstream (input file stream)
		std::ifstream stream(filename);
		// check if stream is_open
		if (!stream.is_open())
		{
			std::cerr << "File did not open.";
			return false;
		}

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::string line;
		while (std::getline(stream, line))
		{
			// read in vertex positions
			// https://cplusplus.com/reference/string/string/substr/
			if (line.substr(0, 2) == "v ")
			{
				// read position of vertex
				std::istringstream sstream{ line.substr(2) };
				glm::vec3 position;
				sstream >> position.x;
				sstream >> position.y;
				sstream >> position.z;
				// TODO: stream in position y
				// TODO: stream in position z

				// TODO: add position to vertices vector
				vertices.push_back(position);
			}

			//read in vertex normals
			else if (line.substr(0, 3) == "vn ")
			{
				// read normal of vertex
				std::istringstream sstream{ line.substr(3) }; //this substring may need to be a 3? (it works fine rn though so I'm not sure)
				glm::vec3 normal;
				sstream >> normal.x;
				sstream >> normal.y;
				sstream >> normal.z;
				// TODO: stream in position y
				// TODO: stream in position z

				// TODO: add position to vertices vector
				normals.push_back(normal);
			}



			// read in faces (triangles)
			else if (line.substr(0,2) == "f ")
			{
				// read face (triangle), index of vertex position in vertices array [1, 2, 3]
				std::istringstream sstream{ line.substr(2) };
				std::string str;
				// https://en.cppreference.com/w/cpp/string/basic_string/getline
				while (std::getline(sstream, str, ' '))
				{
					std::istringstream sstream(str);
					std::string indexString;

					// read each triangle index (position, normal, uv)
					size_t i = 0;
					unsigned int index[3] = { 0, 0, 0 }; // 0 = position, 1 = normal, 2 = uv
					while (std::getline(sstream, indexString, '/' ))
					{
						if (!indexString.empty())
						{
							std::istringstream indexStream{ indexString };
							indexStream >> index[i];
							// TODO: stream indexStream into index[i]
						}
						i++;
					}

					// check if index 0 (position) is valid
					//if (index[0] != 0) //this mihgt also need to be "if index[0]"
					//if (index[0] && index[1]) //this mihgt also need to be "if index[0]"
					if(index[0])
					{
						// get vertex at index position
						// index is 1 based, need to subtract one for array
						//glm::vec3 position = vertices[index[0] - 1];

						vertex_t vertex;
						vertex.position = vertices[index[0] - 1];
						//vertex.position *= -1;

						//vertex.normal = normals[index[1] - 1]; //switch back to this if you switch the if back as well
						vertex.normal = (index[2]) ? normals[index[2] - 1] : glm::vec3{ 1 };
						//vertex.normal *= glm::vec3{ -1 };

						// TODO: add position to m_vertices
						//m_vb.push_back(position);
						m_vb.push_back(vertex);
						//std::cout << "something?" << std::endl;
					}
				}
			}
		}

		// TODO: close stream
		stream.close();

		return true;
	}

//void Model::SetColor(const color4_t& color)
//{
//	m_color = color;
//
//}


	


