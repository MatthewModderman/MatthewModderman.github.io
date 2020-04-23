#include <iostream>
#include <fstream>

#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL2/SOIL2.h>

#include "Camera.h"
#include "InputCallbackFunctions.h"

#include "Cylinder.h"
#include "Cube.h"
#include "Square.h"

#include "vboEboVao.h"
#include "ShaderPrograms.h"

using namespace std;

const double PI = 3.14159;
const float toRadians = PI / 180.0f;


/*Draw Primitive*/
void draw(GLenum mode, GLsizei indices, GLenum type) {
	glDrawElements(mode, indices, type, nullptr);
}


/*Check texture files exist*/
bool filesExist(string fileName) {
	fstream fstream;
	fstream.open(fileName);
	if (fstream.fail()) {
		return 0;
	} else {
		fstream.close();
		return 1;
	}
}

/***Main Method***/
int main(void) {

	/*Setup Camera and Window*/
	initCamera();
	GLFWwindow* window;

	/*Initialize the library*/
	if (!glfwInit())
		return -1;

	/*Verify texture files are present before launch*/
	bool checkFilesExist = (filesExist("crate.png") && filesExist("snhu.jpg"));

	/*Create a windowed mode window and its OpenGL context*/
	window = glfwCreateWindow(windowWidth, windowHeight, "Silo", NULL, NULL);
	if ((!window) || (!checkFilesExist)) {
		cout << "The window could not be launched because either the window was not created of files are missing." << endl;
		glfwTerminate();
		return -1;
	}

	/*Set input callback functions needed for project*/
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	/*Make the window's context current*/
	glfwMakeContextCurrent(window);

	/*Initialize GLEW*/
	if (glewInit() != GLEW_OK)
		cout << "Error!" << endl;

	/*Setup some OpenGL options*/
	glEnable(GL_DEPTH_TEST);

	/*Wireframe mode*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*Declare objects*/
	Cylinder myCylinder;
	Cube backgroundLighting(glm::vec3(20.0f, 10.0f, -30.0f));
	Cube focusLighting(glm::vec3(-3.0f, 3.0f, 0.0f));

	Square floor; // 11 by 11
	glm::vec3 tiles[121];
	int tileCount = 0;
	for (int i = -10; i < 12; i+=2) {
		for (int j = -10; j < 12; j+=2) {
			tiles[tileCount].x = (float)i;
			tiles[tileCount].y = 0.0f;
			tiles[tileCount].z = (float)j;
			tileCount++;
		}
	}


	/*Declare vboEboVao and call functions to generate buffers*/
	vboEboVao vboEboVao;
	vboEboVao.cylinderVboEboVao(&(myCylinder.cylinderVertices), &(myCylinder.cylinderIndices));
	vboEboVao.roofVboEboVao(&(myCylinder.roofVertices), &(myCylinder.roofIndices));
	vboEboVao.cubeVboEboVao(&(backgroundLighting.cubeVertices), &(backgroundLighting.cubeIndices));
	vboEboVao.squareVboEboVao(&(floor.squareVertices), &(floor.squareIndices));


	/*Load images*/
	int brickTexWidth, brickTexHeight;
	int crateTexWidth, crateTexHeight;
	unsigned char* brickImage = SOIL_load_image("snhu.jpg", &brickTexWidth, &brickTexHeight, 0, SOIL_LOAD_RGB);
	unsigned char* crateImage = SOIL_load_image("crate.png", &crateTexWidth, &crateTexHeight, 0, SOIL_LOAD_RGB);

	/*Generate textures with the images*/
	GLuint brickTexture;
	glGenTextures(1, &brickTexture);
	glBindTexture(GL_TEXTURE_2D, brickTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, brickTexWidth, brickTexHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, brickImage);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(brickImage);
	glBindTexture(GL_TEXTURE_2D, 0);	

	GLuint crateTexture;
	glGenTextures(1, &crateTexture);
	glBindTexture(GL_TEXTURE_2D, crateTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, crateTexWidth, crateTexHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, crateImage);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(crateImage);
	glBindTexture(GL_TEXTURE_2D, 0);

	ShaderPrograms shaders;

	/*Loop until the user closes the window*/
	while (!glfwWindowShouldClose(window)) {
		/*Set delta time*/
		GLfloat currentFrame = glfwGetTime(); // get time for current frame
		deltaTime = currentFrame - lastFrame; // time between current and last
		lastFrame = currentFrame;			  // last frame is now current frame value

		/*Resize window and graphics simultaneously*/
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		/*Render*/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*Use Shader Program exe and select VAO before drawing*/ 
		glUseProgram(shaders.cylinderShaderProgram); // Call Shader per-frame when updating attributes

		/*Declare and initialize projection matrix*/
		glm::mat4 projectionMatrix;
		projectionMatrix = glm::perspective(fov, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0f, 30.0f);

		/*Declare and initialize view matrix*/
		glm::mat4 viewMatrix;
		viewMatrix = glm::lookAt(cameraPosition, getTarget(), worldUp);
		viewMatrix = glm::rotate(viewMatrix, 33.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f)); // 45 degree view around x-axis

		/*Declare and initialize model matrix*/
		glm::mat4 modelMatrix;


		/***USE CYLINDERSHADERPROGRAM TO DRAW CYLINDER OBJECTS*/
		/*Get matrix's uniform location and set matrix for cylinder*/
		GLint modelLoc = glGetUniformLocation(shaders.cylinderShaderProgram, "model");
		GLint viewLoc = glGetUniformLocation(shaders.cylinderShaderProgram, "view");
		GLint projLoc = glGetUniformLocation(shaders.cylinderShaderProgram, "projection");
		/*Set view, projection, and model Uniform objectsfor cylinder*/
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		/*Get object and light position for cylinder*/
		GLint backgroundLightPosLoc = glGetUniformLocation(shaders.cylinderShaderProgram, "backgroundLightPos");
		GLint focusLightPosLoc = glGetUniformLocation(shaders.cylinderShaderProgram, "focusLightPos");
		GLint viewPosLoc = glGetUniformLocation(shaders.cylinderShaderProgram, "viewPos");
		/*Set object and light position for cylinder*/
		glUniform3f(backgroundLightPosLoc, backgroundLighting.cubePosition.x, backgroundLighting.cubePosition.y, backgroundLighting.cubePosition.z);
		glUniform3f(focusLightPosLoc, focusLighting.cubePosition.x, focusLighting.cubePosition.y, focusLighting.cubePosition.z);
		glUniform3f(viewPosLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		/*Get lighting and object colors for cylinder*/
		GLint objectColorLoc = glGetUniformLocation(shaders.cylinderShaderProgram, "objectColor");
		GLint backgroundLightColorLoc = glGetUniformLocation(shaders.cylinderShaderProgram, "backgroundLightColor");
		GLint focusLightColorLoc = glGetUniformLocation(shaders.cylinderShaderProgram, "focusLightColor");
		/*Set lighting and object colors for cylinder*/
		glUniform3f(objectColorLoc, 0.46f, 0.36f, 0.25f);
		glUniform3f(backgroundLightColorLoc, 1.0f, 1.0f, 0.0f);
		glUniform3f(focusLightColorLoc, 0.0f, 1.0f, 0.0f);

		/*Bind vaoCylinder to create cylinder object with brick texture*/
		glBindVertexArray(vboEboVao.vaoCylinder); 
		glBindTexture(GL_TEXTURE_2D, brickTexture); 

		/*Draw cylinder primatives*/
		draw(GL_TRIANGLE_STRIP, 130, GL_UNSIGNED_BYTE);

		/*Unbind VAO and shader program*/
		glBindVertexArray(0);
		glUseProgram(0);

		/*Bind vaoCylinder to create roof of cylinder object with brick texture*/
		glUseProgram(shaders.cylinderShaderProgram);
		glBindVertexArray(vboEboVao.vaoRoof);


		/*Draw roof primitives*/
		draw(GL_TRIANGLE_FAN, 66, GL_UNSIGNED_BYTE);

		/*Unbind VAO and shader program*/
		glBindVertexArray(0); 
		glUseProgram(0); 


		/***USE LIGHTSHADERPROGRAM TO DRAW LIGHT OBJECTS*/
		/*Pass uniform values to GPU to create light objects*/
		glUseProgram(shaders.lightShaderProgram);
		GLint lightModelLoc = glGetUniformLocation(shaders.lightShaderProgram, "model");
		GLint lightViewLoc = glGetUniformLocation(shaders.lightShaderProgram, "view");
		GLint lightProjLoc = glGetUniformLocation(shaders.lightShaderProgram, "projection");
		glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(lightProjLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		/*Set color for backgroundlight object*/
		GLint focusLightingColorLoc = glGetUniformLocation(shaders.lightShaderProgram, "lightColor");
		glUniform3f(focusLightingColorLoc, 1.0f, 1.0f, 0.0f);

		/*Bind vaoLight to create light objects called before draw*/
		glBindVertexArray(vboEboVao.vaoLight);

		/*Transform Planes to Create Background Light Source Cube*/
		for (GLuint i = 0; i < 6; i++) {
			glm::mat4 modelMatrix;
			modelMatrix = glm::translate(modelMatrix, backgroundLighting.cubePlanePositions[i] / glm::vec3(0.1f, 0.1f, 0.1f) + backgroundLighting.cubePosition);
			modelMatrix = glm::rotate(modelMatrix, backgroundLighting.cubePlaneRotations[i] * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(10.0f, 10.0f, 10.0f));
			if (i >= 4) {
				modelMatrix = glm::rotate(modelMatrix, backgroundLighting.cubePlaneRotations[i] * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			}
			glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			/*Draw background light primitives*/
			draw(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_BYTE);
		}

		/*Set color for focuslight object*/
		glUniform3f(focusLightingColorLoc, 0.0f, 1.0f, 0.0f);

		/*Transform Planes to Create Focus Light Source Cube*/
		for (GLuint i = 0; i < 6; i++) {
			glm::mat4 modelMatrix;
			modelMatrix = glm::translate(modelMatrix, focusLighting.cubePlanePositions[i] / glm::vec3(2.0f, 2.0f, 2.0f) + focusLighting.cubePosition);
			modelMatrix = glm::rotate(modelMatrix, focusLighting.cubePlaneRotations[i] * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
			if (i >= 4) {
				modelMatrix = glm::rotate(modelMatrix, focusLighting.cubePlaneRotations[i] * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			}
			glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			/*Draw focus light primitives*/
			draw(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_BYTE);
		}

		/*Unbind cube VAO and shader program*/
		glBindVertexArray(0);
		glUseProgram(0);


		/***USE SQUARESHADERPROGRAM TO DRAW FLOOR OBJECT*/
		/*Pass uniform values to GPU to create square objects*/
		glUseProgram(shaders.squareShaderProgram);

		/*Get matrix's uniform location and set matrix*/
		GLint floorModelLoc = glGetUniformLocation(shaders.squareShaderProgram, "model");
		GLint floorViewLoc = glGetUniformLocation(shaders.squareShaderProgram, "view");
		GLint floorProjLoc = glGetUniformLocation(shaders.squareShaderProgram, "projection");
		glUniformMatrix4fv(floorViewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(floorProjLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		/*Get object and light position for square*/
		backgroundLightPosLoc = glGetUniformLocation(shaders.squareShaderProgram, "backgroundLightPos");
		focusLightPosLoc = glGetUniformLocation(shaders.squareShaderProgram, "focusLightPos");
		viewPosLoc = glGetUniformLocation(shaders.squareShaderProgram, "viewPos");

		/*Set object and light position for square*/
		glUniform3f(backgroundLightPosLoc, backgroundLighting.cubePosition.x, backgroundLighting.cubePosition.y, backgroundLighting.cubePosition.z);
		glUniform3f(focusLightPosLoc, focusLighting.cubePosition.x, focusLighting.cubePosition.y, focusLighting.cubePosition.z);
		glUniform3f(viewPosLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		/*Get lighting and object colors for square*/
		GLint floorColorLoc = glGetUniformLocation(shaders.squareShaderProgram, "floorColor");	
		backgroundLightColorLoc = glGetUniformLocation(shaders.squareShaderProgram, "backgroundLightColor");
		focusLightColorLoc = glGetUniformLocation(shaders.squareShaderProgram, "focusLightColor");

		/*Set lighting and object colors for square*/
		glUniform3f(backgroundLightColorLoc, 1.0f, 1.0f, 0.0f);
		glUniform3f(focusLightColorLoc, 0.0f, 1.0f, 0.0f);
		glUniform3f(floorColorLoc, 0.7f, 0.7f, 0.5f);

		/*Bind vaoSquare to create square called before draw*/
		glBindVertexArray(vboEboVao.vaoSquare);
		glBindTexture(GL_TEXTURE_2D, crateTexture);

		modelMatrix = glm::rotate(modelMatrix, floor.squareRotation * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));

		for (GLuint i = 0; i < 121; i++) {
			glm::mat4 modelMatrix;
			modelMatrix = glm::translate(modelMatrix, tiles[i]);
			modelMatrix = glm::rotate(modelMatrix, floor.squareRotation * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
			glUniformMatrix4fv(floorModelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
			draw(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_BYTE);
		}

		/*Unbind VAO and shader program for square*/
		glBindVertexArray(0);
		glUseProgram(0);

		/*Swap front and back buffers*/
		glfwSwapBuffers(window);
		/*Poll for and process events*/
		glfwPollEvents();
		/*Poll camera transformations*/
		TransformCamera();
	}

	/***CLEAR GPU RESOURCES FOR ALL OBJECTS*/
	glDeleteVertexArrays(1, &vboEboVao.vaoCylinder);
	glDeleteBuffers(1, &vboEboVao.vboCylinder);
	glDeleteBuffers(1, &vboEboVao.eboCylinder);

	glDeleteVertexArrays(1, &vboEboVao.vaoRoof);
	glDeleteBuffers(1, &vboEboVao.vboRoof);
	glDeleteBuffers(1, &vboEboVao.eboRoof);

	glfwTerminate();
	return 0;
}