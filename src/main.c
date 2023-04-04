#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

#include "../engine/input.h"
#include "../engine/render.h"
#include "../engine/time.h"

#define numberSectors  4
#define numberWalls   16


typedef struct {
	int x, y, z;
	int angle;
	int lookAngle;
} Player;


typedef struct {
	float sin[360];
	float cos[360];
} MathTable;


typedef struct {
	int x1, y1;
	int x2, y2;
	int color;
}Walls;


typedef struct {
	int wallStart, wallEnd;
	int z1, z2;
	int d;
	int c1, c2;
	int surf[SCREEN_WIDTH];
	int surface;
} Sectors;


Time time;
MathTable mathTable;
Player player;
Walls walls[30];
Sectors sectors[30];


int distance(int x1, int y1, int x2, int y2) {int distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)); return distance;}


void movement() {
	if (Keys.d == 1 && Keys.m == 0) {player.angle -= 4; if (player.angle <   0) {player.angle += 360;}}
	if (Keys.a == 1 && Keys.m == 0) {player.angle += 4; if (player.angle > 359) {player.angle -= 360;}}

	int deltaX = mathTable.sin[player.angle] * 10.0;
	int deltaY = mathTable.cos[player.angle] * 10.0;

	if (Keys.w == 1 && Keys.m == 0) {player.x += deltaX; player.y += deltaY;}
	if (Keys.s == 1 && Keys.m == 0) {player.x -= deltaX; player.y -= deltaY;}

	if (Keys.e == 1) {player.x += deltaY; player.y -= deltaX;}
	if (Keys.q == 1) {player.x -= deltaY; player.y += deltaX;}

	if (Keys.a == 1 && Keys.m == 1) {player.lookAngle -= 1;}
	if (Keys.d == 1 && Keys.m == 1) {player.lookAngle += 1;}
	if (Keys.w == 1 && Keys.m == 1) {player.z -= 4;}
	if (Keys.s == 1 && Keys.m == 1) {player.z += 4;}
}


void clipBehindPlayer(int *x1, int *y1, int *z1, int x2, int y2, int z2) {
	float distanceA = *y1;
	float distanceB =  y2;
	float deltaDistance = distanceA - distanceB; if (deltaDistance == 0) {deltaDistance = 1;}

	float intersectionFactor = distanceA / deltaDistance;

	*x1 = *x1 + intersectionFactor * (x2 - (*x1));
	*y1 = *y1 + intersectionFactor * (y2 - (*y1)); if (*y1 == 0) {*y1 = 1;}
	*z1 = *z1 + intersectionFactor * (z2 - (*z1));
}


void drawWall(int x1, int x2, int b1, int b2, int t1, int t2, int color, int sector){
	int deltaBottom = b2 - b1;
	int deltaTop    = t2 - t1;
	int deltaX      = x2 - x1; if (deltaX == 0) {deltaX = 1;}

	if (x1 < 1)                {x1 = 1;}
	if (x2 < 1)                {x2 = 1;}
	if (x1 > SCREEN_WIDTH - 1) {x1 = SCREEN_WIDTH - 1;}
	if (x2 > SCREEN_WIDTH - 1) {x2 = SCREEN_WIDTH - 1;}

	int xStart = x1;

	for (int x = xStart; x < x2; x++) {
		int y1 = deltaBottom * (x - xStart + 0.5) / deltaX + b1;
		int y2 = deltaTop    * (x - xStart + 0.5) / deltaX + t1;

		if (y1 < 1)                 {y1 = 1;}
		if (y2 < 1)                 {y2 = 1;}
		if (y1 > SCREEN_HEIGHT - 1) {y1 = SCREEN_HEIGHT - 1;}
		if (y2 > SCREEN_HEIGHT - 1) {y2 = SCREEN_HEIGHT - 1;}

		if (sectors[sector].surface ==  1) {sectors[sector].surf[x] = y1; continue;}
		if (sectors[sector].surface ==  2) {sectors[sector].surf[x] = y2; continue;}
		if (sectors[sector].surface == -1) {for (int y = sectors[sector].surf[x]; y< y1; y++) {drawPixel(x, y, sectors[sector].c1);}}
		if (sectors[sector].surface == -2) {for (int y = y2; y < sectors[sector].surf[x]; y++) {drawPixel(x, y, sectors[sector].c2);}}

		for (int y = y1; y < y2; y++) {drawPixel(x, y, color);}
	}
}


