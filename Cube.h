#include <stdio.h>

struct Cube
{
    float x;
    float y;
    float size;
    float speed_x;
    float speed_y;
};

void drawCube(struct Cube *cube);
void updateCube(struct Cube *cube);
