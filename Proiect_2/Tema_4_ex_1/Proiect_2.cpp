#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "SOIL.h"

boolean fscreen = false;
boolean checkJump = false;
boolean checkCap = false;
boolean CheckKey[256];
boolean valid;

GLuint startList;

//CAMERA
float angle = 0;
float lx = 0, lz = -1;
float x = 0.0f, y = 1, z = 5.0f;
float g = -100;
GLuint textureID[20];

GLdouble platformPoz[] = {1,2,3,4
};

void LoadTexture(void)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textureID[1] = SOIL_load_OGL_texture("tree.jpg", 0, false, 0);
	textureID[2] = SOIL_load_OGL_texture("pamant.jpg", 0, false, 0);
	textureID[3] = SOIL_load_OGL_texture("wall.jpg", 0, false, 0);
	textureID[4] = SOIL_load_OGL_texture("road_2.jpg", 0, false, 0);
}

void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

void generate(void) {
	GLUquadric *objS = gluNewQuadric();

	startList = glGenLists(3);

	//Sfera
	gluQuadricDrawStyle(objS, GLU_FILL);
	gluQuadricNormals(objS, GLU_SMOOTH);
	gluQuadricTexture(objS, GL_TRUE);
	glNewList(startList, GL_COMPILE);
		gluSphere(objS, 3, 15, 10);
	glEndList();

	//Disk
	gluQuadricDrawStyle(objS, GLU_FILL);
	gluQuadricNormals(objS, GLU_SMOOTH);
	gluQuadricTexture(objS, GL_TRUE);
	glNewList(startList + 1, GL_COMPILE);
		gluDisk(objS, 0, 1.0, 20, 20);
	glEndList();
	//Stalpi
	gluQuadricDrawStyle(objS, GLU_FILL);
	gluQuadricNormals(objS, GLU_SMOOTH);
	gluQuadricTexture(objS, GL_TRUE);
	glNewList(startList + 2, GL_COMPILE);
		gluCylinder(objS, 2, 2, 15, 20, 20);
	glEndList();
	//Trunchi
	gluQuadricDrawStyle(objS, GLU_FILL);
	gluQuadricNormals(objS, GLU_SMOOTH);
	gluQuadricTexture(objS, GL_TRUE);
	glNewList(startList + 3, GL_COMPILE);
		gluCylinder(objS, 1, 0.6, 7, 20, 20);
	glEndList();
	//Ramura 1
	gluQuadricDrawStyle(objS, GLU_FILL);
	gluQuadricNormals(objS, GLU_SMOOTH);
	gluQuadricTexture(objS, GL_TRUE);
	glNewList(startList + 4, GL_COMPILE);
		gluCylinder(objS, 0.6, 0, 10, 20, 20);
	glEndList();

	//Ramura 2
	gluQuadricDrawStyle(objS, GLU_FILL);
	gluQuadricNormals(objS, GLU_SMOOTH);
	gluQuadricTexture(objS, GL_TRUE);
	glNewList(startList + 5, GL_COMPILE);
		gluCylinder(objS, 0.25, 0, 5, 20, 20);
	glEndList();
}

