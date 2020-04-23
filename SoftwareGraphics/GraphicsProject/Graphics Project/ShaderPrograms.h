#include <iostream>
#include <GLEW/glew.h>

using namespace std;

class ShaderPrograms {

public:
	GLuint cylinderShaderProgram;
	GLuint lightShaderProgram;
	GLuint squareShaderProgram;

	string getCylinderVertexShaderSource() {
		return cylinderVertexShaderSource;
	}

	string getCylinderFragementShaderSource() {
		return cylinderFragmentShaderSource;
	}

	string getLightVertexShaderSource() {
		return lightVertexShaderSource;
	}

	string getLightFragmentShaderSource() {
		return lightFragmentShaderSource;
	}

	string getSquareVertexShaderSource() {
		return squareVertexShaderSource;
	}

	string getSquareFragmentShaderSource() {
		return squareFragmentShaderSource;
	}

	/*Create and Compile Shaders*/
	GLuint CompileShader(const string& source, GLuint shaderType) {
		// Create Shader object
		GLuint shaderID = glCreateShader(shaderType);
		const char* src = source.c_str();
		// Attach source code to Shader object
		glShaderSource(shaderID, 1, &src, nullptr);
		// Compile Shader
		glCompileShader(shaderID);
		// Return ID of Compiled shader
		return shaderID;
	}

	/*Create Program Object*/
	GLuint CreateShaderProgram(const string& vertexShader, const string& fragmentShader) {
		// Compile vertex shader
		GLuint vertexShaderComp = CompileShader(vertexShader, GL_VERTEX_SHADER);
		// Compile fragment shader
		GLuint fragmentShaderComp = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
		// Create program object
		GLuint shaderProgram = glCreateProgram();
		// Attach vertex and fragment shaders to program object
		glAttachShader(shaderProgram, vertexShaderComp);
		glAttachShader(shaderProgram, fragmentShaderComp);
		// Link shaders to create executable
		glLinkProgram(shaderProgram);
		// Delete compiled vertex and fragment shaders
		glDeleteShader(vertexShaderComp);
		glDeleteShader(fragmentShaderComp);
		// Return Shader Program
		return shaderProgram;
	}

	/*Cylinder vertex shader source code*/
	string cylinderVertexShaderSource =
		"#version 330 core\n"
		/*Passed in from vao and named*/
		"layout(location = 0) in vec4 vPosition;"
		"layout(location = 1) in vec2 texCoord;"
		"layout(location = 2) in vec3 normal;"
		/*Name variables passed to fragment shader*/
		"out vec2 oTexCoord;"
		"out vec3 oNormal;"
		"out vec3 FragPos;"
		/*Variables named and initilized from main*/
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		/*Run program in GPU*/
		"void main()\n"
		"{\n"
		/*Determine position of points*/
		"gl_Position = projection * view * model * vPosition;"
		/*Set variables to be sent to fragment shader*/
		"oTexCoord = texCoord;"
		"oNormal = mat3(transpose(inverse(model))) * normal;"
		"FragPos = vec3(model * vPosition);"
		"}\n";

	/*Cylinder fragment shader source code*/
	string cylinderFragmentShaderSource =
		"#version 330 core\n"
		/*Name variables passed to fragment shader*/
		"in vec2 oTexCoord;"
		"in vec3 oNormal;"
		"in vec3 FragPos;"
		/*Name variables used to draw*/
		"out vec4 fragColor;"
		/*Variables named and initilized from main*/
		"uniform sampler2D myTexture;"
		"uniform vec3 objectColor;"
		"uniform vec3 backgroundLightColor;"
		"uniform vec3 focusLightColor;"
		"uniform vec3 backgroundLightPos;"
		"uniform vec3 focusLightPos;"
		"uniform vec3 viewPos;"
		/*Run program in GPU*/
		"void main()\n"
		"{\n"
		/*Ambient Lighting*/
		"float ambientStrength = 0.85f;"
		"vec3 ambient = ambientStrength * backgroundLightColor;"
		/*Diffuse Lighting*/
		"vec3 norm = normalize(oNormal);"
		"vec3 focusLightDirection = normalize(focusLightPos - FragPos);"
		"float focusDiff = max(dot(norm, focusLightDirection), 0.0);"
		"vec3 focusDiffuse = focusDiff * focusLightColor;"
		"vec3 backgroundLightDirection = normalize(backgroundLightPos - FragPos);"
		"float backgroundDiff = max(dot(norm, backgroundLightDirection), 0.0);"
		"vec3 backgroundDiffuse = backgroundDiff * backgroundLightColor;"
		/*Specular Lighting*/
		"float focusSpecularStrength = 10.0;"
		"vec3 viewDir = normalize(viewPos - FragPos);"
		"vec3 focusReflectDir = reflect(focusLightDirection, norm);"
		"float focusSpec = pow(max(dot(viewDir, focusReflectDir), 0.0), 8);"
		"vec3 focusSpecular = focusSpecularStrength * focusSpec * focusLightColor;"
		"float backgroundSpecularStrength = 10.0;"
		"vec3 backgroundReflectDir = reflect(backgroundLightDirection, norm);"
		"float backgroundSpec = pow(max(dot(viewDir, backgroundReflectDir), 0.0), 32);"
		"vec3 backgroundSpecular = backgroundSpecularStrength * backgroundSpec * backgroundLightColor;"
		/*Results and application of lighting*/
		/*result =  lighting * objectColor*/
		"vec3 result = (ambient + focusDiffuse + backgroundDiffuse + focusSpecular + backgroundSpecular) * objectColor;"
		"fragColor = texture(myTexture, oTexCoord) * vec4(result, 1.0f);"
		"}\n";

