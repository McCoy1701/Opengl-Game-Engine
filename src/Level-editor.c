#include <GL/freeglut_std.h>
#include <GL/glut.h>

#include "../engine/input.h"
#include "../engine/time.h"
#include "../engine/render.h"


void display() {
	clearScreen();
	drawLine(10, 10, 100, 100, 1, red);

	glutSwapBuffers();
}


void init() {
	
}

int main(int argc, char* argv[]) {
	createWindow(argc, argv, "Level Editor", init, display, buttonsDown, buttonsUp);
	return 0;
}

