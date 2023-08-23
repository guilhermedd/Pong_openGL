// C program to demonstrate
// drawing a circle using
// OpenGL
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "Bar.h"
#include "Ball.h"

#define WIDTH 1000
#define HEIGHT 800
#define pi 3.142857

// function to initialize
void myInit(void)
{
    // making background color black as first
    // 3 arguments all are 0.0
    glClearColor(0.0, 0.0, 0.0, 1.0);
    // making picture color green (in RGB mode), as middle argument is 1.0
    glColor3f(0.0, 1.0, 0.0);
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

    struct Bar left = { 30 , HEIGHT / 4, 15, 300, 0}; // x, y, w, h, speed
    drawBar(&left);

    struct Bar right = {WIDTH - 40, HEIGHT / 4, 15, 300, 0}; // x, y, w, h, speed
    drawBar(&right);

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
