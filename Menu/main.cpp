#pragma warning (disable: 4996)

#include "GL/glut.h"
#include "MenuView.h"
#include "Rectangle.h"
#include "boost/signals2.hpp"

void reshape(int w, int h);
void display();
void idle();
void mouseFunc(int button, int state, int x, int y);

static MenuView* MENU_VIEW = nullptr;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Menu");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouseFunc);

    MENU_VIEW = new MenuView(argc, argv, "empty");

    glutMainLoop();
    return 0;
}


void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (MENU_VIEW != nullptr)
    {
        MENU_VIEW->displayView();
    }

    glutSwapBuffers();
    glutPostRedisplay();
}
void idle()
{
    
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
        MENU_VIEW->processLeftClick(Point{ (double)x,(double)y });
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    case GLUT_MIDDLE_BUTTON:
        break;
    default:
        break;
    }
}