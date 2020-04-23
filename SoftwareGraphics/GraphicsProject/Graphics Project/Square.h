#include <GLEW/glew.h>
#include <glm/glm.hpp>

class Square {

public: 
	glm::float32 squareRotation = 90.0f;

	/*Square Vertices*/
	GLfloat squareVertices[32] = {
		/*Index 0*/
		-0.5, -0.5, 0.0,	// xyz coordinates
		0.0, 0.0,			// uv coordinates
		0.0, 0.0, 1.0,		// noraml for xyz
		/*Index 1*/
		-0.5, 0.5, 0.0, 
		0.0, 1.0,
		0.0, 0.0, 1.0,
		/*Index 2*/
		0.5, -0.5, 0.0,	
		1.0, 0.0,	
		0.0, 0.0, 1.0,
		/*Index 3*/
		0.5, 0.5, 0.0, 
		1.0, 1.0,
		0.0, 0.0, 1.0
	};

	/*Square Indices*/
	GLubyte squareIndices[6] = {
		0, 1, 2,
		1, 2, 3
	};

};

