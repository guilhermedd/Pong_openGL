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
