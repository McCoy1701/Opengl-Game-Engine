#ifndef RENDER_H
#define RENDER_H

#define resolution         1
#define SCREEN_WIDTH       160 * resolution
#define SCREEN_HEIGHT      120 * resolution
#define HALF_SCREEN_WIDTH  SCREEN_WIDTH / 2
#define HALF_SCREEN_HEIGHT SCREEN_HEIGHT / 2
#define PixelScale         4 / resolution
#define OPENGL_WIN_WIDTH   (SCREEN_WIDTH  * PixelScale)
#define OPENGL_WIN_HEIGHT  (SCREEN_HEIGHT * PixelScale)


typedef struct {
	float red, green, blue;
} ColorRGB;

extern ColorRGB red;
extern ColorRGB green;
extern ColorRGB blue;
extern ColorRGB cyan;
extern ColorRGB yellow;
extern ColorRGB magenta;
extern ColorRGB white;
extern ColorRGB black;


void clearScreen(void);

void drawPixel(int x, int y, int c);

void drawLine(int x1, int y1, int x2, int y2, int thickness, ColorRGB color);

void drawSquare(int x, int y, int w, int h, int offset, ColorRGB color);

void drawVerticalLine(int x, int y1, int y2, int thickness, ColorRGB color);

void buttonsDown(unsigned char key, int x, int y);

void buttonsUp(unsigned char key, int x, int y);

void createWindow(int argc, char* argv[], char* text, void (*init)(), void (*disFunc)(), void (*butDown)(unsigned char, int, int), void (*butUp)(unsigned char, int, int));


#endif
