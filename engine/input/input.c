#include "../input.h"

#include <GL/glut.h>

ButtonKeys Keys;

void buttonsDown(unsigned char key, int x, int y){
	if (key == 'w') {Keys.w  = 1;}
	if (key == 'a') {Keys.a  = 1;}
	if (key == 's') {Keys.s  = 1;}
	if (key == 'd') {Keys.d  = 1;}
	if (key == 'q') {Keys.q  = 1;}
	if (key == 'e') {Keys.e  = 1;}
	if (key == 'm') {Keys.m  = 1;}
	if (key == ' ') {Keys.sp = 1;}
	glutPostRedisplay();
}


void buttonsUp(unsigned char key, int x, int y){
	if (key == 'w') {Keys.w  = 0;}
	if (key == 'a') {Keys.a  = 0;}
	if (key == 's') {Keys.s  = 0;}
	if (key == 'd') {Keys.d  = 0;}
	if (key == 'q') {Keys.q  = 0;}
	if (key == 'e') {Keys.e  = 0;}
	if (key == 'm') {Keys.m  = 0;}
	if (key == ' ') {Keys.sp = 0;}
	glutPostRedisplay();
}
