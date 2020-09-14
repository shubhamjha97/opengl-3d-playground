#ifndef COLOR_STRUCT_H
#define COLOR_STRUCT_H
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>
#include <glm/glm.hpp>
#include "primitive_structs.h"


using namespace std;


class Object
{
/* Class for handling blender generated obj and mtl files and 
drawing and rendering these models on the OpengGL scene */	
public:

	/* Function to read .obj file and parse vertices, normals and faces 
	from it. These vertices and normals are stored in the vector arrays as per
	the indexing used in the face vector
	
	Parameters:
	----------
	path: char*
		path for the obj file

	out_vertices : vector<gln::vec3>
		vector array to store the vertices

	out_normals : vector<glm::vec3>
		vector array to store the norrmals 

	color_material : vector<string>
		vector to store the string defining the color material to be used for each face

	*/
	bool loadOBJ(
		const char * path, 
		vector<glm::vec3> & out_vertices, 
		vector<glm::vec3> & out_normals,
		vector<string> & color_material);

	/* Function to Draw the blender object model using the loaded vertices and normal 
	vector arrays using openGL. The generated faces are all triangulated and the vertices and 
	normal arrays are presorted in the order of the faces they belong to

	Parameters:
	----------
	vertices : vector< glm::vec3 >
		vector that has the vertices stored for the object

	normals : vector< glm::vec3 >
		vector that has the normals store for the object

	colors : <vector <string> 
		vector that has the color string used for each face

	colorMap : map
		map between the color string and Color struct for setting the color of the faces
	*/
	void drawOBJ(
		vector< glm::vec3 > vertices, 
		vector< glm::vec3 > normals, 
		vector< string > colors, 
		map<string, Color> colorMap, 	
		double x, double y, double z, 
		double angle, double rx, double ry, double rz, 
		double sx, double sy, double sz);

	/* Function to read .mtl Material file and create a string to struct Color map 
	to be later referenced for coloring the faces of the blender generated model in
	the OpenGL scene

	Parameters:
	----------
	filename : string
		filename for the mtl material file

	colorMap : map
		Map for storing the color name string and the RGB struct contaiing the corresponding RGB values
	*/
	bool loadColors(string filename, map<string, Color> &colorMap);
};

#endif