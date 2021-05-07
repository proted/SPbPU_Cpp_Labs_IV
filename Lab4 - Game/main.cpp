#pragma warning (disable: 4996)

#include "GL/glut.h"
#include "MenuView.h"
#include "Rectangle.h"

void reshape(int w, int h);
void display();
void idle();
void mouseFunc(int button, int state, int x, int y);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);

static MenuView* MENU_VIEW = nullptr;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Game");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouseFunc);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);

    MENU_VIEW = new MenuView("GameStructure.json");

    glutMainLoop();
    return 0;
}


void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (MENU_VIEW != nullptr)
    {
        MENU_VIEW->display();
    }

    glutSwapBuffers();
    glutPostRedisplay();
}
void idle()
{
    MENU_VIEW->processIdle();
}
void mouseFunc(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_UP)
        {
            break;
        }
        prtd_ct::Point pt = prtd_ct::Point{ (double)x, 720.0 - (double)y };
        MENU_VIEW->processLeftClick(pt);
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    case GLUT_MIDDLE_BUTTON:
        break;
    default:
        break;
    }
}
void keyboardFunc(unsigned char key, int x, int y)
{
    MENU_VIEW->processKeyboard(key);
}
void specialFunc(int key, int x, int y)
{
    MENU_VIEW->processSpecial(key);
}