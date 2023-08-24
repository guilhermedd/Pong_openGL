// C program to demonstrate
// drawing a circle using
// OpenGL
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "Bar.h"
#include "Cube.h"

#define WIDTH 1200
#define HEIGHT 800
#define pi 3.142857

void drawText(float x, float y, const char *string, int size)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size / 24.0, size / 24.0, 1.0); // Scale text based on size

    glColor3f(1.0, 1.0, 1.0); // Set text color to white

    while (*string)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string);
        string++;
    }

    glPopMatrix();
}

// function to initialize
void myInit(void)
{
    // making background color black as first
    // 3 arguments all are 0.0
    glClearColor(0.0, 0.0, 0.0, 1.0);
    // making picture color green (in RGB mode), as middle argument is 1.0
    glColor3f(1.0, 1.0, 1.0);
    // breadth of picture boundary is 1 pixel
    glPointSize(1.0);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // setting window dimension in X- and Y- direction
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, -1, 1);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    struct Cube cube = {WIDTH/2, HEIGHT/2, 30, 0, 0}; // x, y, size, speed_x, speed_y
    drawCube(&cube);

    float height = 300, y = (HEIGHT / 2) - (height / 2), speed = 0, width = 15, x = 30;

    struct Bar left = {x, y, width, height, speed};
    drawBar(&left);

    struct Bar right = {WIDTH - x - width, y, width, height, speed};
    drawBar(&right);

    drawText(10, 10, "PONG", 500);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // giving window size in X- and Y- direction
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);

    // Giving name to window
    glutCreateWindow("Circle Drawing");
    myInit();

    glutDisplayFunc(display);
    glutMainLoop();
}
