#include "../time.h"

#include <GL/glut.h>


double delta (Time fps) {
    fps.frame1 = fps.frame2;
    fps.frame2 = glutGet(GLUT_ELAPSED_TIME);
    return (double) (fps.frame2 - fps.frame1) / 1000.0;
}
