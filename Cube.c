#include <stdio.h>
#include <GL/glut.h>
#include "Cube.h"

void drawCube(struct Cube *cube) {
    glBegin(GL_QUADS);

    glVertex2f(cube->x, cube->y); // top left
    glVertex2f(cube->x + cube->size, cube->y); // top right
    glVertex2f(cube->x + cube->size, cube->y + cube->size); // bottom right
    glVertex2f(cube->x, cube->y + cube->size);                  // bottom left

    glEnd();
}

void updateCube(struct Cube *cube, float height, float width)
{
    if (cube->y >= height || cube->y <= 0 ) {
        cube->speed_y *= -1;
    }

    if (cube->x >= width || cube->x <= 0 ) reset(cube, height, width);

    cube->x += cube->speed_x;
    cube->y += cube->speed_y;
}

void reset(struct Cube *cube, float height, float width) {
    cube->x = width / 2;
    cube->y = height / 2;
    cube->isMoving = 0;
    cube->speed_x = 0;
    cube->speed_y = 0;
}
