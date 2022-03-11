#ifndef MESH_H
#define MESH_H

#include<string>
#include<glad/glad.h>
#include<glm/glm.hpp>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"

class Mesh {
	public:
		std::vector <Vertex> vertices;
		std::vector <GLuint> indices;

		VAO VAO;

		Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices);

		void Draw(Shader& shader, Camera& camera, GLfloat = 0.0f, glm::vec3 rotVector = glm::vec3(0.0, 0.0, 0.0), GLfloat radians = 0.0f);
};
#endif
