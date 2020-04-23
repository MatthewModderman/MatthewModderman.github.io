#include <GLEW/glew.h>
#include <glm/gtc/matrix_transform.hpp>

class Cube {

public:

	/*Cube Vertices*/
	GLfloat cubeVertices[12] = {
		-0.5, -0.5, 0.0,	// index 0
		-0.5, 0.5, 0.0,		// index 1
		0.5, -0.5, 0.0,		// index 2	
		0.5, 0.5, 0.0		// index 3	
	};

	/*Cube Indices*/
	GLubyte cubeIndices[6] = {
		0, 1, 2,
		1, 2, 3
	};

	/*Cube Plane Translations*/
	glm::vec3 cubePlanePositions[6] = {
		glm::vec3(0.0f,  0.0f,  0.5f),
		glm::vec3(0.5f,  0.0f,  0.0f),
		glm::vec3(0.0f,  0.0f,  -0.5f),
		glm::vec3(-0.5f, 0.0f,  0.0f),
		glm::vec3(0.0f, 0.5f,  0.0f),
		glm::vec3(0.0f, -0.5f,  0.0f)
	};

	/*Cube Plane Rotations*/
	glm::float32 cubePlaneRotations[6] = {
	0.0f, 90.0f, 180.0f, 270.0f, 270.f, 90.f
	};

	/*Cube Position*/
	glm::vec3 cubePosition;

	/*Set cube position through constructor*/
	Cube(glm::vec3 positionOfCube) {
		cubePosition = positionOfCube;
	}
};