	/*Light vertex shader source code*/
	string lightVertexShaderSource =
		"#version 330 core\n"
		/*Passed in from vao and named*/
		"layout(location = 0) in vec3 vPosition;"
		/*Variables named and initilized from main*/
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		/*Run program in GPU*/
		"void main()\n"
		"{\n"
		/*Determine position of points*/
		"gl_Position = projection * view * model * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);"
		"}\n";

	/*Light fragment shader source code*/
	string lightFragmentShaderSource =
		"#version 330 core\n"
		/*Name variables used to draw*/
		"out vec4 fragColor;"
		"uniform vec3 lightColor;"
		/*Run program in GPU*/
		"void main()\n"
		"{\n"
		"fragColor = vec4(lightColor, 1.0f);"
		"}\n";

	/*Square vertex shader source code*/
	string squareVertexShaderSource =
		"#version 330 core\n"
		/*Passed in from vao and named*/
		"layout(location = 0) in vec3 vPosition;"
		"layout(location = 1) in vec2 texCoord;"
		"layout(location = 2) in vec3 normal;"
		/*Name variables passed to fragment shader*/
		"out vec2 oTexCoord;"
		"out vec3 oNormal;"
		"out vec3 FragPos;"
		/*Variables named and initilized from main*/
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		/*Run program in GPU*/
		"void main()\n"
		"{\n"
		/*Determine position of points*/
		"gl_Position = projection * view * model * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);"
		/*Set variables to be sent to fragment shader*/
		"oTexCoord = texCoord;"
		"oNormal = mat3(transpose(inverse(model))) * normal;"
		"FragPos = vec3(model * (vec4(vPosition.x, vPosition.y, vPosition.z, 1.0)));"
		"}\n";

	/*Square fragment shader source code*/
	string squareFragmentShaderSource =
		"#version 330 core\n"
		/*Name variables passed to fragment shader*/
		"in vec2 oTexCoord;"
		"in vec3 oNormal;"
		"in vec3 FragPos;"
		/*Name variables used to draw*/
		"out vec4 fragColor;"
		/*Variables named and initilized from main*/
		"uniform sampler2D myTexture;"
		"uniform vec3 floorColor;"
		"uniform vec3 backgroundLightColor;"
		"uniform vec3 focusLightColor;"
		"uniform vec3 backgroundLightPos;"
		"uniform vec3 focusLightPos;"
		"uniform vec3 viewPos;"
		/*Run program in GPU*/
		"void main()\n"
		"{\n"
		/*Ambient Lighting*/
		"float ambientStrength = 0.85f;"
		"vec3 ambient = ambientStrength * backgroundLightColor;"
		/*Diffuse Lighting*/
		"vec3 norm = normalize(oNormal);"
		"vec3 focusLightDirection = normalize(focusLightPos - FragPos);"
		"float focusDiff = max(dot(norm, focusLightDirection), 0.0);"
		"vec3 focusDiffuse = focusDiff * focusLightColor;"
		"vec3 backgroundLightDirection = normalize(backgroundLightPos - FragPos);"
		"float backgroundDiff = max(dot(norm, backgroundLightDirection), 0.0);"
		"vec3 backgroundDiffuse = backgroundDiff * backgroundLightColor;"
		/*Specular Lighting*/
		"float focusSpecularStrength = 2.0;"
		"vec3 viewDir = normalize(viewPos - FragPos);"
		"vec3 focusReflectDir = reflect(-focusLightDirection, norm);"
		"float focusSpec = pow(max(dot(viewDir, focusReflectDir), 0.0), 8);"
		"vec3 focusSpecular = focusSpecularStrength * focusSpec * focusLightColor;"
		"float backgroundSpecularStrength = 5.0;"
		"vec3 backgroundReflectDir = reflect(-backgroundLightDirection, norm);"
		"float backgroundSpec = pow(max(dot(viewDir, backgroundReflectDir), 0.0), 32);"
		"vec3 backgroundSpecular = backgroundSpecularStrength * backgroundSpec * backgroundLightColor;"
		/*Results and application of lighting*/
		/*result =  lighting * floorColor*/
		"vec3 result = (ambient + focusDiffuse + backgroundDiffuse + focusSpecular + backgroundSpecular) * floorColor;"
		"fragColor = texture(myTexture, oTexCoord) * vec4(result, 1.0f);"
		"}\n";

	/*Default shader constructor binds and builds all of the programs to be used later*/
	ShaderPrograms() {
		cylinderShaderProgram = CreateShaderProgram(getCylinderVertexShaderSource(), getCylinderFragementShaderSource());
		lightShaderProgram = CreateShaderProgram(getLightVertexShaderSource(), getLightFragmentShaderSource());
		squareShaderProgram = CreateShaderProgram(getSquareVertexShaderSource(), getSquareFragmentShaderSource());
	}
};

