#include "pch.h"
#include <iostream>
#include<GL/glut.h>

void draw_pixel(int x, int y)
{
	glColor3f(1.0, 0.0, 1.0);
	glPointSize(1.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void edgedetect(float x1, float y1, float x2, float y2, int *le, int *re)
{
	float temp, x, mx;
	int i;

	if (y1 > y2)
	{
		temp = x1, x1 = x2, x2 = temp;
		temp = y1, y1 = y2, y2 = temp;
	}

	if (y1 == y2)
		mx = x2 - x1;
	else
		mx = (x2 - x1) / (y2 - y1);

	x = x1;

	for (i = int(y1); i <= (int)y2; i++)
	{
		if (x < (float)le[i]) le[i] = (int)x;
		if (x > (float)re[i]) re[i] = (int)x;
		x += mx;
	}
}

void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, 
	float x5, float y5, float x6, float y6, float x7, float y7, float x8, float y8, float x9, float y9)
{
	int le[500], re[500], i, j;

	for (i = 0; i < 500; i++)
		le[i] = 500, re[i] = 0;

	edgedetect(x1, y1, x2, y2, le, re);
	edgedetect(x2, y2, x3, y3, le, re);
	edgedetect(x3, y3, x4, y4, le, re);
	edgedetect(x4, y4, x5, y5, le, re);
	edgedetect(x5, y5, x6, y6, le, re);
	edgedetect(x6, y6, x7, y7, le, re);
	edgedetect(x7, y7, x8, y8, le, re);
	edgedetect(x8, y8, x9, y9, le, re);
	edgedetect(x9, y9, x1, y1, le, re);

	for (j = 0; j < 500; j++)
	{
		if (le[j] <= re[j])
			for (i = le[j]; i < re[j]; i++)
				draw_pixel(i, j);
	}
}

void display()
{
	int x1 = 150.0;
	int y1 = 300.0;
	int x2 = 150.0;
	int y2 = 270.0;
	int x3 = 170.0;
	int y3 = 250.0;
	int x4 = 200.0;
	int y4 = 240.0;
	int x5 = 230.0;
	int y5 = 240.0;
	int x6 = 230.0;
	int y6 = 260.0;
	int x7 = 200.0;
	int y7 = 260.0;

	int x8 = 180.0;
	int y8 = 275.0;

	int x9 = 180.0;
	int y9 = 300.0;
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(140, 301);
	glVertex2f(140, 350);
	glVertex2f(190, 350);
	glVertex2f(190, 301);
	glEnd();

	glColor3f(2.0f, 0.5f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(190, 325);
	glVertex2f(220, 280);
	glVertex2f(220, 370);
	glEnd();

	glColor3f(2.0f, 0.5f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(140, 325);
	glVertex2f(110, 280);
	glVertex2f(110, 370);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glVertex2f(x5, y5);
	glVertex2f(x6, y6);
	glVertex2f(x7, y7);
	glVertex2f(x8, y8);
	glVertex2f(x9, y9);
	glEnd();

	scanfill(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9);

	glFlush();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);

	glutCreateWindow("Clase4");
	glutDisplayFunc(display);

	init();
	glutMainLoop();
}