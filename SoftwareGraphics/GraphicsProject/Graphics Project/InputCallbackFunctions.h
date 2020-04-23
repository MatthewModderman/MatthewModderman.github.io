#include <cmath>

/*Declare and initialize height and width for window and movement variables*/
int windowWidth = 1920, windowHeight = 1080;

/*Radius, pitch, and yaw for transformations*/
GLfloat radius = sqrt((cameraPosition.x - target.x) * (cameraPosition.x - target.x) + (cameraPosition.y - target.y) * (cameraPosition.y - target.y) + (cameraPosition.z - target.z) + (cameraPosition.z - target.z)); 
GLfloat rawYaw = 0.0f, rawPitch = 0.0f; // Initialize variables
GLfloat degYaw, degPitch; // Declare degree changes for yaw and pitch

/*Declare time to offset processing speed*/
GLfloat deltaTime = 0.0f, lastFrame = 0.0f; // Initialize variables

/*Declare X and Y coordinates and variables for mouse movements*/
GLfloat lastX = windowWidth / 2, lastY = windowHeight / 2;
GLfloat xChange, yChange;
bool firstMouseMove = true;

/***DEFINE INPUT CALLBACK FUNCTIONS*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	/*Define boolean answer in array based on action*/
	if (action == GLFW_PRESS) {
		keys[key] = true;
	} else if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
};

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	/*Set cursor position when mouse begins to move*/
	if (firstMouseMove) {
		lastX = xpos;
		lastY = ypos;
		firstMouseMove = false;
	}

	/*Calculate cursor offset*/
	xChange = xpos - lastX;
	yChange = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	/*Panning camera if isPanning is true*/
	if (isPanning) {

		if (cameraPosition.z > 0.0f) {
			cameraFront.z = -1.0f;
		} else {
			cameraFront.z = 1.0f;
		}

		GLfloat cameraSpeed = xChange * deltaTime; // Panning along x-axis
		cameraPosition += cameraSpeed * cameraRight;

		cameraSpeed = yChange * deltaTime;		  // Panning along y-axis
		cameraPosition += cameraSpeed * cameraUp;
	}

	/*Orbit camera if isOrbiting is true*/
	if (isOrbiting) {
		rawYaw += xChange;
		rawPitch += yChange;

		/*Convert Yaw and Pitch to degrees*/
		degYaw = glm::radians(rawYaw);
		degPitch = glm::clamp(glm::radians(rawPitch), -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f);

		/*Azimuth altitude formula*/
		cameraPosition.x = target.x + radius * sinf(degYaw) * cosf(degPitch);	// x = radius * sin(yaw) * cos(pitch)
		cameraPosition.y = target.y + radius * sinf(degPitch);					// y = sin(pitch)
		cameraPosition.z = target.z + radius * cosf(degYaw) * cosf(degPitch);	// z = radius * cos(yaw) * cos(pitch)
	}
	

};

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	/*Define boolean answer in array based on action*/
	if (action == GLFW_PRESS) {
		mouseButtons[button] = true;
	} else if (action == GLFW_RELEASE) {
		mouseButtons[button] = false;
	}
};

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (fov >= 1.0f && fov <= 45.0f) {
		fov -= yoffset * 0.2f;
	}

	/*Default FOV*/
	if (fov < 1.0f) {
		fov = 1.0f;
	}
	if (fov > 45.0f) {
		fov = 45.0f;
	}
};
