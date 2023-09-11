#include "Pieces.h"

void drawCube(struct Cube *cube)
{

    glBegin(GL_QUADS);

    glVertex2f(cube->x, cube->y);                           // top left
    glVertex2f(cube->x + cube->size, cube->y);              // top right
    glVertex2f(cube->x + cube->size, cube->y + cube->size); // bottom right
    glVertex2f(cube->x, cube->y + cube->size);              // bottom left

    glEnd();
}

void updateCube(struct Cube *cube, float height, float width, struct Bar *left, struct Bar *right)
{
    if (cube->y >= height || cube->y <= 0)
    {
        cube->speed_y *= -1;
    }

    if (cube->x >= width || cube->x <= 0)
        reset(cube, height, width);

    cube->x += cube->speed_x;
    cube->y += cube->speed_y;

    if (cube->x <= left->x && cube->y >= left->y && cube->y <= left->y + left->h)
        cube->speed_x *= -1;
    else if (cube->x + cube->size >= right->x && cube->y >= right->y && cube->y <= right->y + right->h)
        cube->speed_x *= -1;
}

void reset(struct Cube *cube, float height, float width)
{
    cube->x = width / 2;
    cube->y = height / 2;
    cube->isMoving = 0;
    cube->speed_x = 0;
    cube->speed_y = 0;
}

// ################### BAR

void drawBar(struct Bar *bar)
{
    glBegin(GL_QUADS);

    glVertex2f(bar->x, bar->y);                   // top left
    glVertex2f(bar->x + bar->w, bar->y);          // top right
    glVertex2f(bar->x + bar->w, bar->y + bar->h); // bottom right
    glVertex2f(bar->x, bar->y + bar->h);          // bottom left

    glEnd();
}

void make_point(struct Bar *this, struct Bar *other)
{
    this->points++;
    this->last_winner = 1;
    other->last_winner = 0;
}

void up(struct Bar *this, float height)
{
    if (!(this->y <= 0))
    {
        this->y -= this->speed;
    }
}

void down(struct Bar *this, float height)
{
    if (!(this->y + this->h >= height))
    {
        this->y += this->speed;
    }
}
