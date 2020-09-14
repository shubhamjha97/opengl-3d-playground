#define GL_GLEXT_PROTOTYPES
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>
#include <glm/glm.hpp>
#include "objLoader.h"
#include "primitive_structs.h"
#include "primitives.h"

using namespace std;

Object* obj;		// Instace of Object Class for handling blender models
Primitives* pr;		// Instance of Primitives Class for drawing 3D primitives

Color RGB;			// Face Color
wireColor RGB_wire;	// WireFrame Color

double dimensions = 61;						// Dimensions of the scene
double cam_height = 5;						// Initial height of the camera - y-axis
double cam_horizontal = dimensions/2;		// x-axis position of the camera
double cam_distance = dimensions+30;		// z-axis position of the camera
double angle=0.0;							// camera rotation angles
double lx=0.0f,lz=-1.0f;
double xinit=0.0f,zinit=0.0f;
double trans_y = 0.0;
double swing_theta = 0.0;					// swing rotation angle
bool increment_swing_theta = true;			// increment or decrement angle
char order = 'w';
int merry_go_round_angle = -60;				// merry go rotation angle



// vectors for holding the vertices, normals, color string vector, and string to RGB colorMap

// MerrygoRound Lego bot
vector< glm::vec3 > vertices_lego_merrygo;
vector< glm::vec3 > normals_lego_merrygo;
vector< string > colors_lego_merrygo;
map<string, Color> colorMap_lego_merrygo;

// Entrance Gate
vector< glm::vec3 > vertices_gate;
vector< glm::vec3 > normals_gate;
vector< string > colors_gate;
map<string, Color> colorMap_gate;

// Cool Slide
vector< glm::vec3 > vertices_slide;
vector< glm::vec3 > normals_slide;
vector< string > colors_slide;
map<string, Color> colorMap_slide;

// MerryGo Round
vector< glm::vec3 > vertices_merrygo;
vector< glm::vec3 > normals_merrygo;
vector< string > colors_merrygo;
map<string, Color> colorMap_merrygo;


void redraw(void);

// keyboard key press events for camera pointing direction(lookup point) updates
void cameraMovementKeys(int key, int xx, int yy)
{
	double fraction = 0.5f;
	switch (key) {
		case 100 : //left arrow key press
			angle -= 0.03f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 102 :	//right arrow key press
			angle += 0.03f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 101 :	// top arrow key press
			xinit += lx * fraction;
			zinit += lz * fraction;
			break;
		case 103 :	// bottom arrow key press
			xinit -= lx * fraction;
			zinit -= lz * fraction;
			break;
	}
	glutPostRedisplay(); 	// redraw the OpenGl scene
}

// keyboard events for camera position updates
void keyboard(unsigned char key, int x, int y)
{

	if(key=='q'){cam_height+=0.4;}
	if(key=='z'){cam_height-=0.4;}
	if(key=='w'){cam_distance+=1;}
	if(key=='s'){cam_distance-=1;}
	if(key=='a'){cam_horizontal-=1;}
	if(key=='d'){cam_horizontal+=1;}
	glutPostRedisplay();
}

void drawBoundary(double dimensions)
{
	/* Draw bricks and the boundary of the park. Each brick is drawn using the
	Cuboid draw function. */
	RGB_wire = {0,0,0};
	int height = 5;
	while(height--)
	{
		// brick variables
		double brick_length = 2;
		double brick_breadth = 1;
		double brick_height = 1;
		int bricks = dimensions/brick_length;
		RGB = {.341, .050, .043};

		//draw wall at z=0;
		for(int i=0;i<bricks;i++)
		{
			double translation = (int)height%2==0?1:0;

			double layout_x = brick_length*i+translation;
			double layout_y = height+1;
			double layout_z = 0;
			cuboid_d top_row = {layout_x, layout_y, layout_z, brick_length, brick_breadth, brick_height};
			pr->Cuboid(top_row, true);
		}

		//draw wall at x=0
		for(int i=0;i<bricks;i++)
		{
			double translation = (int)height%2==0?0:1;
			double layout_x = 0;
			double layout_y = height+1;
			double layout_z = brick_length*i+translation;
			cuboid_d left_row = {layout_x, layout_y, layout_z, brick_breadth, brick_length, brick_height};
			pr->Cuboid(left_row, true);
		}

		//draw wall at z=dimensions
		for(int i=0;i<bricks;i++)
		{
			if(i<bricks/2-3 || i>bricks/2+2)
			{
				double translation = (int)height%2==0?0:1;

				double layout_x = brick_length*i+translation;
				double layout_y = height+1;
				double layout_z = dimensions-1;
				cuboid_d top_row = {layout_x, layout_y, layout_z, brick_length, brick_breadth, brick_height};
				pr->Cuboid(top_row, true);
			}
		}

		//draw wall at x=dimensions
		for(int i=0;i<bricks;i++)
		{
			double translation = (int)height%2==0?1:0;
			double layout_x = dimensions-1;
			double layout_y = height+1;
			double layout_z = brick_length*i+translation;
			cuboid_d left_row = {layout_x, layout_y, layout_z, brick_breadth, brick_length, brick_height};
			pr->Cuboid(left_row, true);
		}
	}

}

