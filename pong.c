// C program to demonstrate
// drawing a circle using
// OpenGL
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "Pieces.h"

#define WIDTH 1200
#define HEIGHT 800
#define pi 3.142857

#define BAR_HEIGHT 300
#define BAR_Y (HEIGHT / 2) - (BAR_HEIGHT / 2)
#define BAR_SPEED 20
#define BAR_WIDTH 15
#define BAR_X 30

struct Bar left = {BAR_X, BAR_Y, BAR_WIDTH, BAR_HEIGHT, BAR_SPEED, 0, 0};
struct Bar right = {WIDTH - BAR_X - BAR_WIDTH, BAR_Y, BAR_WIDTH, BAR_HEIGHT, 0.05, 0, 0};
struct Cube cube = {WIDTH / 2, HEIGHT / 2, 30, 0.0, 0.0, 0}; // x, y, size, speed_x, speed_y, isMoving

// void timerCallback(int value);
void update(struct Cube *cube, struct Bar *left, struct Bar *right);

void keyboardUp(unsigned char key, int x, int y)
{
    // Callback chamado quando uma tecla é liberada (key_released)
    switch (key)
    {
    case GLUT_KEY_UP: // Tecla ESPAÇO
        printf("LIBEROUUU\n");
        break;
        // Outras teclas podem ser tratadas aqui
    }
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        printf("CIMAAAA\n");
        break;
    case GLUT_KEY_DOWN:
        // A seta para baixo foi pressionada
        break;
    case GLUT_KEY_LEFT:
        // A seta para a esquerda foi pressionada
        break;
    case GLUT_KEY_RIGHT:
        // A seta para a direita foi pressionada
        break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    const float cameraSpeed = 0.1f;

    switch (key)
    {
    case ' ':
        if (cube.isMoving)
            break;
        if (!cube.isMoving && left.last_winner)
        {
            cube.isMoving = 1;
            cube.speed_x = 0.1;
            cube.speed_y = 0.1;
        }
        else
        {
            cube.isMoving = 1;
            cube.speed_x = -0.1;
            cube.speed_y = 0.1;
        }
        break;
    case 'w':
        if (left.y <= 0)
            break;
        up(&left, HEIGHT);
        break;
    case 's':
        if (left.y + left.h >= HEIGHT)
            break;
        down(&left, HEIGHT);
        break;
    }

    glutPostRedisplay();
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

void update(struct Cube *cube, struct Bar *left, struct Bar *right)
{
    updateCube(cube, HEIGHT, WIDTH, left, right); // Update ball position
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    drawText(WIDTH / 2 - 35, 50, "- PONG - ", 500);

    drawCube(&cube);

    drawBar(&left);

    drawBar(&right);

    update(&cube, &left, &right);

    if (cube.x <= 0)
        make_point(&left, &right);
    else if (cube.x >= WIDTH)
        make_point(&right, &left);
    drawCube(&cube); // Draw the cube with the updated position

    /////////////// "AI"
    if (cube.y > right.y + right.h)
        down(&right, HEIGHT);

    if (cube.y < right.y)
        up(&right, HEIGHT);

    // printf("Pontos direita: %i | Pontos esquerda: %i\n", right.points, left.points);

    char left_points[20];
    sprintf(left_points, "%d", left.points);

    char right_points[20];
    sprintf(right_points, "%d", right.points);

    drawText(WIDTH / 2 - 70, 50, right_points, 500);
    drawText(WIDTH / 2 + 95, 50, left_points, 500);

    // to use in AI
    printf("%f, %f, %f, %f, %f\n", left.y, cube.x, cube.y, cube.speed_x, cube.speed_y); // bar.x, cube.x, cube.y, cube.speed_x, cube.speed_y

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
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
}
