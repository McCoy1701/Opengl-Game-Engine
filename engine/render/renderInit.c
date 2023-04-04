#include "../input.h"
#include "../render.h"

#include <GL/glut.h>


void createWindow(int argc, char* argv[], char* text, void (*init)(), void (*disFunc)(), 
				  void (*butDown)(unsigned char, int, int), void (*butUp)(unsigned char, int, int)){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(OPENGL_WIN_WIDTH / 2, OPENGL_WIN_HEIGHT / 2);
	glutInitWindowSize(OPENGL_WIN_WIDTH, OPENGL_WIN_HEIGHT);
	glutCreateWindow(text);
	glPointSize(PixelScale);
	gluOrtho2D(0, OPENGL_WIN_WIDTH, 0, OPENGL_WIN_HEIGHT);

	init();
	glutDisplayFunc(disFunc);
	glutKeyboardFunc(butDown);
	glutKeyboardUpFunc(butUp);
	glutMainLoop();
}