void drawTree(double x, double y, double z, double sx, double sy, double sz)
{
	/* Draw trees
		Tree = Tree Trunk + Tree Top
		Tree Trunk = Cylinder => Bottom Radius = Top Radius
		Tree Top = Cone => Top Radius = 0

		Parameters:
		----------
		x : double
			x position
		y : double
			y position
		z : double
			z position
		sx : double
			scaling in x axis
		sy : double
			scaling in y axis
		sz : double
			scaling in z axis
	*/
	glPushMatrix();
	cylinder_d top = {10, 0.8, 0.0, x, 14, z, 1, 0, 0, 90};
	cylinder_d trunk = {4, 0.2, 0.2, x, 4, z, 1, 0, 0, 90};
	glTranslatef(x, 0, z);
	glScalef(sx, sy, sz);
	glTranslatef(-x, 0, -z);
	RGB = {0.0, 0.6, 0.0};
	pr->Cylinder(top);
	RGB = {0.26, 0.13, 0.09};
	pr->Cylinder(trunk);
	glPopMatrix();
}

void drawSwing()
{
	// Draw an animating swing that actually swings
	// by rotating about the hinge point as the scene
	// rerenders each time

	RGB_wire = {0,0,0};
	RGB = {1,1,1};
	cylinder_d frame1 = {15, 0.2,0.2,dimensions-5, 15, dimensions-17, 1, 0, 0, 90};
	cylinder_d frame2 = {15, 0.2,0.2,dimensions-5, 15, dimensions-4, 1, 0, 0, 90};
	cylinder_d frame3 = {18, 0.2,0.2, dimensions-5, 15,dimensions-20, 0, 0, 0, 0};
	cylinder_d swing_cable1 = {12, 0.05,0.05,dimensions-5, 15, dimensions-12.5, 1, 0, 0, 90};
	cylinder_d swing_cable2 = {12, 0.05,0.05,dimensions-5, 15, dimensions-8.5, 1, 0, 0, 90};
	cuboid_d seat = {dimensions-6, 3, dimensions-13.5, 2, 6, 0.5};

	pr->Cylinder(frame1);
	pr->Cylinder(frame3);
	glPushMatrix();
	glTranslatef(+dimensions-5, 15, 10.5);
	glRotatef(swing_theta, 0, 0, 1);
	glTranslatef(-dimensions+5, -15, -10.5);
	RGB = {0.26,0.13,0.09};
	pr->Cuboid(seat, true);
	RGB = {1,1,1};
	pr->Cylinder(swing_cable1);
	pr->Cylinder(swing_cable2);
	glPopMatrix();
	pr->Cylinder(frame2);

}

