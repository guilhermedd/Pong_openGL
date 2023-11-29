// OpenGL
#include <GL/glut.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <stdio.h>
#endif

#include "Pieces.h"

#define WIDTH 1200
#define HEIGHT 800

#define BAR_HEIGHT 300
#define CUBE_SPEED 0.5
#define BAR_Y (HEIGHT / 2) - (BAR_HEIGHT / 2)
#define BAR_SPEED 20
#define BAR_WIDTH 15
#define BAR_X 30

FILE *file;

struct Bar left = {BAR_X, BAR_Y, BAR_WIDTH, BAR_HEIGHT, BAR_SPEED, 0, 0};
struct Bar right = {WIDTH - BAR_X - BAR_WIDTH, BAR_Y, BAR_WIDTH, BAR_HEIGHT, 0.2, 0, 0};
struct Cube cube = {WIDTH / 2, HEIGHT / 2, 30, 0.0, 0.0, 0}; // x, y, size, speed_x, speed_y, isMoving
int activeScreen = 0;

void update(struct Cube *cube, struct Bar *left, struct Bar *right);

// User arrow keys to move the bar
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (left.y <= 0)
            break;
        up(&left, HEIGHT);
        break;
    case GLUT_KEY_DOWN:
        if (left.y + left.h >= HEIGHT)
            break;
        down(&left, HEIGHT);
        break;
    }
}

// Use keyboard to move and to start the game
void keyboard(unsigned char key, int x, int y)
{
    const float cameraSpeed = 0.1f;

    switch (key)
    {
    case ' ':
        if (cube.isMoving)
            break;
        if (left.last_winner == 1)
        {
            cube.isMoving = 1;
            cube.speed_x = CUBE_SPEED;
            cube.speed_y = CUBE_SPEED + 0.1;
        }
        else
        {
            cube.isMoving = 1;
            cube.speed_x = -CUBE_SPEED;
            cube.speed_y = CUBE_SPEED + 0.1;
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

// function to draw text on screen.
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

// myInit function for initializing values
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

// function to display animation
void update(struct Cube *cube, struct Bar *left, struct Bar *right)
{
    updateCube(cube, HEIGHT, WIDTH, left, right); // Update ball position
}

// Write the highest points in scores.bin
void writeScore(int playerScore, int botScore)
{
    FILE *arquivo;
    arquivo = fopen("../Assets/scores.txt", "wb");

    if (arquivo != NULL)
    {
        fprintf(arquivo, "%d - %d", playerScore, botScore);
        fclose(arquivo);
    }
    else
    {
        printf("Não foi possível abrir o arquivo para escrita.\n");
    }
}

// function to display animation
void displayEasy(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    drawText(WIDTH / 2 - 35, 50, "- PONG - ", 500);

    drawCube(&cube);

    drawBar(&left);

    drawBar(&right);

    update(&cube, &left, &right);

    // The bot points
    if (cube.x <= 0)
    {
        make_point(&right, &left);
        writeScore(left.points, right.points);
    }

    // We point
    else if (cube.x >= WIDTH)
    {
        make_point(&left, &right);
        writeScore(left.points, right.points);
    }

    drawCube(&cube); // Draw the cube with the updated position

    /////////////// "AI"
    if (cube.y > right.y + right.h)
        down(&right, HEIGHT);

    if (cube.y < right.y)
        up(&right, HEIGHT);

    char left_points[20];
    sprintf(left_points, "%d", left.points);

    char right_points[20];
    sprintf(right_points, "%d", right.points);

    drawText(WIDTH / 2 - 70, 50, left_points, 500);
    drawText(WIDTH / 2 + 95, 50, right_points, 500);

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

// function to display animation
void displayHard(void)
{

    right.speed = 4;

    glClear(GL_COLOR_BUFFER_BIT);

    drawText(WIDTH / 2 - 35, 50, "- PONG - ", 500);

    drawCube(&cube);

    drawBar(&left);

    drawBar(&right);

    update(&cube, &left, &right);

    if (cube.x <= 0)
    {
        make_point(&left, &right);
    }
    else if (cube.x >= WIDTH)
    {
        make_point(&right, &left);
    }
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

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

// function to start game
void keyboardMenu(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        activeScreen = 1;
        glutDestroyWindow(1);
        glutCreateWindow("Facil");
        myInit();
        glutDisplayFunc(displayEasy);
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(specialKeys);
        break;
    case '2':
        activeScreen = 2;
        printf(" Em desenvolvimento🤓 \n");
        glutCreateWindow("Dificil");
        myInit();
        glutDisplayFunc(displayHard);
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(specialKeys);
        break;
    case '3':
        glutDestroyWindow(1); // Fecha a janela de menu
        break;
    default:
        break;
    }
}

// function to read the scores.txt file
char *lerArquivoScores()
{
    FILE *file = fopen("../Assets/scores.txt", "rb");

    if (!file)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer)
    {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    fclose(file);
    return buffer;
}

// function to display menu
void displayMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Carrega a textura da imagem
    GLuint textureID = SOIL_load_OGL_texture(
        "/home/debian/Documents/opengl/pong/Pong_openGL/Assets/mario.png", // Caminho para a imagem
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_COMPRESS_TO_DXT);
    if (textureID == 0)
    {
        printf("Erro ao carregar a textura da imagem.\n");
    }

    // Habilita o mapeamento de textura 2D
    glEnable(GL_TEXTURE_2D);

    // Vincula a textura carregada
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Desenha a textura como plano de fundo
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Desativa o mapeamento de textura 2D antes de desenhar o texto
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0); // Cor do texto
    char texto[100];
    sprintf(texto, "Ultima pontuacao:\t");
    glRasterPos2i(100, HEIGHT - 400);
    for (int i = 0; texto[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
    }

    char *conteudoScores = lerArquivoScores();
    if (conteudoScores)
    {
        glRasterPos2i(300, HEIGHT - 400);
        for (int i = 0; conteudoScores[i] != '\0'; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, conteudoScores[i]);
        }
        free(conteudoScores);
    }
    else
    {
        // Trate o caso em que o arquivo não pode ser lido
        glRasterPos2i(100, HEIGHT - 175);
        char erro[] = "Erro ao ler o arquivo scores.txt";
        for (int i = 0; erro[i] != '\0'; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, erro[i]);
        }
    }

    sprintf(texto, "Selecione uma opcao:");
    glRasterPos2i(100, HEIGHT - 200);
    for (int i = 0; texto[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
    }
    sprintf(texto, "1 - Jogar Facil");
    glRasterPos2i(100, HEIGHT - 150);
    for (int i = 0; texto[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
    }
    sprintf(texto, "2 - Jogar Dificil");
    glRasterPos2i(100, HEIGHT - 100);
    for (int i = 0; texto[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
    }
    sprintf(texto, "3 - Sair");
    glRasterPos2i(100, HEIGHT - 50);
    for (int i = 0; texto[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, texto[i]);
    }

    glutSwapBuffers();
}

// Driver Program
int main(int argc, char **argv)
{

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        return 1;
    }
    Mix_Music *musica = Mix_LoadMUS("../Assets/ye_flashing_lights.mp3");
    if (!musica)
    {
        return 1;
    }
    Mix_PlayMusic(musica, -1);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // giving window size in X- and Y- direction
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Menu");
    myInit();
    glutDisplayFunc(displayMenu);
    glutKeyboardFunc(keyboardMenu);
    glutMainLoop();

    Mix_FreeMusic(musica);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
