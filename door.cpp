#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "getBMP.h"

static unsigned int texture[3];
int Xangle = 0;  int Yangle = 0; int Zangle = 0; int rotateDoor = 0; float door = 0.0; float maju = 10.0;

void loadTextures()
{
	imageFile* image[3];

	image[0] = getBMP("blacktexture.bmp");
	image[1] = getBMP("whitetexture.bmp");
	image[2] = getBMP("floortexture.bmp");

	if (image[0] == nullptr || image[1] == nullptr) {
		// Handle error: Failed to load BMP file
		// Print an error message, log, or exit the program
		std::cerr << "Error: Failed to load BMP file." << std::endl;
		return;
	}

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->width, image[1]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[2]->width, image[2]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[2]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void drawBlock(float x, float X, float y, float Y, float z, float Z, unsigned int tex, float st)
{
	glBindTexture(GL_TEXTURE_2D, tex);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);

	glTexCoord2f(0.0, 0.0); glVertex3f(x, y, z);
	glTexCoord2f(st, 0.0); glVertex3f(x, Y, z);
	glTexCoord2f(st, st); glVertex3f(x, Y, Z);
	glTexCoord2f(0.0, st); glVertex3f(x, y, Z);

	glTexCoord2f(0.0, 0.0); glVertex3f(x, y, z);
	glTexCoord2f(st, 0.0); glVertex3f(X, y, z);
	glTexCoord2f(st, st); glVertex3f(X, y, Z);
	glTexCoord2f(0.0, st); glVertex3f(x, y, Z);

	glTexCoord2f(0.0, 0.0); glVertex3f(x, y, z);
	glTexCoord2f(st, 0.0); glVertex3f(X, y, z);
	glTexCoord2f(st, st); glVertex3f(X, Y, z);
	glTexCoord2f(0.0, st); glVertex3f(x, Y, z);

	glTexCoord2f(0.0, 0.0); glVertex3f(x, y, Z);
	glTexCoord2f(st, 0.0); glVertex3f(X, y, Z);
	glTexCoord2f(st, st); glVertex3f(X, Y, Z);
	glTexCoord2f(0.0, st); glVertex3f(x, Y, Z);

	glTexCoord2f(0.0, 0.0); glVertex3f(x, Y, z);
	glTexCoord2f(st, 0.0); glVertex3f(X, Y, z);
	glTexCoord2f(st, st); glVertex3f(X, Y, Z);
	glTexCoord2f(0.0, st); glVertex3f(x, Y, Z);

	glTexCoord2f(0.0, 0.0); glVertex3f(X, y, z);
	glTexCoord2f(st, 0.0); glVertex3f(X, Y, z);
	glTexCoord2f(st, st); glVertex3f(X, Y, Z);
	glTexCoord2f(0.0, st); glVertex3f(X, y, Z);

	glEnd();
}
void drawLine(float x, float X, float y, float Y, float z, float Z)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_LINE_STRIP);
	glVertex3f(x, y, z);
	glVertex3f(x, Y, z);
	glVertex3f(X, Y, z);
	glVertex3f(X, y, z);
	glVertex3f(x, y, z);

	glVertex3f(x, y, Z);
	glVertex3f(x, Y, Z);
	glVertex3f(X, Y, Z);
	glVertex3f(X, y, Z);
	glVertex3f(x, y, Z);

	glVertex3f(x, Y, z);
	glVertex3f(x, Y, Z);
	glVertex3f(X, Y, Z);
	glVertex3f(X, Y, z);
	glVertex3f(x, Y, z);

	glVertex3f(x, y, z);
	glVertex3f(x, y, Z);
	glVertex3f(X, y, Z);
	glVertex3f(X, y, z);
	glVertex3f(x, y, z);

	glVertex3f(x, y, z);
	glVertex3f(x, y, Z);
	glVertex3f(x, Y, Z);
	glVertex3f(x, Y, z);
	glVertex3f(x, y, z);

	glVertex3f(X, y, z);
	glVertex3f(X, y, Z);
	glVertex3f(X, Y, Z);
	glVertex3f(X, Y, z);
	glVertex3f(X, y, z);
	glEnd();
}

