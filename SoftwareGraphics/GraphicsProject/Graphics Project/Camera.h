
/*Booleans to check camera transformations*/
bool isPanning = false;
bool isOrbiting = false;
bool isMoving = false;

/*Boolean array for keys and mouse buttons*/
bool keys[1024], mouseButtons[3];


/*Define camera attributes*/
GLfloat fov = 45.0f;
glm::vec3 cameraPosition = glm::vec3(0.0f, 5.0f, 10.0f); // Where the camera is located
glm::vec3 target = glm::vec3(0.0f, 0.5f, 0.0f); // Where the camera is pointed
glm::vec3 cameraDirection = glm::normalize(cameraPosition - target);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f); // Define up for world
glm::vec3 cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection)); // Define right for camera
glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight)); // Define up for camera
glm::vec3 cameraFront = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)); // 1 unit back from lens

/*Define initiate/reset camera function*/
void initCamera() {
	fov = 45.0f;
	cameraPosition = glm::vec3(0.0f, -1.0f, 10.0f); // Where the camera is located
	target = glm::vec3(0.0f, 0.5f, 0.0f); // Where the camera is pointed
	cameraDirection = glm::normalize(cameraPosition - target);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f); // Define up for world
	cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection)); // Define right for camera
	cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight)); // Define up for camera
	cameraFront = glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)); // 1 unit back from lens
}

/*Define getTarget Function to return te position vector the camera is pointing towards*/
glm::vec3 getTarget() {
	if (isPanning) {
		target = cameraPosition + cameraFront;
	}
	return target; 
};

/*Define TransformCamera function*/
void TransformCamera() {
	/*Pan camera with Left-Alt plus MMB*/
	if (keys[GLFW_KEY_LEFT_ALT] && mouseButtons[GLFW_MOUSE_BUTTON_MIDDLE]) { 
		isPanning = true;
	} else {
		isPanning = false;
	}

	/*Orbit camera with Left-Alt plus LMB*/
	if (keys[GLFW_KEY_LEFT_ALT] && mouseButtons[GLFW_MOUSE_BUTTON_LEFT]) { 
		isOrbiting = true;
	} else {
		isOrbiting = false;
	}

	/*Reset Camera with F key*/
	if (keys[GLFW_KEY_F]) { 
		initCamera();
	}
};
