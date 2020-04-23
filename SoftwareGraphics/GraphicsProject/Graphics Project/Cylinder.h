#include <GLEW/glew.h>
#include <glm/gtc/matrix_transform.hpp>

class Cylinder {

public:
	/*cylinderVertices array, 8 values * 65 points * 2 circles = 1040*/
	GLfloat cylinderVertices[1040];
	/*Define element indices array for cylinder*/
	GLubyte cylinderIndices[130];

	/*roofVertices array for roof of object (65 points * 8 values) + (1 pt * 8 values) = 528*/
	GLfloat roofVertices[528];
	/*Indices array for roof is 64 points + center point*/
	GLubyte roofIndices[66];

	/*Variables for circular objects*/
	GLfloat cylinderVerticlePoint = 65.0f;		// used to calculate u value
	GLfloat uVerticlePoint = 1.0f / 65.0f;
	GLfloat cylinderRadius = 0.5f;				// Radius for cylinder
	GLfloat cylinderRoofRadius = 0.7f;			// Radius for roof
	GLfloat incrementAngle = 360.0f / 64.0f;	// Increment around circle (one less than count so that the ends touch)
	
	/*Set cylinderVertices*/
	void cylinder_coordinates() {
		for (int i = 0; i < 1040; i++) {
			GLfloat currentAngle = glm::radians(incrementAngle * (GLfloat(i) / 16));	// Current angle is i / 16 multiplied by increment
			GLfloat yCoordinate = 0.0f;													// set y coordinate to 0.0 for first vertice
			GLfloat vCoordinate = 1.0f;													// set v coordinate to 1.0 for next vertice
			if (i > 0) {
				cylinderVerticlePoint--;
			}
			for (int j = 0; j < 2; j++) {
				cylinderVertices[i] = cylinderRadius * cosf(currentAngle);				// x coordinate is cosine of current angle * radius
				i++;
				cylinderVertices[i] = yCoordinate;										// y coordinate is bottom first, top second time
				i++;
				cylinderVertices[i] = cylinderRadius * sinf(currentAngle);				// z coordinate is sine of current angle * radius
				i++;
				cylinderVertices[i] = cylinderVerticlePoint * uVerticlePoint;			// u value based on rotation around circle
				i++;
				cylinderVertices[i] = vCoordinate;										// v value is bottom first, top second time
				i++;
				cylinderVertices[i] = 0.0f;												// normal x value
				i++;
				cylinderVertices[i] = 0.0f;												// normal y value
				i++;
				cylinderVertices[i] = 1.0f;												// normal z value
				if (j == 0) {
					i++;
				}
				yCoordinate = 2.0f;														// set y coordinate to 2.0 for next vertice
				vCoordinate = 0.0f;														// set v coordinate to 0.0 for next vertice
			}
		}
	}

	/*Set cylinderIndicies*/
	void cylinder_indices() {
		for (int i = 0; i < 130; i++) {
			cylinderIndices[i] = i;
		};
	}

	/*Set roofVertices*/
	void cylinder_roof_coordinates() {
		roofVertices[0] = 0.0f;			// x of triangle fan center point
		roofVertices[1] = 2.5f;			// y of triangle fan center point
		roofVertices[2] = 0.0f;			// z of triangle fan center point
		roofVertices[3] = 0.5f;			// u of triangle fan center point
		roofVertices[4] = 0.5f;			// v of triangle fan center point
		roofVertices[5] = 0.0f;			// normal x of triangle fan center point
		roofVertices[6] = 0.0f;			// normal y of triangle fan center point
		roofVertices[7] = 1.0f;			// normal z of triangle fan center point

		for (int i = 8; i < 528; i++) {
			GLfloat currentAngle = glm::radians(incrementAngle * (GLfloat(i) / 8 - 1));	// Current angle is i / 8 - 1 multiplied by increment
			roofVertices[i] = cylinderRoofRadius * cosf(currentAngle);					// x coordinate is cosine of current angle * radius
			i++;
			roofVertices[i] = 1.9f;														// y coordinate is always 0.9
			i++;
			roofVertices[i] = cylinderRoofRadius * sinf(currentAngle);					// z coordinate is sine of current angle * radius
			i++;
			roofVertices[i] = 0.5f + (cylinderRoofRadius * cosf(currentAngle));			// u coordinate is middle of u + cosine of current angle * radius
			i++;
			roofVertices[i] = 0.5f + (cylinderRoofRadius * sinf(currentAngle));			// v coordinate is middle of v + sine of current angle * radius
			i++;
			roofVertices[i] = 0.0f;														// normal x value
			i++;
			roofVertices[i] = 0.0f;														// normal y value
			i++;
			roofVertices[i] = 1.0f;														// normal z value
		}
	}

	/*Set roofIndicies*/
	void cylinder_roof_indices() {
		for (int i = 0; i < 66; i++) {
			roofIndices[i] = i;
		}
	}

	Cylinder() {
		cylinder_coordinates();
		cylinder_indices();
		cylinder_roof_coordinates();
		cylinder_roof_indices();
	}
	
};