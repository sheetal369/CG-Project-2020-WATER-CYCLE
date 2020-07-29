#include<stdio.h>
#include<GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#define SPEED 2.0

float i=0.0, b=0.0, m=0.0,n=0.0,o=0.0,c=0.0;
float p=0.75,q=0.47,r=0.14;
float e=0.90,f=0.91,g=0.98;
int count=0;

int xm=900,bird=0;

void draw_pixel(GLint cx, GLint cy)
{

	glBegin(GL_POINTS);
		glVertex2i(cx,cy);
	glEnd();
}

void plotpixels(GLint h,GLint k, GLint x,GLint y)
{
	draw_pixel(x+h,y+k);
	draw_pixel(-x+h,y+k);
	draw_pixel(x+h,-y+k);
	draw_pixel(-x+h,-y+k);
	draw_pixel(y+h,x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,-x+k);
}

void draw_circle(GLint h, GLint k, GLint r)
{
	GLint d=1-r, x=0, y=r;
	while(y>x)
	{
		plotpixels(h,k,x,y);
		if(d<0) d+=2*x+3;
		else
		{
			d+=2*(x-y)+5;
			--y;
		}
		++x;
	}
	plotpixels(h,k,x,y);
}

//Drawing Objects
int l;
void drawSky()
{
    //SKY
    glColor3f(0.0,0.9,0.9);
    glBegin(GL_POLYGON);
        glVertex2f(0,250);
        glVertex2f(0,700);
        glVertex2f(1100,700);
        glVertex2f(1100,250);
    glEnd();
}

void drawSun()
{
    //SUN
	for(l=0;l<=35;l++)
    {
		glColor3f(1.0,0.9,0.0);
		draw_circle(100,625,l);
    }
}
void drawClouds()
{
    //CLOUD FIRST
	for(l=0;l<=20;l++)
	{
		glColor3f(1.0,1.0,1.0);
		draw_circle(160+m,625,l);
	}
	for(l=0;l<=35;l++)
	{
		glColor3f(1.0,1.0,1.0);
		draw_circle(200+m,625,l);
		draw_circle(225+m,625,l);
	}
	for(l=0;l<=20;l++)
	{
		glColor3f(1.0,1.0,1.0);
		draw_circle(265+m,625,l);
	}

//CLOUD SECOND
	for(l=0;l<=20;l++)
	{
		glColor3f(1.0,1.0,1.0);
		draw_circle(370+m,615,l);
    }
	for(l=0;l<=35;l++)
	{
		glColor3f(1.0,1.0,1.0);
		draw_circle(410+m,615,l);
		draw_circle(435+m,615,l);
		draw_circle(470+m,615,l);
	}
for(l=0;l<=20;l++)
	{
		glColor3f(1.0,1.0,1.0);
		draw_circle(500+m,615,l);
}
}

void drawGrass()
{
    //GRASS
    glColor3f(0.6,0.8,0.196078);
    glBegin(GL_POLYGON);
        glVertex2f(0,160);
        glVertex2f(0,380);
        glVertex2f(1100,250);
        glVertex2f(1100,160);
    glEnd();
}

void drawSea()
{
    //SEA
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
		glVertex2f(-600,0);
		glVertex2f(-600,200);
		glVertex2f(1100,200);
		glVertex2f(1100,0);
	glEnd();
}
void drawTree()
{
    //TREE
glColor3f(0.9,0.2,0.0);
glBegin(GL_POLYGON);
glVertex2f(280,185);
glVertex2f(280,255);
glVertex2f(295,255);
glVertex2f(295,185);
glEnd();

	for(l=0;l<=30;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(270,250,l);
		draw_circle(310,250,l);
	}

	for(l=0;l<=25;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(280,290,l);
		draw_circle(300,290,l);
	}

	for(l=0;l<=20;l++)
	{
		glColor3f(0.0,0.5,0.0);
		draw_circle(290,315,l);
	}
}
void drawRaindrops()
{
    //RAIN_DROPS
glColor3f(0.0,0.0,1.0);
	glBegin(GL_POINTS);

		glVertex2f(230+i-xm,180+b);
		glVertex2f(230+i-xm,150+b);
		glVertex2f(200+i-xm,150+b);

		glVertex2f(200+i-xm,50+b);

		glVertex2f(230+i-xm,150+b);
		glVertex2f(230+i-xm,120+b);
		glVertex2f(200+i-xm,110+b);

		glVertex2f(200+i-xm,50+b);
	glEnd();
}

void Draw_Scene()
{
     drawSky();
     drawSun();
     drawClouds();
     drawRaindrops();

     drawGrass();
     drawTree();
     drawSea();

	glColor3f(0.0,0.0,1.0);
glFlush();
}


void idle()
{
if(count<=100)
    {
glClearColor(1.0,1.0,1.0,1.0);

     i+=SPEED/10;
     b+=SPEED/1;
     m+=SPEED/15;
    }
if(i>1900)
	 i=800.0;
if(m>1100)
	 m=0.0;

if(b>500)
{
	b=0.0;
	i=800.0;
	count=count+1;
}
glutPostRedisplay();
}


void myinit()
{
glClearColor(1.0,1.0,1.0,1.0);
glColor3f(0.0,0.0,1.0);
glPointSize(2.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,1100.0,0.0,700.0);
}



void display()
{
glClear(GL_COLOR_BUFFER_BIT);
Draw_Scene();
glFlush();
}


int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1100.0,700.0);
	glutInitWindowPosition(0,0);
	glutCreateWindow("[CG PROJECT] WATER CYCLE");
	glutDisplayFunc(display);
    glutIdleFunc(idle);
	myinit();;
	glutMainLoop();
	return 0;
}
