// All structs used throughout the programmes
#ifndef PRIMITIVE_STRUCTURES
#define PRIMITIVE_STRUCTURES

//Struct for storing the RGB color values for Faces
struct Color
{
	double r;
	double g;
	double b;
};

// Struct for storing RGB values for the wireframe of cuboid primitive
struct wireColor
{
	double r;
	double g;
	double b;
};

// Struct for parameters for drawing a cube
struct cube_d
{
	int size;
	double tx;
	double ty;
	double tz;
	double rx;
	double ry;
	double rz;
	double theta;
};

// Struct for parameters for drawing a cylinder
struct cylinder_d
{
	double height;
	double rad_t;
	double rad_b;
	double tx;
	double ty;
	double tz;
	double rx;
	double ry;
	double rz;
	double theta;
};

// Struct for parameters for drawing a sphere
struct sphere_d
{
	double radius;
	double tx;
	double ty;
	double tz;
};


// Struct for parameters for drawing a cuboid
struct cuboid_d
{
	double x_corner;
	double y_corner;
	double z_corner;
	double length;
	double width;
	double height;
};

extern Color RGB;
extern wireColor RGB_wire;

#endif