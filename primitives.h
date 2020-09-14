#ifndef PRIMITIVES
#define PRIMITIVES
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>
#include <glm/glm.hpp>
#include "primitive_structs.h"

using namespace std;

class Primitives
{
/* Class for drawing Primitive 3D structures using OpenGL such as Sphere, Cube, Cylinder/Cone, and Cuboid */
public:
	/* Function to draw Sphere
	
	Parameters:
	----------
	d : struct sphere_d
		struct holding parameters for drawing a sphere such as radius, center etc.
	*/
	void Sphere(sphere_d d);
	
	/* Function to draw Cube
	
	Parameters:
	----------
	d : struct cube_d
		struct holding parameters for cube a sphere such as size, center etc.
	*/
	void Cube(cube_d d);

	/* Function to draw Cylinder or Cone
	
	Parameters:
	----------
	d : struct cylinder_d
		struct holding parameters for drawing a cylinder such as height, radius_top, radius_bottom etc.
	*/
	void Cylinder(cylinder_d d);

	/* Function to draw Cuboid
	
	Parameters:
	----------
	d : struct cuboid_d
		struct holding parameters for drawing a Cuboid such as Corner Coordinates, length, breadth and height

	wire : boolean
		if true, draw wireframe and if false do not draw the wireframe for the cuboid
	*/
	void Cuboid(cuboid_d d, bool wire);
};
#endif