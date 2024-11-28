#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Triangle.h"
#include "Sphere.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>




void Model::Update()
{
	for (size_t i = 0; i < m_local_vertices.size(); i++)
	{
		m_vb[i] = m_transform * glm::vec4{ m_local_vertices[i], 1 };
	}

	// get center point of transformed vertices
	m_center = glm::vec3{ 0 };
	for (auto& vertex : m_vb)
	{
		m_center += vertex;
	}
	m_center /= (float)m_vb.size();

	//After that, compute the radius by getting the length of each vertex from the center.Store the highest radius.

		// get radius of transformed vertices
	m_radius = 0;
	for (auto& vertex : m_vb)
	{
		//float radius = <use glm::length of the vector(vertex - m_center)>;
		float radius = glm::length(vertex - m_center);
		m_radius = glm::max(radius, m_radius);
		//m_radius = <use glm::max of the radius and m_radius>
	}

	//Finally, in the Hit() method, check for a sphere hit using Sphere::Raycast, providing all the parameters.If not hit, return false;
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

		vertexbuffer_t vertices;
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
					if (index[0] != 0) //this mihgt also need to be "if index[0]"
					{
						// get vertex at index position
						// index is 1 based, need to subtract one for array
						glm::vec3 position = vertices[index[0] - 1];

						// TODO: add position to m_vertices
						m_local_vertices.push_back(position);
						//std::cout << "something?" << std::endl;
					}
				}
			}
		}

		m_vb.resize(m_local_vertices.size());

		// TODO: close stream
		stream.close();

		return true;
	}



bool Model::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
	// check for bounding sphere raycast
	float t;
	if (!Sphere::Raycast(ray, m_center, m_radius, minDistance, maxDistance, t)) return false;


	// check cast ray with mesh triangles 
	for (size_t i = 0; i < m_vb.size(); i += 3) //<skip by 3>
	{
		float t;
		if (Triangle::Raycast(ray, m_vb[i], m_vb[i + 1], m_vb[i + 2], minDistance, maxDistance, t))
		{
			// set raycast hit
			raycastHit.distance = t;
			raycastHit.point = ray.at(t);

			// set edges of the triangle
			glm::vec3 edge1 = m_vb[i + 1] - m_vb[i];
			glm::vec3 edge2 = m_vb[i + 2] - m_vb[i];

			raycastHit.normal = glm::cross(edge1, edge2);
			raycastHit.material = GetMaterial();

			



			return true;
		}

		////Triangle triangle(<create triangle with the three vertex points>);
		//glm::vec3 point1{ m_vertices[i].x, m_vertices[i].y, m_vertices[i].z };
		//glm::vec3 point2{ m_vertices[i + 1].x, m_vertices[i + 1].y, m_vertices[i + 1].z };
		//glm::vec3 point3{ m_vertices[i + 2].x, m_vertices[i + 2].y, m_vertices[i + 2].z };
		//Triangle triangle(point1, point2, point3, SceneObject::GetMaterial().lock());
		//if (triangle.Hit(ray, raycastHit, minDistance, maxDistance))
		//{
		//	return true;
		//}
	}

	return false;
}







	


