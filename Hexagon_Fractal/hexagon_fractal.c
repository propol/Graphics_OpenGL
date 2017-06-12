#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

GLdouble orthox=0.0;
GLdouble orthoy=0.0;
int numOfPoints = 8000;
int randomColor=0;

void myinit(int first)
{
 
if(first==1){
glEnable(GL_BLEND);
 	  glClearColor(1.0, 1.0, 1.0, 0.0); 
	  glColor3f(0.0, 0.0, 0.0);} 

	
	   glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	   gluOrtho2D(-orthox, -orthox+500.0 , -orthoy, -orthoy + 500.0);
	   
	   glMatrixMode(GL_MODELVIEW);
}

void display( void )
{


	
    typedef GLfloat point2[2];     

	point2 vertices[6]={{150.0,300.0},{350.0,300.0},{450.0,200.0},{350.0,100.0},{150.0,100.0},{50.0,200.0}}; /* A hexagon */

    int i, j, k;
    
    point2 p ={75.0,50.0};  /* An initial point */

    glClear(GL_COLOR_BUFFER_BIT);  



	if(randomColor == 0){
 
			  glColor3ub( rand()%255, rand()%255, rand()%255 );
	}
    for( k=0; k<numOfPoints; k++)
    {
	      j=rand()%6; 

	      p[0] = (p[0]+vertices[j][0])/3.0; 
	      p[1] = (p[1]+vertices[j][1])/3.0;
	
     
		  if(randomColor==1){
		  
		  glColor3ub( rand()%255, rand()%255, rand()%255 );}

	       glBegin(GL_POINTS);
		         glVertex2fv(p); 
	       glEnd();

		   
     }
	if(randomColor==0){
		randomColor=2;
	}
	glutSwapBuffers();
    glFlush(); 
 }

void menuChoice(int id){
	numOfPoints=10000;

	if(id==1){
		randomColor=0;
		display();
	}else if(id==2){	
		randomColor=1;
		display();
	}else exit(0);
}

void Menu(int button, int state, int x, int y){
	
	if(button == GLUT_RIGHT_BUTTON){
		glutCreateMenu(menuChoice);
		glutAddMenuEntry("10.000 points",1);
		glutAddMenuEntry("10.000 points with random color",2);
		glutAddMenuEntry("Exit",3);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}

}

void FractalMove(int x, int y){
	orthoy =  500 - y;
	orthox = x;
	myinit(0);
	glutPostRedisplay();
	
}


void main(int argc, char** argv)
{

	    glutInit(&argc,argv);
	    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
	    glutInitWindowSize(500,500); /* 500 x 500 pixel window */
	    glutInitWindowPosition(0,0); /* place window top left on display */
	    glutCreateWindow("Hexagon Fractal"); /* window title */
		glutMouseFunc(Menu);
		glutMotionFunc(FractalMove);
		randomColor=2;
	    glutDisplayFunc(display); /* display callback invoked when window opened */

		myinit(1); /* set attributes */

	    glutMainLoop(); /* enter event loop */
}
