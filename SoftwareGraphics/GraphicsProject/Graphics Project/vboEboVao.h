#include <iostream>
#include <GLEW/glew.h>

class vboEboVao {

public:
	GLuint vboCylinder, eboCylinder, vaoCylinder;
	GLuint vboRoof, eboRoof, vaoRoof;
	GLuint vboLight, eboLight, vaoLight;
	GLuint vboSquare, eboSquare, vaoSquare;
	
	/*Build the vbo, ebo, and vao for cylinder*/
	void cylinderVboEboVao(GLfloat(*cylinderVertices)[1040], GLubyte(*cylinderIndices)[130]) {
		/*Generate buffers and vertex array for cylinder*/
		glGenBuffers(1, &vboCylinder);
		glGenBuffers(1, &eboCylinder);
		glGenVertexArrays(1, &vaoCylinder);

		glBindVertexArray(vaoCylinder); //Start sending information for vaoCylinder
		glBindBuffer(GL_ARRAY_BUFFER, vboCylinder); // Select VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboCylinder); // Select EBO 

		glBufferData(GL_ARRAY_BUFFER, sizeof(*cylinderVertices), *cylinderVertices, GL_STATIC_DRAW); // Load vertex attributes
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*cylinderIndices), *cylinderIndices, GL_STATIC_DRAW); // Load indices for cylinder

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // index vertex coordinates
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // index UV coordinates
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat))); // index normal values
		glEnableVertexAttribArray(2);

		/*Finish sending information for vaoCylinder*/
		glBindVertexArray(0);
	}

	/*Build the vbo, ebo, and vao for roof of cylinder*/
	void roofVboEboVao(GLfloat(*roofVertices)[528], GLubyte(*roofIndices)[66]) {
		/*Generate buffers and vertex array for roof*/
		glGenBuffers(1, &vboRoof);
		glGenBuffers(1, &eboRoof);
		glGenVertexArrays(1, &vaoRoof);
		
		glBindVertexArray(vaoRoof); //Start sending information for vaoRoof
		glBindBuffer(GL_ARRAY_BUFFER, vboRoof); // Select VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboRoof); // Select EBO

		glBufferData(GL_ARRAY_BUFFER, sizeof(*roofVertices), *roofVertices, GL_STATIC_DRAW); // Load vertex attributes
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*roofIndices), *roofIndices, GL_STATIC_DRAW); // Load indices for roof

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // index vertex coordinates
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // index UV coordinates
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat))); // index normal values
		glEnableVertexAttribArray(2);

		/*Finish sending information for vaoLight*/
		glBindVertexArray(0);
	}

	/*Build the vbo, ebo, and vao for cube*/
	void cubeVboEboVao(GLfloat(*cubeVertices)[12], GLubyte(*cubeIndices)[6]) {
		/*Generate buffers and vertex array for cubes*/
		glGenBuffers(1, &vboLight);
		glGenBuffers(1, &eboLight);
		glGenVertexArrays(1, &vaoLight);
		
		glBindVertexArray(vaoLight); //Start sending information for vaoLight
		glBindBuffer(GL_ARRAY_BUFFER, vboLight); // Select VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboLight); // Select EBO

		glBufferData(GL_ARRAY_BUFFER, sizeof(*cubeVertices), *cubeVertices, GL_STATIC_DRAW); // Load vertex attributes
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*cubeIndices), *cubeIndices, GL_STATIC_DRAW); // Load indices for cube

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); // index vertex coordinates
		glEnableVertexAttribArray(0);

		/*Finish sending information for vaoLight*/
		glBindVertexArray(0);
	}

	/*Build the vbo, ebo, and vao for square*/
	void squareVboEboVao(GLfloat(*squareVertices)[32], GLubyte(*squareIndices)[6]) {
		/*Generate buffers and vertex array for square*/
		glGenBuffers(1, &vboSquare);
		glGenBuffers(1, &eboSquare);
		glGenVertexArrays(1, &vaoSquare);

		glBindVertexArray(vaoSquare); //Start sending information for vaoSquare
		glBindBuffer(GL_ARRAY_BUFFER, vboSquare); // Select VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboSquare); // Select EBO 

		glBufferData(GL_ARRAY_BUFFER, sizeof(*squareVertices), *squareVertices, GL_STATIC_DRAW); // Load vertex attributes
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*squareIndices), *squareIndices, GL_STATIC_DRAW); // Load indices for square

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // index vertex coordinates
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // index UV coordinates
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat))); // index normal values
		glEnableVertexAttribArray(2);

		/*Finish sending information for vaoSquare*/
		glBindVertexArray(0);
	}
};

