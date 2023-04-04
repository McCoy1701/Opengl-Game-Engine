#include "../render.h"

#include <GL/glut.h>
#include <GL/gl.h>


ColorRGB red     = {1.0, 0.0, 0.0};
ColorRGB green   = {0.0, 1.0, 0.0};
ColorRGB blue    = {0.0, 0.0, 1.0};
ColorRGB yellow  = {1.0, 1.0, 0.0};
ColorRGB cyan    = {0.0, 1.0, 1.0};
ColorRGB magenta = {1.0, 0.0, 1.0};
ColorRGB white   = {1.0, 1.0, 1.0};
ColorRGB black   = {0.0, 0.0, 0.0};


void clearScreen() {
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			drawPixel(x, y, 8);
		}
	}
}


void drawPixel(int x, int y, int c){
	switch (c) {
		case  1: {glColor3f(red.red, red.green, red.blue);                 break;}
		case  2: {glColor3f(green.red, green.green, green.blue);           break;}
		case  3: {glColor3f(blue.red, blue.green, blue.blue);              break;}
		case  4: {glColor3f(yellow.red, yellow.green, yellow.blue);        break;}
		case  5: {glColor3f(cyan.red, cyan.green, cyan.blue);              break;}
		case  6: {glColor3f(magenta.red, magenta.green, magenta.blue);     break;}
		case  7: {glColor3f(white.red, white.green, white.blue);           break;}
		case  8: {glColor3f(black.red, black.green, black.blue);           break;}
		case  9: {glColor3f(red.red/2, red.green, red.blue);               break;}
		case 10: {glColor3f(green.red, green.green/2, green.blue);         break;}
		case 11: {glColor3f(blue.red, blue.green, blue.blue/2);            break;}
		case 12: {glColor3f(yellow.red/2, yellow.green/2, yellow.blue);    break;}
		case 13: {glColor3f(cyan.red, cyan.green/2, cyan.blue/2);          break;}
		case 14: {glColor3f(magenta.red/2, magenta.green, magenta.blue/2); break;}
		case 15: {glColor3f(white.red/2, white.green/2, white.blue/2);	   break;}
	}

	glBegin(GL_POINTS);
	glVertex2i(x * PixelScale + 2, y * PixelScale + 2);
	glEnd();
}


void drawLine(int x1, int y1, int x2, int y2, int thickness, ColorRGB color){
	glColor3f(color.red, color.green, color.blue);
	glLineWidth(thickness);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}


void drawVerticalLine(int x, int y1, int y2, int thickness, ColorRGB color){
	if (y2 < y1) {
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}

	if (y1 < 0) y1 = 0;
	if (y2 >= SCREEN_HEIGHT) y2 = SCREEN_HEIGHT - 1;
	if (x < 0 || x >= SCREEN_WIDTH) return;

	glColor3f(color.red, color.green, color.blue);
	glLineWidth(thickness);
	glBegin(GL_LINES);
	glVertex2i(x, y1);
	glVertex2i(x, y2);
	glEnd();
}


void drawSquare(int x, int y, int w, int h, int offset, ColorRGB color){
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_QUADS);
	glVertex2i(x     + offset, y     + offset);
	glVertex2i(x     + offset, y + h - offset);
	glVertex2i(x + w - offset, y + h - offset);
	glVertex2i(x + w - offset, y     + offset);
	glEnd();
}
