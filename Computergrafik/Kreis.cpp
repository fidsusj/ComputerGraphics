#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <stdio.h>
#include <math.h>

namespace kreis {


#pragma warning(disable:4996)

#define PI 3.14159265358979323846

	int width = 800;
	int height = 600;

	void init(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE);
		glutInitWindowSize(width, height);
		glutInitWindowPosition(100, 100);
		glViewport(0, 0, width, height);
		glutCreateWindow("Programmieruebung Kreis-Plotter");
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height);
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_POINT_SMOOTH);
	}

	void drawCoordinateSystem(float* origin, int xLength, int yLength, int numTicksX, int numTicksY, float minX, float maxX, float minY, float maxY) {

		float xTickDistance = (float)xLength / (float)numTicksX;
		float yTickDistance = (float)yLength / (float)numTicksY;

		int  k;
		float j;

		float resX, resY;

		char label[10];

		resX = (maxX - minX) / xLength;
		resY = (maxY - minY) / yLength;

		glColor3f(0.0, 0.0, 0.0);
		/* drawing the coordinate system */
		glBegin(GL_LINES);
		// x axis
		glVertex2f(origin[0], origin[1]);
		glVertex2f(origin[0] + xLength, origin[1]);
		// y axis
		glVertex2f(origin[0], origin[1]);
		glVertex2f(origin[0], origin[1] + yLength);
		// arrow head at x axis
		glVertex2f(origin[0] + xLength, origin[1]);
		glVertex2f(origin[0] + xLength - 15, origin[1] - 10);
		glVertex2f(origin[0] + xLength, origin[1]);
		glVertex2f(origin[0] + xLength - 15, origin[1] + 10);
		// arrow head at y axis
		glVertex2f(origin[0], origin[1] + yLength);
		glVertex2f(origin[0] - 10, origin[1] + yLength - 15);
		glVertex2f(origin[0], origin[1] + yLength);
		glVertex2f(origin[0] + 10, origin[1] + yLength - 15);
		glEnd();

		// drawing ticks at x axis
		for (j = 0; j < xLength; j = j + xTickDistance) {
			glBegin(GL_LINES);
			glVertex2f(origin[0] + j, origin[1] - 5);
			glVertex2f(origin[0] + j, origin[1] + 5);
			glEnd();
			sprintf(label, "%5.2f", minX + (j * resX));
			glRasterPos2i((int)round(origin[0] + j - (8 * 5)), (int)round(origin[1] - 13 - 10));
			for (k = 0; k < 5; k++) {
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, label[k]);
			}
		}

		// drawing ticks at y axis
		for (j = 0; j < yLength; j = j + yTickDistance) {
			glBegin(GL_LINES);
			glVertex2f(origin[0] - 5, origin[1] + j);
			glVertex2f(origin[0] + 5, origin[1] + j);
			glEnd();
			sprintf(label, "%5.2f", minY + (j * resY));
			glRasterPos2i((int)round(origin[0] - (8 * 5) - 10), (int)round(origin[1] + j - 13 / 2));
			for (k = 0; k < 5; k++) {
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, label[k]);
			}
		}
	}


	void drawCircle(float origin[2], float center[2], float radius, GLint numPoints)
	{
		//////////////////////////////////////////////////////////////////////////////////////////////
		// - calculate numPoints points on the surface of the circle with given center and radius
		//		hint: see circle equation in parametric form 
		// - position points in the coordinate system starting at given origin
		// - draw the points by OpenGL commands
		// Origin: Ursprung des lokalen Koordinatensystems
		// Center: Mittelpunkt des Kreises


		float x, y;
		float i;
		glBegin(GL_POINTS);
		for (i = 0.0; i < 2 * PI; i = i + 2 * PI / numPoints) {
			x = origin[0] + center[0] + radius * cos(i);
			y = origin[1] + center[1] + radius * sin(i);
			glVertex2f(x, y);
		}
		glEnd();

		//////////////////////////////////////////////////////////////////////////////////////////////
	}




	void display(void)
	{

		int n;
		int xTickDistance = 50;
		int yTickDistance = 50;
		int numPoints = 30;
		float radius[] = { 50, 100, 150 };
		float center[] = { 300, 200 };
		float origin[] = { 100, 100 };
		GLfloat c[] = { 0.0,0.0,0.0 };
		int xLength = 600;
		int yLength = 400;
		float size = 2;


		/* settings for the coordinate system */
		int numTicksX = 6;
		int numTicksY = 4;
		float minX = 0;
		float maxX = 600;
		float minY = 0;
		float maxY = 400;


		/* clearing the background color */
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		drawCoordinateSystem(origin, xLength, yLength, numTicksX, numTicksY, minX, maxX, minY, maxY);


		for (n = 0; n < 3; n++) {

			///////////////////////////////////////////////////////////////////////////////
			// - set the point size different for each loop iteration
			// - set the color different for each loop iteration

			if (n == 0) {
				glColor3f(1.0, 0.0, 0.0);
				glPointSize(1);
			}
			else if (n == 1) {
				glColor3f(0.0, 1.0, 0.0);
				glPointSize(2);
			}
			else {
				glColor3f(0.0, 0.0, 1.0);
				glPointSize(3);
			}

			//////////////////////////////////////////////////////////////////////////////
			drawCircle(origin, center, radius[n], numPoints);
		}


		glFlush();
	}


	int main(int argc, char** argv)
	{
		init(argc, argv);

		glutDisplayFunc(display);
		glutMainLoop();
		return 0;
	}

}