void drawSlide(double x, double y, double z)
{
	/*
		draw a slide using OpenGL

		Parameters:
		----------
		x : double
			x position of the slide
		y : double
			y position of the slide
		z : double
			z position of the slide
	*/
	RGB = {0.7, 0.7, 0.7};
	double foot_frame_seperation = 3;
	double slide_slope_theta = 55;
	double slide_support_theta = 80;
	double height = 12;
	double foot_frame_length = height*sin(80*3.14/180);
	double platform_length = 1;
	double slide_length = foot_frame_length/sin(slide_slope_theta*3.14/180);
	double slide_pos = platform_length - 0.18 + foot_frame_length*(1/tan(slide_support_theta*3.14/180) + 1/tan(slide_slope_theta*3.14/180));
	cylinder_d foot_frame1 = {foot_frame_length, .1, .1, x, foot_frame_length+1, z, 1, 0, 0, 90};
	cylinder_d foot_frame2 = {foot_frame_length, .1, .1, x+foot_frame_seperation, foot_frame_length+1, z, 1, 0, 0, 90};
	glPushMatrix();
	glTranslatef(x+foot_frame_seperation/2, 1, z);
	glRotatef(90.0-slide_support_theta, 1, 0, 0);
	glTranslatef(-x-foot_frame_seperation/2, -1, -z);
	for(int i=1;i<foot_frame_length/2;i++)
	{
		double height = 2*i+1;
		cylinder_d foot_rest = {foot_frame_seperation, .1, .1, x, height, z, 0, 1, 0, 90};
		pr->Cylinder(foot_rest);
	}
	pr->Cylinder(foot_frame1);
	pr->Cylinder(foot_frame2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 3.3);
	cuboid_d platform = {x, foot_frame_length+0.965, z-1.2, foot_frame_seperation, 1, .2};
	pr->Cuboid(platform, true);
	glPopMatrix();
	glPushMatrix();
	cylinder_d platform_support1 = {height+2, 0.05, 0.05, x, height+3, z+2.1, 1, 0, 0, 90};
	cylinder_d platform_support2 = {height+2, 0.05, 0.05, x+foot_frame_seperation, height+3, z+2.1, 1, 0, 0, 90};
	cylinder_d platform_support3 = {height+2, 0.05, 0.05, x, height+3, z+2.1+platform_length, 1, 0, 0, 90};
	cylinder_d platform_support4 = {height+2, 0.05, 0.05, x+foot_frame_seperation, height+3, z+2.1+platform_length, 1, 0, 0, 90};
	cylinder_d platform_support_h1 = {platform_length+0.1, 0.05, 0.05, x, height+3, z+2.05, 0, 0, 0, 0};
	cylinder_d platform_support_h2 = {platform_length+0.1, 0.05, 0.05, x+foot_frame_seperation, height+3, z+2.05, 0, 0, 0, 0};
	pr->Cylinder(platform_support1);
	pr->Cylinder(platform_support2);
	pr->Cylinder(platform_support3);
	pr->Cylinder(platform_support4);
	pr->Cylinder(platform_support_h1);
	pr->Cylinder(platform_support_h2);

	cuboid_d slide = {x, slide_length+0.88, z+slide_pos, foot_frame_seperation, 0.1, slide_length};
	glTranslatef(x+foot_frame_seperation/2, 1, z+slide_pos);
	glRotatef(-90+slide_slope_theta, 1, 0, 0);
	glTranslatef(-x-foot_frame_seperation/2, -1, -z-slide_pos);
	pr->Cuboid(slide, true);
	glPopMatrix();
}
void drawSandCastle(double x, double y, double z)
{
	/*
		draw a sand castle using OpenGL

		Parameters:
		----------
		x : double
			x position of the slide
		y : double
			y position of the slide
		z : double
			z position of the slide
	*/
	double castle_l = 3;
	double castle_b = 1.8;
	double castle_h = 3;
	cylinder_d tower1 = {4, 0.2, 0.2, x, 5, z, 1, 0, 0, 90};
	cylinder_d tower2 = {4, 0.2, 0.2, x+castle_l, 5, z, 1, 0, 0, 90};
	cylinder_d tower3 = {4, 0.2, 0.2, x, 5, z+castle_b, 1, 0, 0, 90};
	cylinder_d tower4 = {4, 0.2, 0.2, x+castle_l, 5, z+castle_b, 1, 0, 0, 90};
	cylinder_d cone1 = {1, 0.3, 0.0, x, 5.8, z, 1, 0, 0, 90};
	cylinder_d cone2 = {1, 0.3, 0.0, x+castle_l, 5.8, z, 1, 0, 0, 90};
	cylinder_d cone3 = {1, 0.3, 0.0, x, 5.8, z+castle_b, 1, 0, 0, 90};
	cylinder_d cone4 = {1, 0.3, 0.0, x+castle_l, 5.8, z+castle_b, 1, 0, 0, 90};
	cuboid_d gate_pillar1 = {x+castle_l/2-.5, y+2, z+castle_b, 0.2,0.1,2};
	cuboid_d gate_pillar2 = {x+castle_l/2+.5, y+2, z+castle_b, 0.2,0.1,2};
	cuboid_d gate_pillar3 = {x+castle_l/2-.5, y+2+0.2, z+castle_b, 1.2, 0.1, 0.2};
	cuboid_d center_block = {x, y+3, z, castle_l, castle_b, castle_h};
	RGB_wire = {0.58, 0.47, 0.3};
	glPushMatrix();
	glTranslatef(x+castle_l/2, y+3, z+castle_h/2);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-x-castle_l/2, -y-3, -z-castle_h/2);
	pr->Cuboid(center_block, false);
	RGB = {0.26,0.13,0.09};
	RGB_wire = {0.26,0.13,0.09};
	pr->Cuboid(gate_pillar1, true);
	pr->Cuboid(gate_pillar2, true);
	pr->Cuboid(gate_pillar3, true);
	RGB = {0.58, 0.47, 0.3};
	pr->Cylinder(tower1);
	pr->Cylinder(tower2);
	pr->Cylinder(tower3);
	pr->Cylinder(tower4);
	RGB = {0.26,0.13,0.09};
	pr->Cylinder(cone1);
	pr->Cylinder(cone2);
	pr->Cylinder(cone3);
	pr->Cylinder(cone4);
	RGB = {1.0, 0.0, 0.0};
	sphere_d ball = {1, x+5, 2, z+5};
	pr->Sphere(ball);
	glPopMatrix();


}
void drawSandplayground()
{
	double corner_coord_x = 4;
	double corner_coord_y = 2;
	double corner_coord_z = 4;
	double l=30;
	double b=0.5;
	double h=corner_coord_y;
	double ratio = 2;
	cuboid_d wall1 = {corner_coord_x, corner_coord_y, corner_coord_z, l/ratio, b, h};
	cuboid_d wall2 = {corner_coord_x, corner_coord_y, corner_coord_z+b, b, l, h};
	cuboid_d wall3 = {corner_coord_x+b, corner_coord_y, corner_coord_z+l, l/ratio, b, h};
	cuboid_d wall4 = {corner_coord_x+l/ratio, corner_coord_y, corner_coord_z, b, l, h};
	cuboid_d sand = {corner_coord_x+b, 1, corner_coord_z+b, l/ratio-b, l-b, 1};
	pr->Cuboid(wall1, true);
	pr->Cuboid(wall2, true);
	pr->Cuboid(wall3, true);
	pr->Cuboid(wall4, true);
	RGB = {0.58, 0.47, 0.3};
	pr->Cuboid(sand, true);
	drawSandCastle(7, 1, l);
	drawSlide(corner_coord_x+8, 1, corner_coord_z+5);
}

