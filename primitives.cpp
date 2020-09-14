#include "primitives.h"
void Primitives::Sphere(sphere_d d)
{
	glPushMatrix();
	glTranslatef(d.tx, d.ty, d.tz);
	glColor3f(RGB.r, RGB.g, RGB.b);
	glutSolidSphere(d.radius, 32, 32);
	glPopMatrix();
}
void Primitives::Cube(cube_d d)
{
	glPushMatrix();
	glTranslatef(d.tx, d.ty, d.tz);
	glRotatef(d.theta,d.rx, d.ry, d.rz );
	glColor3f(0,0.0,0.0);
	glLineWidth(3);
	glutWireCube(d.size);
	glColor3f(0.26,0.13,0.09);
	glutSolidCube(d.size);
	glLineWidth(1);
	glPopMatrix();
    // sawp buffers called because we are using double buffering 
}


void Primitives::Cylinder(cylinder_d d)
{
	glPushMatrix();
	glColor3f(RGB.r, RGB.g, RGB.b);
	glTranslatef(d.tx,d.ty,d.tz);
	glRotatef(d.theta, d.rx, d.ry, d.rz);
	gluCylinder(gluNewQuadric(), d.rad_b, d.rad_t, d.height, 100, 100);
	glPopMatrix();
}

void Primitives::Cuboid(cuboid_d d, bool wire = true)
{
	if(wire)
	{
		glColor3f(RGB_wire.r, RGB_wire.g, RGB_wire.b);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex3f(d.x_corner, d.y_corner, d.z_corner);
		glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner);

		glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner);
		glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner+d.width);

		glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner+d.width);
		glVertex3f(d.x_corner, d.y_corner, d.z_corner+d.width);

		glVertex3f(d.x_corner, d.y_corner, d.z_corner+d.width);
		glVertex3f(d.x_corner, d.y_corner, d.z_corner);

		glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner);
		glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner);

		glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner);
		glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner+d.width);

		glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner+d.width);
		glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner+d.width);

		glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner+d.width);
		glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner);

		glVertex3f(d.x_corner, d.y_corner, d.z_corner);
		glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner);

		glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner);
		glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner);

		glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner+d.width);
		glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner+d.width);

		glVertex3f(d.x_corner, d.y_corner, d.z_corner+d.width);
		glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner+d.width);
		glEnd();

	}
	glColor3f(RGB.r, RGB.g, RGB.b);
	glBegin(GL_QUADS);

	// top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(d.x_corner, d.y_corner, d.z_corner);
    glVertex3f(d.x_corner, d.y_corner, d.z_corner+d.width);
    glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner+d.width);
    glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner);
	
	//bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner);
    glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner+d.width);
    glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner+d.width);
    glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner);
	//front
	glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(d.x_corner, d.y_corner, d.z_corner+d.width);
    glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner+d.width);
    glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner+d.width);
    glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner+d.width);
 
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner+d.width);
    glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner+d.width);
    glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner);
    glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner);
 
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(d.x_corner+d.length, d.y_corner, d.z_corner);
    glVertex3f(d.x_corner+d.length, d.y_corner-d.height, d.z_corner);
    glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner);
    glVertex3f(d.x_corner, d.y_corner, d.z_corner);
 
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(d.x_corner, d.y_corner, d.z_corner);
    glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner);
    glVertex3f(d.x_corner, d.y_corner-d.height, d.z_corner+d.width);
    glVertex3f(d.x_corner, d.y_corner, d.z_corner+d.width);

    glEnd();
}