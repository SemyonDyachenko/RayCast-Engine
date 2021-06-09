#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <glm.hpp>
#include <sstream>
#include <GL/glew.h>
#include "Mesh.h"

class OBJLoader
{

public:
	OBJLoader() {

	}

	virtual ~OBJLoader() {}

	static std::vector<Vertex>  loadObjModel(std::string filename) {

			std::vector<Vertex> finalVertices;

			std::string line = "";
			std::string prefix = "";
			glm::vec3 temp_vec3;
			glm::vec2 temp_vec2;
			GLuint temp_glint = 0;

			std::vector<glm::fvec3> vertices;
			std::vector<glm::fvec2> textures;
			std::vector<glm::fvec3> normals;

			std::vector<GLint> vertices_indices;
			std::vector<GLint> textures_indices;
			std::vector<GLint> normals_indices;
			

			std::stringstream ss;
			std::ifstream file(filename);
				
			if (!file.is_open()) {
				throw "Could not open obj file...";
			}
			while (std::getline(file, line))
			{
			 
				ss.clear();
				ss.str(line);
				ss >> prefix;

				if (prefix == "#")
				{

				}
				else if (prefix == "o")
				{

				}
				else if (prefix == "s")
				{

				}
				else if (prefix == "use_mtl")
				{

				}
				else if (prefix == "v") 
				{
					ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
					vertices.push_back(temp_vec3);
				}
				else if (prefix == "vt")
				{
					ss >> temp_vec2.x >> temp_vec2.y;
					textures.push_back(temp_vec2);
				}
				else if (prefix == "vn")
				{
					ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
					normals.push_back(temp_vec3);
				}
				else if (prefix == "f")
				{
					int counter = 0;
					while (ss >> temp_glint)
					{
						//Pushing indices into correct arrays
						if (counter == 0)
							vertices_indices.push_back(temp_glint);
						else if (counter == 1)
							textures_indices.push_back(temp_glint);
						else if (counter == 2)
							normals_indices.push_back(temp_glint);

						//Handling characters
						if (ss.peek() == '/')
						{
							++counter;
							ss.ignore(1, '/');
						}
						else if (ss.peek() == ' ')
						{
							++counter;
							ss.ignore(1, ' ');
						}

						//Reset the counter
						if (counter > 2)
							counter = 0;
					}
				}
				else
				{

				}
			}
			
	
			finalVertices.resize(vertices_indices.size(), Vertex());

		
			for (size_t i = 0; i < finalVertices.size(); ++i)
			{
				finalVertices[i].position = vertices[vertices_indices[i] - 1];
				finalVertices[i].texcoord = textures[textures_indices[i] - 1];
				finalVertices[i].normal = normals[normals_indices[i] - 1];
				finalVertices[i].color = glm::vec3(1.f, 1.f, 1.f);
			}

			return finalVertices;
		

		}
		
};

#endif