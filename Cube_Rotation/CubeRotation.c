// CubeRotation.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

//Globals
double dim = 20; // dimension of orthogonal box 
char *windowName = "OpenGL Project 2"; //window title
int windowWidth = 500;
int windowHeight = 450;

GLfloat angle = 0.0f; //Initial angle of rotation
GLfloat sc = 1.0; //scaling variable
GLfloat sc2 = 1.0; //assistant variable used for accurate scaling

float scalingFactor = 0.001;
float rotationFactor = 0.2;

int flag; //assistant flag used for accurate scaling
int flag2; //assistant flag used for accurate scaling

/*
* project()
* ------
* Sets the projection
*/
void project()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Orthogonal projection
	glOrtho(-dim, +dim, -dim, +dim, -150, +150);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
*  drawShape()
*  ------
*  Draw the cube
*/
void drawShape()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear the window

	glNewList(1, GL_COMPILE); //Save rectangle in a list

		//Plot a base rectangle 
		glBegin(GL_QUADS);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
		glEnd();

	glEndList(); //Close list "section"

	 //checks if scaled above double size.
	 //If so, raise flags
	if (sc > 2.0)
	{
		flag = 1; //signals that scaling reached double size
		flag2 = 1; //helps keep scaling between 1.0 - 2.0
				   //permits flag from changing again instantly, when sc goes slightly below 2.0
	}
	else if (flag2 == 0 && sc < 2.0) //flag2==0 signals that sc has reached 1.0, allows its upwards scaling again
	{
		flag = 0; //Signals that scaling reached initial size   
	}

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glTranslatef(0.0, 0.0, -110.0);

	glScalef(sc, sc, sc);
	
	glRotatef(angle, 1.0, 1.0, 1.0);


	//front face
	glPushMatrix();

	glScalef(3.0, 3.0, 3.0);

	//glTranslatef(0.0, 0.0, -1.0);

	glCallList(1);

	glPopMatrix();


	//right face
	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0); // green
	glScalef(3.0, 3.0, 3.0);
	//glTranslatef(-0.8, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);

	glCallList(1);

	glPopMatrix();

	//left face
	glPushMatrix();

	glColor3f(0.0, 0.0, 1.0); //blue
	glScalef(3.0, 3.0, 3.0);
	glTranslatef(-2.0, 0.0, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);

	glCallList(1);

	glPopMatrix();

	//up face
	glPushMatrix();

	glColor3f(0.0, 1.0, 1.0);
	glScalef(3.0, 3.0, 3.0);
	//glTranslatef(0.0, 0.8, 0.0); //light blue
	glRotatef(90, 1.0, 0.0, 0.0);

	glCallList(1);

	glPopMatrix();

	//down face
	glPushMatrix();

	glColor3f(1.0, 0.0, 1.0);
	glScalef(3.0, 3.0, 3.0);
	glTranslatef(0.0, +2.0, 0.0); //purple
	glRotatef(90, 1.0, 0.0, 0.0);

	glCallList(1);

	glPopMatrix();

	//back face
	glPushMatrix();

	glColor3f(1.0, 1.0, 0.0); //yellow
	glScalef(3.0, 3.0, 3.0);
	glTranslatef(0.0, 0.0, -2.0);

	glCallList(1);

	glPopMatrix();


}


/*
* idle()
* ------
* Idle callback function
* Increase or decrease the scaling factor and rotation angle
*/

void idle()
{

	if (flag == 0) //signals that sc is < 2.0
	{
		sc += scalingFactor; //gradually raise sc to 2.0
	}

	if (flag == 1) //signals that sc is >= 2.0
	{
		sc -= scalingFactor; //gradually decrease sc to 1.0

		if (sc<1.0)
		{
			flag2 = 0; //signals that sc reached initial size, allows upwards scaling again
		}
	}

	angle += rotationFactor; //increase roatation angle

	glutPostRedisplay();
}

/*
*  display()
*  ------
*  Display the scene
*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear window

	glEnable(GL_DEPTH_TEST); //Enable Z-buffering

	glLoadIdentity();

	drawShape();

	glFlush();

	glutSwapBuffers();
}

/*
*  reshape()
*  ------
*  Called when the window is resized
*/
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	project();
}

/*
*  main()
*  ----
*  Initialiazation
*/
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow(windowName);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}