void drawDoorDetail(float x, float X, float y, float Y, float z, float Z)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_LINE_STRIP);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, Y, z);
	glVertex3f(X - 1, Y, z);
	glVertex3f(X - 1, y, z);

	glVertex3f(x + 1, y, Z);
	glVertex3f(x + 1, Y, Z);
	glVertex3f(X - 1, Y, Z);
	glVertex3f(X - 1, y, Z);
	glEnd();

	for (float i = 0.4; i < Y; i += 3.4)
	{
		glBegin(GL_LINE_STRIP);
		glVertex3f(x + 1, y + i, z);
		glVertex3f(X - 1, y + i, z);
		glVertex3f(x + 1, y + i, Z);
		glVertex3f(X - 1, y + i, Z);
		glEnd();
	}
}
// Drawing routine.
void drawScene(void)
{
	// Light property vectors that change during runtime.
	float lightDifAndSpec[] = { 1, 1, 1, 1.0 };
	float lightPos[] = { /*cos((M_PI / 180.0) * 60), sin((M_PI / 180.0) * 60)*/0.0, 0.0, 0.0 };

	// Light properties.
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 25.0, 100.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);

	glTranslatef(-1.0, -2.0, -maju);

	glRotatef(Xangle, 1.0, 0.0, 0.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Zangle, 0.0, 0.0, 1.0);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(100.0, 0.0); glVertex3f(-1000.0, 0, 1000.0);
	glTexCoord2f(100.0, 100.0); glVertex3f(-1000.0, 0, -1000.0);
	glTexCoord2f(0.0, 100.0); glVertex3f(1000.0, 0, -1000.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1000.0, 0, 1000.0);
	glEnd();

	drawBlock(-20.0, -4.0, 0.0, 25.0, 11.0, 12.5, texture[1], 100.0);
	drawBlock(8.0, 22.0, 0.0, 25.0, 11.0, 12.5, texture[1], 100.0);
	drawBlock(-4.0, 8.0, 18.01, 25.0, 11.0, 12.5, texture[1], 100.0);
	glColor3f(1.0, 1.0, 1.0);
	drawLine(-20.0, -4.0, 0.0, 25.0, 11.0, 12.501);
	drawLine(8.0, 22.0, 0.0, 25.0, 11.0, 12.501);
	drawLine(-4.0, 8.0, 18.03, 25.0, 11.0, 12.501);

	drawBlock(-4.0, 0.0, 0.0, 18.0, 11.2, 12.3, texture[0], 1.0);
	glColor3f(0.0, 0.0, 0.0);
	drawDoorDetail(-4.0, 0.0, 0.0, 18.0, 11.2, 12.3);
	glColor3f(1.0, 1.0, 1.0);
	drawLine(-4.0, 0.0, 0.0, 18.0, 11.2, 12.301);

	glTranslatef(-door, 0.0, door);
	glRotatef(rotateDoor, 0.0, -1.0, 0.0);
	drawBlock(0.0, 8.0, 0.0, 18.0, 11.2, 12.3, texture[0], 1.0);
	glColor3f(1.0, 1.0, 1.0);
	drawDoorDetail(0.0, 8.0, 0.0, 18.0, 11.2, 12.301);
	glColor3f(1.0, 1.0, 1.0);
	drawLine(0.0, 8.0, 0.0, 18.0, 11.2, 12.301);

	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	// Turn on OpenGL lighting.
	glEnable(GL_LIGHTING);

	// Light property vectors that are constant.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float globAmb[] = { 0.7,0.7, 0.7, 1.0 };

	// Light properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);

	glEnable(GL_LIGHT0); // Enable particular light source.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

	// Material property vectors.
	float matAmbAndDif[] = { 1.0, 1.0, 1.0, 1.0 };
	float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float matShine[] = { 50.0 };

	// Material properties.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	// Create texture ids.
	glGenTextures(2, texture);

	// Load external textures.
	loadTextures();

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Turn on OpenGL texturing.
	glEnable(GL_TEXTURE_2D);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, 1.0, 1.0, 1000.0);
	//glFrustum(-3.0, 3.0, -2.0, 3.0, 1.0, 25.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case ' ':
		if (rotateDoor == 0) rotateDoor = 95, door = -5;
		else rotateDoor = 0, door = 0;
		glutPostRedisplay();
		break;
	case 'x':
		Xangle += 45;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 45;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 45;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'r':
		Xangle = 0; Yangle = 0; Zangle = 0; maju = 10.0;
		glutPostRedisplay();
		break;
	case 'w':
		maju--;
		glutPostRedisplay();
		break;
	case 's':
		maju++;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void consoleText()
{
	std::cout << "\nTekan x untuk memutar sumbu X\n";
	std::cout << "Tekan y untuk memutar sumbu Y\n";
	std::cout << "Tekan z untuk memutar sumbu Z\n";
	std::cout << "Tekan r untuk mengatur ulang\n";
	std::cout << "Tekan w untuk maju\n";
	std::cout << "Tekan s untuk mundur\n";
	std::cout << "Tekan spasi untuk membuka pintu\n";
}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TugasAkhirGrafkom.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	consoleText();

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}