void draw3D() {
	for (int s = 0; s < numberSectors; s++) {
		for (int w = 0; w < numberWalls; w++) {
			if(sectors[w].d < sectors[w + 1].d) {
				Sectors temp = sectors[w]; sectors[w] = sectors[w + 1]; sectors[w + 1] = temp;
			}
		}
	}

	for (int sector = 0; sector < numberSectors; sector++) {
		sectors[sector].d = 0;
		if (player.z < sectors[sector].z1)      {sectors[sector].surface = 1;}
		else if (player.z > sectors[sector].z2) {sectors[sector].surface = 2;}
		else                                    {sectors[sector].surface = 0;}
		for (int loop = 0; loop < 2; loop++){
			for (int wall = sectors[sector].wallStart; wall < sectors[sector].wallEnd; wall++) {

				int wallX[4], wallY[4], wallZ[4];
				float wallCos = mathTable.cos[player.angle], wallSin = mathTable.sin[player.angle];

				int x1 = walls[wall].x1 - player.x, y1 = walls[wall].y1 - player.y;
				int x2 = walls[wall].x2 - player.x, y2 = walls[wall].y2 - player.y;
				if (loop ==0) {int temp = x1; x1 = x2; x2 = temp; temp = y1; y1 = y2; y2 = temp;}

				wallX[0] = x1 * wallCos - y1 * wallSin;
				wallX[1] = x2 * wallCos - y2 * wallSin;
				wallX[2] = wallX[0];
				wallX[3] = wallX[1];

				wallY[0] = y1 * wallCos + x1 * wallSin;
				wallY[1] = y2 * wallCos + x2 * wallSin;
				wallY[2] = wallY[0];
				wallY[3] = wallY[1];

				sectors[sector].d += distance(0, 0, (wallX[0] + wallX[1]) / 2, (wallY[0] + wallY[1]) / 2);

				wallZ[0] = sectors[sector].z1 - player.z + ((player.lookAngle * wallY[0]) / 32.0);
				wallZ[1] = sectors[sector].z1 - player.z + ((player.lookAngle * wallY[1]) / 32.0);
				wallZ[2] = wallZ[0] + sectors[sector].z2;
				wallZ[3] = wallZ[1] + sectors[sector].z2;

				if (wallY[0] < 1 && wallY[1] < 1) {continue;}

				if (wallY[0] < 1) {
					clipBehindPlayer(&wallX[0], &wallY[0], &wallZ[0], wallX[1], wallY[1], wallZ[1]);
					clipBehindPlayer(&wallX[2], &wallY[2], &wallZ[2], wallX[3], wallY[3], wallZ[3]);
				}

				if (wallY[1] < 1) {
					clipBehindPlayer(&wallX[1], &wallY[1], &wallZ[1], wallX[0], wallY[0], wallZ[0]);
					clipBehindPlayer(&wallX[3], &wallY[3], &wallZ[3], wallX[2], wallY[2], wallZ[2]);
				}

				wallX[0] = wallX[0] * 200 / wallY[0] + HALF_SCREEN_WIDTH; wallY[0] = wallZ[0] * 200 / wallY[0] + HALF_SCREEN_HEIGHT;
				wallX[1] = wallX[1] * 200 / wallY[1] + HALF_SCREEN_WIDTH; wallY[1] = wallZ[1] * 200 / wallY[1] + HALF_SCREEN_HEIGHT;
				wallX[2] = wallX[2] * 200 / wallY[2] + HALF_SCREEN_WIDTH; wallY[2] = wallZ[2] * 200 / wallY[2] + HALF_SCREEN_HEIGHT;
				wallX[3] = wallX[3] * 200 / wallY[3] + HALF_SCREEN_WIDTH; wallY[3] = wallZ[3] * 200 / wallY[3] + HALF_SCREEN_HEIGHT;

				drawWall(wallX[0], wallX[1], wallY[0], wallY[1], wallY[2], wallY[3], walls[wall].color, sector);
			}
			sectors[sector].d /= (sectors[sector].wallEnd - sectors[sector].wallStart);
			sectors[sector].surface *= -1;
		}
	}
}

void display() {
	//double fps = delta(time);
	//if (time.frame1 - time.frame2 >= 50) {
	clearScreen();
	movement();
	draw3D();

	glutSwapBuffers();
	// glutReshapeWindow(OPENGL_WIN_WIDTH, OPENGL_WIN_HEIGHT);
	//}
	//time.frame1 = glutGet(GLUT_ELAPSED_TIME);
	glutPostRedisplay();
}


int loadSectors[] = {
	//WallStart, WallEnd, Wall Z1, Wall Z2, bottom color, top color
	0 ,  4,  0, 40, 2, 3, //sector 1
	4 ,  8,  0, 40, 4, 5, //sector 2
	8 , 12,  0, 40, 6, 7, //sector 3
	12, 16,  0, 40, 1, 9, //sector 4
};


int loadWalls[] = {
	//Wall x1, Wall y1, Wall x2, Wall y2, ColorRGB
	0 ,  0, 32,  0,  9,
	32,  0, 32, 32,  1,
	32, 32,  0, 32,  9,
	0 , 32,  0,  0,  1,

	64,  0, 96,  0,  2,
	96,  0, 96, 32,  10,
	96, 32, 64, 32,  2,
	64, 32, 64,  0,  10,

	64, 64, 96, 64,  3,
	96, 64, 96, 96,  11,
	96, 96, 64, 96,  3,
	64, 96, 64, 64,  11,

	0 , 64, 32, 64,  4,
	32, 64, 32, 96,  12,
	32, 96,  0, 96,  4,
	0 , 96,  0, 64,  12,
};


void init() {
	for (int x = 0; x < 360; x++) {
		mathTable.sin[x] = cos(x / 180.0 * M_PI);
		mathTable.cos[x] = sin(x / 180.0 * M_PI);
	}
	player.x = 70; player.y = -110; player.z = 20;
	player.angle = 0; player.lookAngle = 0;

	int v1 = 0, v2 = 0;
	for (int s = 0; s < numberSectors; s++) {
		sectors[s].wallStart = loadSectors[v1 + 0];
		sectors[s].wallEnd   = loadSectors[v1 + 1];
		sectors[s].z1        = loadSectors[v1 + 2];
		sectors[s].z2        = loadSectors[v1 + 3];
		sectors[s].c1        = loadSectors[v1 + 4];
		sectors[s].c2        = loadSectors[v1 + 5];
		v1 += 6;
		for (int w = sectors[s].wallStart; w < sectors[s].wallEnd; w++) {
			walls[w].x1    = loadWalls[v2 + 0];
			walls[w].y1    = loadWalls[v2 + 1];
			walls[w].x2    = loadWalls[v2 + 2];
			walls[w].y2    = loadWalls[v2 + 3];
			walls[w].color = loadWalls[v2 + 4];
			v2 += 5;
		}
	}
}


int main(int argc, char* argv[]) {
	createWindow(argc, argv, "Shit Fucker", init, display, buttonsDown, buttonsUp);
	return 0;
}
