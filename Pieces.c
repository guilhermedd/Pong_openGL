#include "Pieces.h"

GLfloat white_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0}; // Posição da fonte de luz
GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};    // Cor da luz
GLfloat lmodel_ambient[] = {0.1, 0.1, 1, 1.0}; // Cor ambiente global

void drawCube(struct Cube *cube)
{

    glPushMatrix();    
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.2f, 0.2f);
    glVertex2f(cube->x, cube->y);                           // top left
    glVertex2f(cube->x + cube->size, cube->y);              // top right
    glVertex2f(cube->x + cube->size, cube->y + cube->size); // bottom right
    glVertex2f(cube->x, cube->y + cube->size);              // bottom left
    glEnd();


}


void drawSphere(struct Cube *cube) {
    float centerX = cube->x + cube->size / 2.0;
    float centerY = cube->y + cube->size / 2.0;
    
    // Calcule o raio da esfera circunscrita ao cubo
    float radius = cube->size / sqrt(3.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, 1.0, 1.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade
    
    glEnable(GL_LIGHTING);  // Habilita iluminação
    glEnable(GL_LIGHT0);    // Habilita a fonte de luz 0
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glPushMatrix();
    glColor3f(1.0f, 0.3f, 0.1f);
    glTranslatef(centerX, centerY, 0.0f); // Mova para o centro do cubo

    // Defina as propriedades do material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse);

    // Desenhe a esfera
    GLUquadric *pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    gluSphere(pObj, radius, 30, 30); // Use o raio calculado
    gluDeleteQuadric(pObj);

    glPopMatrix();
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

    glPushMatrix();

    glBegin(GL_QUADS);

    glColor3f(0.1f, 1.0f, 0.1f);

    glVertex2f(bar->x, bar->y);                   // top left
    glVertex2f(bar->x + bar->w, bar->y);          // top right
    glVertex2f(bar->x + bar->w, bar->y + bar->h); // bottom right
    glVertex2f(bar->x, bar->y + bar->h);          // bottom left

    glEnd();

    glPopMatrix();
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
