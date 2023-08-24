#include <stdio.h>
#include <GL/glut.h>
#include "Bar.h"

void drawBar(struct Bar *bar)
{
    glBegin(GL_QUADS);

    glVertex2f(bar->x, bar->y);                   // top left
    glVertex2f(bar->x + bar->w, bar->y);          // top right
    glVertex2f(bar->x + bar->w, bar->y + bar->h); // bottom right
    glVertex2f(bar->x, bar->y + bar->h);          // bottom left

    glEnd();
}

void make_point(struct Bar *this, struct Bar *other) {
    this->points++;
    this->last_winner = 1;
    other->last_winner = 0;
}
