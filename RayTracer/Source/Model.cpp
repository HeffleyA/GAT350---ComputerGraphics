#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Triangle.h"
#include "Sphere.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Model::Update()
{
	for (size_t i = 0; i < m_local_vertices.size(); i++)
	{
		m_vb[i] = m_transform * glm::vec4{ m_local_vertices[i], 1};
	}

	m_center = glm::vec3{ 0 };
	for (auto& vertex : m_vb)
	{
		m_center += vertex;
	}
	m_center /= (float)m_vb.size();

	m_radius = 0;
	for (auto& vertex : m_vb)
	{
		float radius = glm::length(vertex - m_center);
		m_radius = glm::max(radius, m_radius);
	}
}

bool Model::Load(const std::string& filename)
{
		// open file using ifstream (input file stream)
		std::ifstream stream(filename);
		// check if stream is_open
		if (!stream.is_open())
		{
			std::cerr << "Error opening filename " << filename << SDL_GetError() << std::endl;
			return false;
		}

		vertices_t vertices;
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

				vertices.push_back(position);
			}
			// read in faces (triangles)
			else if (line.substr(0, 2) == "f ")
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
					while (std::getline(sstream, indexString, '/'))
					{
						if (!indexString.empty())
						{
							std::istringstream indexStream{ indexString };
							indexStream >> index[i];
						}
						i++;
					}

					// check if index 0 (position) is valid
					if (index[0] != 0)
					{
						// get vertex at index position
						// index is 1 based, need to subtract one for array
						glm::vec3 position = vertices[index[0] - 1];

						m_local_vertices.push_back(position);
					}
				}
			}
		}

		m_vb.resize(m_local_vertices.size());
		stream.close();

		return true;
	}

bool Model::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
	float t;
	if (!Sphere::Raycast(ray, m_center, m_radius, minDistance, maxDistance, t))
	{
		return false;
	}

	// check cast ray with mesh triangles 
	for (size_t i = 0; i < m_vb.size(); i += 3)
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

			// calculate triangle normal (edge1 x edge2) [x = cross product]
			raycastHit.normal = glm::normalize(Cross(edge1, edge2));
			raycastHit.material = GetMaterial();


			return true;
		}
	}

	return false;
}

