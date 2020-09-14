#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

float angle=0.0;
float lx=0.0f,lz=-1.0f;
float xinit=0.0f,zinit=0.0f;
int px=0, py=0, pz=0;
int quad_index;
struct Quad
{
	int x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	float r, g, b;
};Quad Q[100];

struct QuadStat
{
	int state;
	int total;
}QS;



void addNode(int x, int y, int z)
{
	QS.state++;
	if(QS.state > 4)
	{
		QS.state = 1;
	}
	int state = QS.state;
	if(state == 1)											{ quad_index = ++QS.total;}	
	if(state == 1) 											{ Q[quad_index].x1 = x; Q[quad_index].y1 = y; Q[quad_index].z1 = z; }
	if(state == 1 || state == 2) 							{ Q[quad_index].x2 = x; Q[quad_index].y2 = y; Q[quad_index].z2 = z; }
	if(state == 1 || state == 2 || state == 3) 				{ Q[quad_index].x3 = x; Q[quad_index].y3 = y; Q[quad_index].z3 = z; }
	if(state == 1 || state == 2 || state == 3 || state == 4){ Q[quad_index].x4 = x; Q[quad_index].y4 = y; Q[quad_index].z4 = z; }
}

void drawQuads()
{
	for(int i=0;i<QS.total+1;i++)
	{
		glBegin(GL_QUADS);
		glColor3f(Q[i].r, Q[i].g, Q[i].b);
		glVertex3f(Q[i].x1, Q[i].y1, Q[i].z1);
		glVertex3f(Q[i].x2, Q[i].y2, Q[i].z2);
		glVertex3f(Q[i].x3, Q[i].y3, Q[i].z3);
		glVertex3f(Q[i].x4, Q[i].y4, Q[i].z4);
		glEnd();
		glFlush();
	}
}

void theCube()
{
	glPushMatrix();
	if(py == 0)
	{
		glColor3f(1,1,1);
	}else
	{
		glColor3f(0.5,0.5,0.5);
	}
	glTranslatef(px, py, pz);
	glutSolidCube(0.4);
	glColor3f(0,0,0);
	glutWireCube(0.4);
	glPopMatrix();
}

void keyboard(unsigned char key, int x, int y)
{
	if(key=='w'){pz-=1;}
	if(key=='s'){pz+=1;}
	if(key=='a'){px-=1;}
	if(key=='d'){px+=1;}
	if(key=='q'){py+=1;}
	if(key=='z'){py-=1;}
	if(key==32){addNode(px, py, pz); cout << "node added at -> " << px << ' ' << py << ' ' << pz << endl;}
	if(key == 'r'){Q[quad_index].r = 1; Q[quad_index].g=0; Q[quad_index].b=0;}
	if(key == 'g'){Q[quad_index].r = 0; Q[quad_index].g=1; Q[quad_index].b=0;}
	if(key == 'b'){Q[quad_index].r = 0; Q[quad_index].g=0; Q[quad_index].b=1;}

	glutPostRedisplay();
}

void drawGrid(int n){
	int i;
    for(i=0; i<2*n; i++)
    {
        glPushMatrix();
        if(i<n) glTranslatef(0, 0, (float)i);
       if(i>=n)
        {
            glTranslatef((float)(i-n), 0, 0);
            glRotatef(-90, 0, 1, 0);
        }
        glBegin(GL_LINES);
        glColor3f(0.1,1,0.3);
        glLineWidth(1);
        glVertex3f(0, 0, 0);
        glVertex3f(n-1, 0, 0);
        glEnd();
        glPopMatrix();
    }
}

void cameraMovementKeys(int key, int xx, int yy) {

	float fraction = 0.5f;
	cout << "key -> " << key << endl; 
	switch (key) {
		case 100 :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 102 :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 101 :
			xinit += lx * fraction;
			zinit += lz * fraction;
			break;
		case 103 :
			xinit -= lx * fraction;
			zinit -= lz * fraction;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(xinit, 1.0f, zinit,
			xinit+lx, 1.0f,  zinit+lz,
			0.0f, 1.0f,  0.0f);

	glTranslatef(-35,4,-125);
	glRotatef(40,1,1,0);

	
	drawGrid(50);
	drawQuads();
	theCube();
	glutSwapBuffers();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35,1.0f,0.1f,1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	
	glClearColor(0.2,0.2,0.2,1);
}

int main(int argc, char **argv)
{
	QS = (QuadStat){0, -1};
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(1920,1080);
	glutCreateWindow("");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(cameraMovementKeys);
	init();
	glutMainLoop();
	return 0;
}