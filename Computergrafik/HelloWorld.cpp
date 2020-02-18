#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

namespace helloworld {

	int width = 1920;
	int height = 1080;

	void init(int argc, char** argv) {
		glutInit(&argc, argv);					// Initialisierung der GLUT Bibliothek
		glutInitDisplayMode(GLUT_SINGLE);		// Initialisierung des Single Buffer Modes
		glutInitWindowSize(width, height);		// Fenstergröße in Pixel (Breite, Hoehe)
		glutInitWindowPosition(0, 0);		// Fensterposition in Pixel, ausgehend vom Ursprung des Window Systems
		glViewport(0, 0, width, height);
		glutCreateWindow("Hello World");		// Erstellen des Fensters
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height);
		glMatrixMode(GL_MODELVIEW);
	}

	void display(void)
	{
		glClearColor(0.0, 1.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//Alternativ: glColor3f(1.0, 0.0, 0.0);
		GLfloat myColor[3] = { 0.0, 0.0, 1.0 };
		glColor3fv(myColor);

		glBegin(GL_POLYGON);
		glVertex3f((width / 2) - (width / 4) - 50, (height / 2) - (height / 4) - 250, 0.0);
		glVertex3f((width / 2) + (width / 4) - 50, (height / 2) - (height / 4) - 250, 0.0);
		glVertex3f((width / 2) + (width / 4) - 50, (height / 2) + (height / 4) - 250, 0.0);
		glVertex3f((width / 2) - (width / 4) - 50, (height / 2) + (height / 4) - 250, 0.0);
		glEnd();

		GLfloat myColor2[3] = { 1.0, 0.0, 0.0 };
		glColor3fv(myColor2);

		glBegin(GL_POLYGON);
		glVertex3f((width / 2) - (width / 4) - 50, (height / 2) - (height / 4) + 300, 0.0);
		glVertex3f((width / 2) + (width / 4) - 50, (height / 2) - (height / 4) + 300, 0.0);
		glVertex3f((width / 2) - 50, (height / 2) + (height / 4) + 300, 0.0);
		glEnd();

		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2i((width / 2) - (width / 4) + 120, (height / 2) - (height / 4) + 60);

		char myText[] = "Hello World!";
		for (int j = 0; j < strlen(myText); j++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, myText[j]);
		}

		glFlush();
	}


	int main(int argc, char** argv)
	{
		init(argc, argv);
		glutDisplayFunc(display);				// Callback-Funktion für das Fenster
		glutMainLoop();							// Abgabe der Kontrolle an GLUT-Bibliothek
		return 0;
	}

}

