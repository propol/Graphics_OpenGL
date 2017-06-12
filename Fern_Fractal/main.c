#include <math.h>		
#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>



#define	RGBA_COLOR	1 

#define	FERN_WIDTH	 8.0
#define	FERN_HEIGHT	12.0

double	fern_red[] = {
	0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.90 };
double 	fern_green[] = {
	0.90, 0.86, 0.82, 0.78, 0.76, 0.72, 0.68, 0.64, 0.60, 0.56, 0.52 };
double	fern_blue[] = {
	0.20, 0.24, 0.28, 0.32, 0.36, 0.40, 0.44, 0.48, 0.52, 0.56, 0.60 };

#define	FERN_COLOR	  10

int iterations = 50000;

typedef	GLfloat	point2[2];	

				
void myinit(void);
void display(void);

void main(int argc, char *argv[], char *envp[])
		
	{
	if (argc == 2)
		iterations = atoi(argv[1]);

	glutInit(&argc, argv);
#if defined(RGBA_COLOR)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA );  
#else
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_INDEX);  
#endif
	glutInitWindowSize(60 * (int)FERN_WIDTH, 
		60 * (int)FERN_HEIGHT);	

	glutInitWindowPosition(10, 10);	
	glutCreateWindow("Fractal Barnsley Fern");	
	myinit(); 		
	glutDisplayFunc(display);	
	glutMainLoop();			
	}  /* end of main */




void myinit(void)	{
#if defined(RGBA_COLOR)
	glClearColor(1.0, 1.0, 1.0, 1.0); 	/* white background */
				
	glColor3d(fern_red[0], fern_green[0], fern_blue[0]);
#else
	glutSetColor(0, 0.0, 0.0, 0.0);		/* black */
	glutSetColor(1, 1.0, 1.0, 1.0);		/* white */
	glutSetColor(2, 1.0, 0.0, 0.0);		/*  red  */
	glClearIndex(1.0);			/* note GLfloat */
	glIndexi(2);			/* draw vertices in red */
#endif

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(- FERN_WIDTH/2.0, FERN_WIDTH/2.0, 0.0, FERN_HEIGHT);	
					/* Orthographic
					projection (no perspective
					effect) */
	glMatrixMode(GL_MODELVIEW);
	
	glFlush();
	}  /* end of myinit */


void display(void)
		
	{
	static point2	p = {0.0, 0.0}, q;	
	double	rand_x;				
	int	j, k, color_index, iterations_since_null;
	time_t	ltime;
						
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	time(&ltime);
	srand((unsigned int)ltime);

	color_index = 0;
	iterations_since_null = 0;
	glColor3d(fern_red[0], fern_green[0], fern_blue[0]);

	for (k = 0 ; k < iterations ; k++)
		{
		rand_x = (double)rand()/(double)RAND_MAX;
		if  ( (rand_x >= 0.0) && (rand_x < 0.83) ) 
			j = 0;
		else if ( (rand_x >= 0.83) && (rand_x < 0.91) ) 
			j = 1;
		else if ( (rand_x >= 0.91) && (rand_x < 0.99) ) 
			j = 2;
		else
			j = 3;

		iterations_since_null++;
		if (j == 0)			/* UP */
			{
			q[0] = ( 0.86* p[0]) + ( 0.03 * p[1]) + 0.0;	
			q[1] = (-0.03* p[0]) + ( 0.86 * p[1]) + 1.5;	
			}
		else if (j == 1)		/* RIGHT */
			{
			q[0] = ( 0.02* p[0]) + (-0.25 * p[1]) + 0.0;	
			q[1] = ( 0.21* p[0]) + ( 0.23 * p[1]) + 1.5;	
			}
		else if (j == 2)		/* LEFT */
			{
			q[0] = (-0.15* p[0]) + ( 0.27 * p[1]) + 0.0;	
			q[1] = ( 0.25* p[0]) + ( 0.26 * p[1]) + 0.45;	
			}
		else if (j == 3)		/* RETURN */
			{
			q[0] = ( 0.00* p[0]) + ( 0.00 * p[1]) + 0.0;	
			q[1] = ( 0.00* p[0]) + ( 0.17 * p[1]) + 0.0;	

			color_index = 0; 		/* reset color */
			iterations_since_null = 0;
			glColor3d(fern_red[0], fern_green[0], fern_blue[0]);
			}

		glBegin(GL_POINTS);		
					
			glVertex2fv(q);		
					
		glEnd();

		if ( (color_index < FERN_COLOR) &&
			((iterations_since_null/(FERN_COLOR + 5)) > 
				color_index) )
			{
			color_index++;
			glColor3d(fern_red[color_index], 
			  fern_green[color_index], fern_blue[color_index]);
			}

		p[0] = q[0];
		p[1] = q[1];
		} 
	glutSwapBuffers();
				
	}  /* end of display */



