#include <stdio.h>

struct Cube
{
    float x;
    float y;
    float size;
    float speed_x;
    float speed_y;
    int isMoving;
};

void drawCube(struct Cube *cube);
void reset(struct Cube *cube, float height, float width);
void updateCube(struct Cube *cube, float height, float width);
