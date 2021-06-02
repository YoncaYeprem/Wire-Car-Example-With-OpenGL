#include <iostream>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

char key;

//Variable for rotating X axis
float xCoordinate = 0.0;
//Variable for rotating Y axis
float yCoordinate = 0.0;

//Variable for rotation speed
float speed = 2.0;
//Variable for normal rotation
float tireRotSpeed = 8.0;
//Variable for rotating operation
float forwardRot = 0.0;
//Variable for rotating right and left
float wheelRotation = 0.0;

#define PI 3.14159265358979324


void Menu(int value);
void display();
void keyboard(unsigned char, int, int);

void init()
{
	//Specify the red, green, blue, and alpha values used when the color buffers are cleared.
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Applies subsequent matrix operations to the projection matrix stack.
	glMatrixMode(GL_PROJECTION);
	//Specifies a viewing
	gluPerspective(45, 1, 0.1, 50);
	//Creates a viewing matrix derived from an eye point
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
	//Do depth comparisons and update the depth buffer.
	glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'd') {
		yCoordinate += speed;
	}
	if (key == 'a') {
		yCoordinate -= speed;
	}
	if (key == 'w') {
		xCoordinate += speed;
	}
	if (key == 's') {
		xCoordinate -= speed;
	}

	if (key == 'q') {
		forwardRot -= tireRotSpeed;
	}

	if (key == 'l') {
		if (wheelRotation < 45.0) {
			wheelRotation += speed;
		}
	}
	if (key == 'r') {
		if (wheelRotation > -45.0) {
			wheelRotation -= speed;
		}
	}
}



int main(int argc, char** argv) {

	glutInit(&argc, argv);
	//Display Modes.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//Set the window size
	glutInitWindowSize(650, 650);
	glutCreateWindow("Wire Car");

	//Add Menu Items
	int menu = glutCreateMenu(Menu);
	glutAddMenuEntry("Right", 1);
	glutAddMenuEntry("Left", 2);
	glutAddMenuEntry("Up", 3);
	glutAddMenuEntry("Front", 4);
	glutAddMenuEntry("Back", 5);
	glutCreateMenu(Menu);
	glutAddSubMenu("View", menu);

	glutAddMenuEntry("Exit", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);

	init();

	glutMainLoop();
}

void Menu(int value) {

	switch (value)
	{
	case 1:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(20, 1, 0.1, 60);
		gluLookAt(0, 0, 55, 0, 0, 0, 0, 1, 0);
		
		break;
	case 2:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(20, 1, 0.1, 60);
		gluLookAt(0, 0, -55, 0, 0, 0, 0, 1, 0);
		break;
	case 3:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, 1, 0.1, 60);
		gluLookAt(1, 30, 0, 0, 0, 0, 0, 1, 0);
		break;
	case 4:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(35, 1, 0.1, 60);
		gluLookAt(30, 0, 0, 0, 0, 0, 0, 1, 0);
		break;
	case 5:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(35, 1, 0.1, 60);
		gluLookAt(-30, 0, 0, 0, 0, 0, 0, 1, 0);
		break;
	case 6:
		exit(0);
		break;
	}

	glutPostRedisplay();
}


