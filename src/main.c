#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

#include "../engine/input.h"
#include "../engine/render.h"
#include "../engine/time.h"

Time time;

void display() {
    //double fps = delta(time);
    if (time.frame1 - time.frame2 >= 50) {
        clearScreen();

        glutSwapBuffers();
        // glutReshapeWindow(OPENGL_WIN_WIDTH, OPENGL_WIN_HEIGHT);
    }
    time.frame1 = glutGet(GLUT_ELAPSED_TIME);
    glutPostRedisplay();
}


void init() {

}


int main(int argc, char* argv[]) {
    createWindow(argc, argv, "Shit Fucker", init, display, buttonsDown, buttonsUp);
    return 0;
}