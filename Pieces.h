#include <stdio.h>

struct Bar
{
    float x;
    float y;
    float w;
    float h;
    float speed;
    int points;
    int last_winner;
};

void drawBar(struct Bar *bar);
void make_point(struct Bar *this, struct Bar *other);
void up(struct Bar *this, float height);
void down(struct Bar *this, float height);

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
void updateCube(struct Cube *cube, float height, float width, struct Bar *left, struct Bar *right);