void init(void)
{
	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };
	
	GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_FOG);
	{
		GLfloat fogColor[4] = { 0.5, 0.5, 0.5, 1.0 };

		glFogi(GL_FOG_MODE, GL_EXP);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.03);
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		glFogf(GL_FOG_START, 1.0);
		glFogf(GL_FOG_END, 5.0);
	}
	glClearColor(0.5, 0.5, 0.5, 1.0);
}
void drawWalls(void) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID[3]);

	glPushMatrix();
	//INTRARI
	glTranslated(15, 10, 195);
	glRotated(90, 1, 0, 0);
	glCallList(startList + 2);

	glTranslated(-30, 0, 0);
	glCallList(startList + 2);

	glTranslated(0, -390, 0);
	glCallList(startList + 2);

	glTranslated(30, 0, 0);
	glCallList(startList + 2);

	//COLTURI
	glTranslated(180, 0, 0);
	glCallList(startList + 2);

	glTranslated(-390, 0, 0);
	glCallList(startList + 2);

	glTranslated(0, 390, 0);
	glCallList(startList + 2);

	glTranslated(390, 0, 0);
	glCallList(startList + 2);
	glPopMatrix();
	glBegin(GL_QUADS);
	glRotated(90, 1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-15, -2.9, -195);
	glTexCoord2f(1.0, 0.0); glVertex3f(-195, -2.9, -195);
	glTexCoord2f(0.0, 1.0); glVertex3f(-195, 9, -195);
	glTexCoord2f(1.0, 1.0); glVertex3f(-15, 9, -195);
	glEnd();
	glBegin(GL_QUADS);
	glRotated(90, 1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-195, -2.9, -195);
	glTexCoord2f(1.0, 0.0); glVertex3f(-195, -2.9, 195);
	glTexCoord2f(0.0, 1.0); glVertex3f(-195, 9, 195);
	glTexCoord2f(1.0, 1.0); glVertex3f(-195, 9, -195);
	glEnd();
	glBegin(GL_QUADS);
	glRotated(90, 1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-15, -2.9, 195);
	glTexCoord2f(1.0, 0.0); glVertex3f(-195, -2.9, 195);
	glTexCoord2f(0.0, 1.0); glVertex3f(-195, 9, 195);
	glTexCoord2f(1.0, 1.0); glVertex3f(-15, 9, 195);
	glEnd();
	glBegin(GL_QUADS);
	glRotated(90, 1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(15, -2.9, -195);
	glTexCoord2f(1.0, 0.0); glVertex3f(195, -2.9, -195);
	glTexCoord2f(0.0, 1.0); glVertex3f(195, 9, -195);
	glTexCoord2f(1.0, 1.0); glVertex3f(15, 9, -195);
	glEnd();
	glBegin(GL_QUADS);
	glRotated(90, 1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(195, -2.9, -195);
	glTexCoord2f(1.0, 0.0); glVertex3f(195, -2.9, 195);
	glTexCoord2f(0.0, 1.0); glVertex3f(195, 9, 195);
	glTexCoord2f(1.0, 1.0); glVertex3f(195, 9, -195);
	glEnd();
	glBegin(GL_QUADS);
	glRotated(90, 1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(15, -2.9, 195);
	glTexCoord2f(1.0, 0.0); glVertex3f(195, -2.9, 195);
	glTexCoord2f(0.0, 1.0); glVertex3f(195, 9, 195);
	glTexCoord2f(1.0, 1.0); glVertex3f(15, 9, 195);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void drawTree(void) {
	glEnable(GL_TEXTURE_2D);
	//Draw copacel
	glPushMatrix();
	glTranslatef(1, 0, 1);
	glShadeModel(GL_SMOOTH);
	//Trunchi
	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	glRotated(270, 1, 0, 0);
	glTranslated(0, 0, -3);
	glCallList(startList + 3);
	glTranslated(0, 0, 7);
	//Ramura medie -1
	glCallList(startList + 4);
	//Ramuri mici
	glTranslated(0, 0, 3);
	glRotated(40, 1, 0, 0);
	glCallList(startList + 5);
	glRotated(120, 0, 1, 1);
	glCallList(startList + 5);
	glRotated(120, 0, 1, 1);
	glCallList(startList + 5);
	//Revenire la punctul initial
	glRotated(120, 0, 1, 1); glRotated(40, -1, 0, 0); glTranslated(0, 0, -3);

	//Ramura medie-2
	glRotated(40, 1, 0, 0);
	glCallList(startList + 4);
	//Ramuri mici
	glTranslated(0, 0, 3);
	glRotated(40, 1, 0, 0);
	glCallList(startList + 5);
	glRotated(120, 0, 1, 1);
	glCallList(startList + 5);
	glRotated(120, 0, 1, 1);
	glCallList(startList + 5);
	//Revenire la punctul initial
	glRotated(120, 0, 1, 1); glRotated(40, -1, 0, 0); glTranslated(0, 0, -3);

	//Ramura medie-3
	glRotated(120, 0, 1, 1);
	glCallList(startList + 4);
	//Ramuri mici
	glTranslated(0, 0, 3);
	glRotated(40, 1, 0, 0);
	glCallList(startList + 5);
	glRotated(120, 0, 1, 1);
	glCallList(startList + 5);
	glRotated(120, 0, 1, 1);
	glCallList(startList + 5);
	//Revenire la punctul initial
	glRotated(120, 0, 1, 1); glRotated(40, -1, 0, 0); glTranslated(0, 0, -3);
	//Ramura medie-4
	glRotated(120, 0, 1, 1);
	glCallList(startList + 4);
	//Ramuri mici
	glTranslated(0, 0, 3);
	glRotated(40, 1, 0, 0);
	glCallList(startList + 5);
	glRotated(120, 0, 1, 1);
	glCallList(startList + 5);
	glRotated(120, 0, 1, 1);
	glCallList(startList + 5);
	//Revenire la punctul initial
	glRotated(120, 0, 1, 1); glRotated(40, -1, 0, 0); glTranslated(0, 0, -3);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera

	GLfloat light_position[] = { x, 0, z, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	gluLookAt(x, 1, z,
		x + lx, 1 ,z + lz,
		0.0f, 1, 0.0f);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, textureID[2]);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0.0);
	glVertex3f(-200.0f, -3.0f, -200.0f);
	glVertex3f(-200.0f, -3.0f, 200.0f);
	glVertex3f(200.0f, -3.0f, 200.0f);
	glVertex3f(200.0f, -3.0f, -200.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glBindTexture(GL_TEXTURE_2D, textureID[4]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-15, -2.9, -200);
		glTexCoord2f(0.0, 1.0); glVertex3f(-15, -2.9, 200.0f);
		glTexCoord2f(1.0, 1.0); glVertex3f(15, -2.9, 200.0f);
		glTexCoord2f(1.0, 0.0); glVertex3f(15, -2.9, -200.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	drawWalls();
	for (int i = 1; i < 10; i++)
		for (int j = 1; j < 20; j++) {
			glPushMatrix();
			glTranslatef(-205 + i*20.0, 0, -190 + j * 20.0);
			drawTree();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(205 - i * 20.0, 0, 190 - j * 20.0);
			drawTree();
			glPopMatrix();
		}

	
	
	glutSwapBuffers();
	glFlush();
}

void movement() {

	//LEFT
	if (CheckKey['a']) {
		angle -= 0.01;
		lx = sin(angle);
		lz = -cos(angle);
	}
	//RIGHT
	if (CheckKey['d']) {

		angle += 0.01;
		lx = sin(angle);
		lz = -cos(angle);
	}
	//FRONT
	if (CheckKey['w']) {
		x += lx * 0.3;
		z += lz * 0.3;
	}

	if (CheckKey['s']) {
		x -= lx * 0.3;
		z -= lz * 0.3;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int xx, int yy){
	CheckKey[tolower(key)] = true;
	//FULLSCREEN
	if (CheckKey['f'])
		if (!fscreen) {
			glutFullScreen();
			fscreen = true;
		}
		else {
			glutPositionWindow(0, 0);
			glutReshapeWindow(1920, 1080);
			fscreen = false;
		}
	if (CheckKey[27]) {
		exit(0);
	}
	glutPostRedisplay();
}
void keyboardUp(unsigned char key, int xx, int yy){
	CheckKey[tolower(key)] = false;
}
void mouseFunc(int button, int state, int xx, int yy) {
	if (button== GLUT_LEFT_BUTTON &&state == GLUT_UP) {
		lx = sin(angle);
		lz = -cos(angle);
		valid = false;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			valid = true;
	}
}

void mouseMotion(int xx,int yy){
	if (valid) {
		lx = sin(angle) + 0.01*(xx - 960);
		lz = -cos(angle) + 0.01*(yy - 1080);

	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Scena 3D padure");
	init();
	LoadTexture();
	generate();
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIdleFunc(movement);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);

	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotion);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 1;
}

