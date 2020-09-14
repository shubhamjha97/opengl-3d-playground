#include "objLoader.h"

bool Object::loadOBJ(
	const char * path, 
	vector<glm::vec3> & out_vertices, 
	vector<glm::vec3> & out_normals,
	vector<string> & color_material)
{
	vector< unsigned int > vertexIndices, normalIndices;
	vector< glm::vec3 > temp_vertices;
	vector< glm::vec3 > temp_normals;
	char color_code[25] = "Default\0";
	FILE * file = fopen(path, "r");
	if( file == NULL ){
	    printf("Impossible to open the file !\n");
	    return false;
	}
	while( 1 )
	{

	    char lineHeader[256];
	    // read the first word of the line
	    int res = fscanf(file, "%s", lineHeader);
	    if (res == EOF)
	        break; // EOF = End Of File. Quit the loop.

	    // else : parse lineHeader
	    else
	    {
	    	if ( strcmp( lineHeader, "v" ) == 0 )
	    	{
	    	    glm::vec3 vertex;
	    	    fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
	    	    temp_vertices.push_back(vertex);
	    	}
	    	else if ( strcmp( lineHeader, "usemtl" ) == 0 )
	    	{
	    		fscanf(file, "%s\n", color_code);
	    	}
	    	else if ( strcmp( lineHeader, "vn" ) == 0 )
	    	{
	    	    glm::vec3 normal;
	    	    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
	    	    temp_normals.push_back(normal);    
	    	}
	    	else if ( strcmp( lineHeader, "f" ) == 0 )
	    	{
	    		color_material.push_back(color_code);
	    	    string vertex1, vertex2, vertex3;
	    	    unsigned int vertexIndex[3], normalIndex[3], random[3];
	    	    int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
	    	    if (matches != 6){
	    	        printf("File can't be read by parser\n");
	    	        return false;
	    	    }
	    	    vertexIndices.push_back(vertexIndex[0]);
	    	    vertexIndices.push_back(vertexIndex[1]);
	    	    vertexIndices.push_back(vertexIndex[2]);

	    	    
	    	    normalIndices.push_back(normalIndex[0]);
	    	    normalIndices.push_back(normalIndex[1]);
	    	    normalIndices.push_back(normalIndex[2]);

	    	}
	    }
	}
    for( unsigned int i=0; i<vertexIndices.size(); i++ )
    {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		// cout << normal.x << endl;
		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_normals .push_back(normal);
	
	}
	fclose(file);
	return true;
}

void Object::drawOBJ(vector< glm::vec3 > vertices, vector< glm::vec3 > normals, vector< string > colors, map<string, Color> colorMap, double x, double y, double z, double angle=0, double rx=0, double ry=0, double rz=0, double sx=1, double sy=1, double sz=1)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angle, rx, ry, rz);
	glTranslatef(0, 0, 0);
	glScalef(sx, sy, sz);
	glBegin(GL_TRIANGLES);
	for(int i=0;i<vertices.size();i+=3)
	{
		glColor3f(colorMap[colors[i/3]].r,colorMap[colors[i/3]].g,colorMap[colors[i/3]].b);
		glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		glVertex3f(vertices[i].x, vertices[i+0].y, vertices[i+0].z);
		glVertex3f(vertices[i+1].x, vertices[i+1].y, vertices[i+1].z);
		glVertex3f(vertices[i+2].x, vertices[i+2].y, vertices[i+2].z);
		
	}
	glEnd();
	glPopMatrix();
}

bool Object::loadColors(string filename, map<string, Color>& colorMap)
{
	ifstream cin(filename.c_str());
	string str, name, buffer;
	stringstream ss, st;
	Color tmp = {0, 0, 0};
	while(getline(cin, str)){
		ss.clear();
		ss << str;
		if (str[0] == 'n'){
			ss >> buffer >> name;
			getline(cin, str);
			getline(cin, str);
			ss.clear(); ss << str;
			ss >> buffer >> tmp.r >> tmp.g >> tmp.b;
			colorMap[name] = tmp;
			getline(cin, str);
			getline(cin, str);
		}
	}
	cin.close();
	return true;
}