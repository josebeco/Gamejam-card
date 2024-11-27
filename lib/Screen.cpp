#include <GL/glut.h>
#include "RGB.h"
#include <Main.h>
using namespace std;

int WIDTH = 0;
int HEIGHT = 0;
int MULTIPLIAR_HEIGTH = 0;
int MULTIPLIAR_WIDTH = 0;
struct RGB *pixels = NULL;
GLubyte *realScreen = NULL;

void initGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

struct RGB getPixel(int i, int j){
    return pixels[i * WIDTH + j];
}

void setPixel(int i, int j, struct RGB rgb)
{
    pixels[i * WIDTH + j] = rgb;
}

void display()
{
    cycle();
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, realScreen);
    glutSwapBuffers();
}

void makeScreen()
{
    int position = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int im = 0; im < MULTIPLIAR_HEIGTH; im++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                for (int jm = 0; jm < MULTIPLIAR_WIDTH; jm++)
                {
                    realScreen[position++] = pixels[i * WIDTH + j].r;
                    realScreen[position++] = pixels[i * WIDTH + j].g;
                    realScreen[position++] = pixels[i * WIDTH + j].b;
                }
            }
        }
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'a':
        exit(0);
        break;
    }
}

void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(20, timer, 0); // 50 fps 1000 / 20
}

void start(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("game");
    initGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}

void init(int width, int height, int multipliar_heigth, int multipliar_width)
{
    WIDTH = width;
    HEIGHT = height;
    MULTIPLIAR_HEIGTH = multipliar_heigth;
    MULTIPLIAR_WIDTH = multipliar_width;
    pixels = new struct RGB[WIDTH * HEIGHT];
    realScreen = new GLubyte[WIDTH * HEIGHT * 3 * MULTIPLIAR_HEIGTH * MULTIPLIAR_WIDTH];
}