void car() {
	int i;
	float x=0.0;
	float y=0.0;
	float radius = 1.5;
	int numVertices = 100;

	//modelview matrix stack
	glMatrixMode(GL_MODELVIEW);
	//Replaces the current matrix with the identity matrix
	glLoadIdentity();
	//Set the color of car part
	glColor3f(0.796, 0.584, 0.741);
	//Rotate operations for key press
	glRotatef(yCoordinate, 0.0, 1.0, 0.0);
	glRotatef(xCoordinate, 1.0, 0.0, 0.0);
	glTranslatef(0, 0, 0);
	glScalef(1, 0.25, 0.5);
	glutWireCube(5);

	
	//Right Front Tire

	//set the color of tire
	glColor3f(0.537, 0.262, 0.466);
	//Copies the top matrix and pushes it onto the stack
	glPushMatrix();
	//Give a coordinate for right front tire
	glTranslatef(2.4, -2.5, 3.0);
	//Scaling for circle that I use for tire
	glScalef(0.4, 1.6, 0.4);
	//Rotating operations for right or left
	glRotatef(wheelRotation, 0.0, 1.0, 0.0);
	//Rotating operations for normal rotation
	glRotatef(forwardRot, 0.0, 0.0, 1.0);
	//Copies the top matrix and pushes it onto the stack
	glPushMatrix();
	//Draws a connected group of line segments from the first vertex to the last
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	//Circle algorithm
	for (int i = 0; i < numVertices; ++i)
	{
		glVertex3f(
			x + (radius * cos(i * (2 * PI) / numVertices)),
			y + (radius * sin(i * (2 * PI) / numVertices)), 0.0);
	}
	glEnd();
	//Pops the top matrix off the stack. 
	glPopMatrix();
	//Draw lines from vertex points
	//This lines for line in the circle.It will show the circle return 
	glBegin(GL_LINES);
	//Set color.
	glColor3f(1.0, 0.0, 0.0);
	//Coordinates for lines
	glVertex3f(0.0, -1.5, 0.0);
	glVertex3f(0.0, 1.5, 0.0);
	glVertex3f(-1.5, 0.0, 0.0);
	glVertex3f(1.5, 0.0, 0.0);
	glEnd();
	//Pops the top matrix off the stack.
	glPopMatrix();

	
	//Right Back Tire

	//set the color of tire
	glColor3f(0.537, 0.262, 0.466);
	//Copies the top matrix and pushes it onto the stack
	glPushMatrix();
	//Give a coordinate for right front tire
	glTranslatef(-2.4, -2.5, 3.2);
	//Scaling for circle that I use for tire
	glScalef(0.4, 1.6, 0.4);
	glRotatef(forwardRot, 0.0, 0.0, 1.0);
	//Copies the top matrix and pushes it onto the stack
	glPushMatrix();
	//Draws a connected group of line segments from the first vertex to the last
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	//circle algorithm
	for (int i = 0; i < numVertices; ++i)
	{
		glVertex3f(
			x + (radius * cos(i * (2 * PI) / numVertices)),
			y + (radius * sin(i * (2 * PI) / numVertices)), 0.0);
	}
	glEnd();
	//Pops the top matrix off the stack. 
	glPopMatrix();
	//Draw lines from vertex points
	//This lines for line in the circle.It will show the circle return 
	glBegin(GL_LINES);
	//Set color.
	glColor3f(1.0, 0.0, 0.0);
	//Coordinates for lines
	glVertex3f(0.0, -1.5, 0.0);
	glVertex3f(0.0, 1.5, 0.0);
	glVertex3f(-1.5, 0.0, 0.0);
	glVertex3f(1.5, 0.0, 0.0);
	glEnd();
	//Pops the top matrix off the stack.
	glPopMatrix();

	
	//Left Front Tire

	//set the color of tire
	glColor3f(0.537, 0.262, 0.466);
	//Copies the top matrix and pushes it onto the stack
	glPushMatrix();
	//Give a coordinate for right front tire
	glTranslatef(2.4, -2.5, -3.0);
	//Scaling for circle that I use for tire
	glScalef(0.4, 1.6, 0.4);
	glRotatef(wheelRotation, 0.0, 1.0, 0.0);
	glRotatef(forwardRot, 0.0, 0.0, 1.0);
	//Copies the top matrix and pushes it onto the stack
	glPushMatrix();
	//Draws a connected group of line segments from the first vertex to the last
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	//circle algorithm
	for (int i = 0; i < numVertices; ++i)
	{
		glVertex3f(
			x + (radius * cos(i * (2 * PI) / numVertices)),
			y + (radius * sin(i * (2 * PI) / numVertices)), 0.0);
	}
	glEnd();
	//Pops the top matrix off the stack. 
	glPopMatrix();
	//Draw lines from vertex points
	//This lines for line in the circle.It will show the circle return 
	glBegin(GL_LINES);
	//Set color.
	glColor3f(1.0, 0.0, 0.0);
	//Coordinates for lines
	glVertex3f(0.0, -1.5, 0.0);
	glVertex3f(0.0, 1.5, 0.0);
	glVertex3f(-1.5, 0.0, 0.0);
	glVertex3f(1.5, 0.0, 0.0);
	glEnd();
	//Pops the top matrix off the stack.
	glPopMatrix();
	

	
	//Left Back Tire

	//set the color of tire
	glColor3f(0.537, 0.262, 0.466);
	//Copies the top matrix and pushes it onto the stack
	glPushMatrix();
	//Give a coordinate for right front tire
	glTranslatef(-2.4, -2.5, -3.2);
	//Scaling for circle that I use for tire
	glScalef(0.4, 1.6, 0.4);
	glRotatef(forwardRot, 0.0, 0.0, 1.0);
	//Copies the top matrix and pushes it onto the stack
	glPushMatrix();
	//Draws a connected group of line segments from the first vertex to the last
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 0.0, 0.0);
	//circle algorithm
	for (int i = 0; i < numVertices; ++i)
	{
		glVertex3f(
			x + (radius * cos(i * (2 * PI) / numVertices)),
			y + (radius * sin(i * (2 * PI) / numVertices)), 0.0);
	}
	glEnd();
	//Pops the top matrix off the stack. 
	glPopMatrix();
	//Draw lines from vertex points
	//This lines for line in the circle.It will show the circle return 
	glBegin(GL_LINES);
	//Set color.
	glColor3f(1.0, 0.0, 0.0);
	//Coordinates for lines
	glVertex3f(0.0, -1.5, 0.0);
	glVertex3f(0.0, 1.5, 0.0);
	glVertex3f(-1.5, 0.0, 0.0);
	glVertex3f(1.5, 0.0, 0.0);
	glEnd();
	//Pops the top matrix off the stack.
	glPopMatrix();
	
	
	//This lines present axles
	glBegin(GL_LINES);
	glColor3f(0.0,0.0,1.0);
	glRotatef(forwardRot, 0.0, 0.0, 1.0);
	glVertex3f(-2.4, -2.5, -3.2);
	glVertex3f(-2.4, -2.5, 3.2);
	glVertex3f(2.4, -2.5, -3.0);
	glVertex3f(2.4, -2.5, 3.0);
	glEnd();

	
	//This line present shaft
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-2.4, -2.5, 0.0);
	glVertex3f(2.4, -2.5, 0.0);
	glEnd();
	

	
	//This line present steering wheel

	//Copies the top matrix and pushes it onto the stack
	glPushMatrix();
	//Set the coordinate 
	glTranslatef(-3.0, 9.0, 0.0);
	//Scale the circle
	glScalef(0.5, 2.0, 0.8);
	//Rotate on the X axis
	glRotatef(90.0, 1.0, 0.0, 0.0);
	//Rotate operation for right and left
	glRotatef(-wheelRotation, 0.0, 0.0, 1.0);
	//Circle algorithm
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < numVertices; ++i)
	{
		glVertex3f(
			x + (radius * cos(i * (2 * PI) / numVertices)),
			y + (radius * sin(i * (2 * PI) / numVertices)), 0.0);
	}
	glEnd();
	//Line for the steering wheel
	glBegin(GL_LINES);
	glColor3f(0.8, 0.0, 0.0);
	glVertex3f(1.4, 0.0, 0.0);
	glVertex3f(-1.5, 0.0, 0.0);
	glEnd();
	glPopMatrix();

	//Line for connection to steering wheel and shaft.
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-2.4, -2.5, 0.0);
	glVertex3f(-3.0, 9.0, 0.0);
	glEnd();
	glPopMatrix();


	glPopMatrix();

	
}

void display() {
	//Clear buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Specify the red, green, blue, and alpha values used when the color buffers are cleared.
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Call the car function
	car();
	//Swap buffer the current window
	glutSwapBuffers();
}