void drawMonkeyBars()
{
	//left bars
	cylinder_d left1 = {9, 0.2, 0.2, 3, 9, dimensions-5, 1, 0, 0, 90 };
	cylinder_d left2 = {9, 0.2, 0.2, 3, 9, dimensions-8, 1, 0, 0, 90 };
	//right bars
	cylinder_d right1 = {9, 0.2, 0.2, 8, 9, dimensions-5, 1, 0, 0, 90 };
	cylinder_d right2 = {9, 0.2, 0.2, 8, 9, dimensions-8, 1, 0, 0, 90 };
	//top bars
	cylinder_d top1 = {8, 0.2, 0.2, 1.5, 9, dimensions-5, 0, 1, 0, 90 };
	cylinder_d top2 = {8, 0.2, 0.2, 1.5, 9, dimensions-8, 0, 1, 0, 90 };
	RGB = {1,1,1};

	pr->Cylinder(left1);
	pr->Cylinder(left2);
	pr->Cylinder(right1);
	pr->Cylinder(right2);
	pr->Cylinder(top1);
	pr->Cylinder(top2);
}
void drawPathWay()
{
	// draw the center parthway
	RGB = {0.4,0.4,0.4};
	glColor3f(RGB.r, RGB.g, RGB.b);
	cuboid_d path1 = {dimensions/2-4, .2, 0, 8, dimensions-1, 0.2};
	pr->Cuboid(path1, true);
}
void redraw()
{
	// redraw tge swing for animation and rerender the scene with
	// the updated swing angle
	if(increment_swing_theta)
	{
		swing_theta+=0.3;
		if(swing_theta>10)
		{
			increment_swing_theta = false;
		}
	}else
	{
		swing_theta-=0.3;
		if(swing_theta<-10)
		{
			increment_swing_theta = true;
		}
	}
	glutPostRedisplay();
}


