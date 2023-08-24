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

#define BAR_HEIGHT 300
#define BAR_Y (HEIGHT / 2) - (BAR_HEIGHT / 2)
#define BAR_SPEED 0
#define BAR_WIDTH 15
#define BAR_X 30

struct Bar left = {BAR_X, BAR_Y, BAR_WIDTH, BAR_HEIGHT, BAR_SPEED, 0, 0};
struct Bar right = {WIDTH - BAR_X - BAR_WIDTH, BAR_Y, BAR_WIDTH, BAR_HEIGHT, BAR_SPEED, 0, 0};
struct Cube cube = {WIDTH / 2, HEIGHT / 2, 30, 0.0, 0.0, 0}; // x, y, size, speed_x, speed_y, isMoving

void timerCallback(int value);
void update(struct Cube *cube);

void keyboard(unsigned char key, int x, int y)
{
    const float cameraSpeed = 0.1f;

    switch (key)
    {
        case ' ':
            if (cube.isMoving)
                break;
            if (!cube.isMoving && left.last_winner){
                cube.isMoving = 1;
                cube.speed_x = 0.05;
                cube.speed_y = 0.1;
            } else {
                cube.isMoving = 1;
                cube.speed_x = -0.05;
                cube.speed_y = 0.1;
            }
                break;
    }

    glutPostRedisplay();
}

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
    updateCube(cube, HEIGHT, WIDTH);                 // Update ball position
    // Call update again after 16 ms (approximately 60 fps)
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    drawText(WIDTH / 2 - 35, 50, "- PONG - ", 500);

    drawCube(&cube);

    drawBar(&left);

    drawBar(&right);


    if (cube.x <= 0)
        make_point(&left, &right);
    else if (cube.x >= WIDTH)
        make_point(&right, &left);
    update(&cube);   // Update the cube's position
    drawCube(&cube); // Draw the cube with the updated position

    // printf("Pontos direita: %i | Pontos esquerda: %i\n", right.points, left.points);

    char left_points[20];
    sprintf(left_points, "%d", left.points);

    char right_points[20];
    sprintf(right_points, "%d", right.points);


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
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
