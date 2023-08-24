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

void updateCube(struct Cube *cube)
{
    cube->x += cube->speed_x;
    cube->y += cube->speed_y;
}