void drawLand()
{
	// draw the grass ground for the playground
	RGB = {0.0, 0.3, 0.0};
	glColor3f(RGB.r, RGB.g, RGB.b);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-dimensions, 0.0, -dimensions);
	glVertex3f(-dimensions, 0.0, dimensions*2);
	glVertex3f(dimensions*2, 0.0, dimensions*2);
	glVertex3f(dimensions*2, 0.0, -dimensions);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(xinit, 4.0f, zinit,
		xinit+lx, 4.0f,  zinit+lz,
		0.0f, 1.0f,  0.0f);


	glTranslatef(-cam_horizontal,-cam_height,-cam_distance);
    RGB = {0, 1, 0};
	RGB = {0.7, 0.7, 0.7};
	glPushMatrix();
	glTranslatef(dimensions/2+10, 0, dimensions/2);
	glRotatef(merry_go_round_angle, 0, 1, 0);
	glTranslatef(-dimensions/2-10, 0, -dimensions/2);
	obj->drawOBJ(vertices_lego_merrygo, normals_lego_merrygo, colors_lego_merrygo, colorMap_lego_merrygo, dimensions/2+12, 1.3, dimensions/2+2, -45, 0, 1, 0, .7, 1, .7);
	glPopMatrix();
	obj->drawOBJ(vertices_gate, normals_gate, colors_gate, colorMap_gate, dimensions/2, -0.1, dimensions-1, 180, 0, 1, 0, .68, 1, .7);
	obj->drawOBJ(vertices_slide, normals_slide, colors_slide, colorMap_slide, dimensions-15, 0, 15, 180, 0, 1, 0, 1, 1.3, .8);
	obj->drawOBJ(vertices_merrygo, normals_merrygo, colors_merrygo, colorMap_merrygo, dimensions/2+10, .5, dimensions/2, merry_go_round_angle++, 0, 1, 0, 3,3,3);
	if(merry_go_round_angle > 360)
	{
		merry_go_round_angle-=360;
	}
	drawLand();
	drawBoundary(dimensions);
	drawMonkeyBars();
	drawSwing();
	drawTree(2.7, 0, 2.5, 1.3, 2, 1.3);
	drawTree(2, 0, 2, 1, 1, 1);
	drawTree(4, 0, 1.5, 1.1, 1.3, 1.1);
	drawTree(dimensions-5, 0, dimensions/2, 1.1, 1.3, 1.1);
	drawTree(dimensions-6, 0, dimensions/2-2, 1.3, 1.7, 1.3);
	drawTree(4, 0, 1.5, 1.1, 1.3, 1.1);
	drawTree(dimensions-5.5, 0, dimensions/2-3, 2, 2.5, 2);

	drawPathWay();
	drawSandplayground();

	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = {1.0f, 0.9f, 0.7f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {(GLfloat)dimensions+4.0f, (GLfloat)dimensions, -15, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {25.0f, 50.5f, 60.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glutSwapBuffers();
	redraw();
}


void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100,1920/1080,0.1f,1000);
	glViewport(0, 0, 1920, 1080);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE);
	glClearColor(0.529,0.808,0.980,1);
	RGB_wire = {0,0,0};
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	obj->loadColors("mtl/legoman.mtl", colorMap_lego_merrygo);
	obj->loadOBJ("obj/legoman.obj", vertices_lego_merrygo, normals_lego_merrygo, colors_lego_merrygo);
	obj->loadColors("mtl/gate.mtl", colorMap_gate);
	obj->loadOBJ("obj/gate.obj", vertices_gate, normals_gate, colors_gate);
	obj->loadColors("mtl/slide_baseless.mtl", colorMap_slide);
	obj->loadOBJ("obj/slide_baseless.obj", vertices_slide, normals_slide, colors_slide);
	obj->loadColors("mtl/merry_go_round.mtl", colorMap_merrygo);
	obj->loadOBJ("obj/merry_go_round.obj", vertices_merrygo, normals_merrygo, colors_merrygo);
	glutInitWindowSize(1920,1080);
	glutCreateWindow("");
	glutDisplayFunc(display);
	init();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(cameraMovementKeys);
	glutMainLoop();
	return 0;
}
