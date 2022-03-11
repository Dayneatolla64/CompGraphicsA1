#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<tiny_obj_loader/tiny_obj_loader.h>

#include"Shaders.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"Mesh.h"

const unsigned int width = 800;
const unsigned int height = 800;

//Vertex* object;
//GLuint* indi2;

Vertex planeVertices[] = {
	Vertex{ glm::vec3(-0.5f, -0.001f, -0.5f), glm::vec3(0.0f, 0.3f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, -0.001f, 0.5f), glm::vec3(0.0f, 0.3f, 0.0f) },
	Vertex{ glm::vec3(0.5f, -0.001f, 0.5f), glm::vec3(0.0f, 0.3f, 0.0f) },
	Vertex{ glm::vec3(0.5f, -0.001f, -0.5f), glm::vec3(0.0f, 0.3f, 0.0f) }
};

GLuint planeIndices[] =
{
	0, 2, 1,
	0, 3, 2
};

Vertex treeVertices[] = {
	Vertex{ glm::vec3(-0.08f, 0.0f, 0.08f), glm::vec3(0.0f, 0.7f, 0.0f) }, //Left-Top-Mid 0
	Vertex{ glm::vec3(-0.1f, 0.0f, 0.0f), glm::vec3(0.0f, 0.7f, 0.0f) }, //Left 1
	Vertex{ glm::vec3(-0.08f, 0.0f, -0.08f), glm::vec3(0.0f, 0.7f, 0.0f) }, //Left Bot-Mid 2
	Vertex{ glm::vec3(0.0f, 0.0f, -0.1f), glm::vec3(0.0f, 0.7f, 0.0f) }, //Bottom 3
	Vertex{ glm::vec3(0.08f, 0.0f, -0.08f), glm::vec3(0.0f, 0.7f, 0.0f) }, //Right Bot-Mid 4
	Vertex{ glm::vec3(0.1f, 0.0f, 0.0f), glm::vec3(0.0f, 0.7f, 0.0f) }, //Right 5

	Vertex{ glm::vec3(0.08f, 0.0f, 0.08f), glm::vec3(0.0f, 0.7f, 0.0f) }, //Right Top-Mid 6
	Vertex{ glm::vec3(0.0f, 0.0f, 0.1f), glm::vec3(0.0f, 0.7f, 0.0f) }, //Top 7

	Vertex{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.7f, 0.0f) }, //Bot 8
	Vertex{ glm::vec3(0.0f, 0.6f, 0.0f), glm::vec3(0.0f, 0.7f, 0.0f) }, //Peak 9
};

GLuint treeIndices[]{
	0, 1, 8,
	1, 2, 8,
	2, 3, 8,
	3, 4, 8,
	4, 5, 8,
	5, 6, 8,
	6, 7, 8,
	7, 0, 8,

	0, 1, 9,
	1, 2, 9,
	2, 3, 9,
	3, 4, 9,
	4, 5, 9,
	5, 6, 9,
	6, 7, 9,
	7, 0, 9,
};

/*
void init() {
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err = tinyobj::LoadObj(shapes, materials, "monkey.obj", 0);

	if (!err.empty()) {
		std::cerr << err << std::endl;
		return;
	}

	int nv = shapes[0].mesh.positions.size();
	std::cout << nv << std::endl;
	const int triangles = floor(nv / 3);
	std::cout << nv << std::endl;
	object = new Vertex[triangles];
	for (int i = 0; i < triangles; i++) {
		object[i] = Vertex{ glm::vec3(shapes[0].mesh.positions[i], shapes[0].mesh.positions[i + 1],  shapes[0].mesh.positions[i + 2]), glm::vec3(0.83f, 0.70f, 0.44f) };
	}

	int ni = shapes[0].mesh.indices.size();
	indi2 = new GLuint[ni];
	for (int i = 0; i < ni; i++) {
		indi2[i] = shapes[0].mesh.indices[i];
		std::cout << indi2[i] << std::endl;
	}
}
*/

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Assignment 1 By: Dayne Dellaire", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("assignment1.vs", "assignment1.fs");

	std::vector <Vertex> verts(planeVertices, planeVertices + sizeof(planeVertices) / sizeof(Vertex));
	std::vector <GLuint> ind(planeIndices, planeIndices + sizeof(planeIndices) / sizeof(GLuint));
	Mesh plane(verts, ind);

	//verts = std::vector <Vertex>(pyramidVertices, pyramidVertices + sizeof(pyramidVertices) / sizeof(Vertex));
	//ind = std::vector <GLuint>(pyramidIndices, pyramidIndices + sizeof(pyramidIndices) / sizeof(GLuint));
	//glm::vec3 rot = glm::vec3(0.0, 0.0, 1.0);
	//Mesh pyramid(verts, ind);

	verts = std::vector <Vertex>(treeVertices, treeVertices + sizeof(treeVertices) / sizeof(Vertex));
	ind = std::vector <GLuint>(treeIndices, treeIndices + sizeof(treeIndices) / sizeof(GLuint));
	Mesh tree(verts, ind);

	//verts = std::vector <Vertex>(object, object + sizeof(object) / sizeof(Vertex));
	//ind = std::vector <GLuint>(indi2, indi2 + sizeof(indi2) / sizeof(GLuint));
	//Mesh monkey(verts, ind);

	glEnable(GL_DEPTH_TEST);
	Camera camera(width, height, glm::vec3(0.0f, 0.2f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.30f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		plane.Draw(shaderProgram, camera, 1);
		tree.Draw(shaderProgram, camera, 0.4, glm::vec3(0.2,0.0,-0.2));
		tree.Draw(shaderProgram, camera, 0.2, glm::vec3(-0.4, 0.0, -0.3));
		tree.Draw(shaderProgram, camera, 0.01, glm::vec3(-0.8, 0.0, 0.4));
		tree.Draw(shaderProgram, camera, 0.3, glm::vec3(0.35, 0.0, 0.6));
		//monkey.Draw(shaderProgram, camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

