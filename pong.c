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
struct Cube cube = {WIDTH / 2, HEIGHT / 2, 30, 0.1, 0.1}; // x, y, size, speed_x, speed_y

void timerCallback(int value);
void update(struct Cube *cube);

void timerCallback(int value)
{
    update(&cube);
    glutPostRedisplay();
    glutTimerFunc(16, timerCallback, 0);
}

void drawText(float x, float y, const char *string, int size)
{
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);

    while (*string)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string);
        string++;
    }
}
// function to initialize
void myInit(void)
{
    // making background color black as first
    // 3 arguments all are 0.0
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glViewport(0, 0, WIDTH, HEIGHT);

    // making picture color green (in RGB mode), as middle argument is 1.0
    glColor3f(1.0, 1.0, 1.0);
    // breadth of picture boundary is 1 pixel
    glPointSize(1.0);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // setting window dimension in X- and Y- direction
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
}

void update(struct Cube *cube)
{
    updateCube(cube);                 // Update ball position
    // Call update again after 16 ms (approximately 60 fps)
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawText(WIDTH / 2 - 35, 50, "- PONG - ", 500);

    drawCube(&cube);

    float height = 300, y = (HEIGHT / 2) - (height / 2), speed = 0, width = 15, x = 30;

    struct Bar left = {x, y, width, height, speed, 0};
    drawBar(&left);

    struct Bar right = {WIDTH - x - width, y, width, height, speed, 0};
    drawBar(&right);

    update(&cube);   // Update the cube's position
    drawCube(&cube); // Draw the cube with the updated position

    char right_points[20];
    sprintf(right_points, "%d", right.points);

    char left_points[20];
    sprintf(left_points, "%d", left.points);
    drawText(WIDTH / 2 - 70, 50, right_points, 500);
    drawText(WIDTH / 2 + 95, 50, left_points, 500);

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
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
