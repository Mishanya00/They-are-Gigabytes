#include <iostream>

#include <glew.h>
#include <glut.h>

#include "math_3d.h"
#include "world_transform.hpp"
#include "camera.hpp"
#include "shaders.hpp"
#include "game_kernel.hpp"


static void KeyboardHandler(unsigned char key, int x, int y)
{
    GameCamera.OnKeyboard(key);

    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

static void KeyboardSpecialHandler(int key, int x, int y)
{
    //GameCamera.OnKeyboard(key);
   
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        WorldMatrix.Translate(0.1f, 0, 0);
        break;
    case GLUT_KEY_LEFT:
        WorldMatrix.Translate(-0.1f, 0, 0);
        break;
    case GLUT_KEY_UP:
        WorldMatrix.Translate(0, 0.1f, 0);
        break;
    case GLUT_KEY_DOWN:
        WorldMatrix.Translate(0, -0.1f, 0);
        break;
    }
}

static void MouseHandler(int button, int state, int x, int y)
{
    GameCamera.OnMouse(button, state, x, y);
}

static void PassiveMotionHandler(int x, int y)
{
    //std::cout << x << ' ' << y << '\n';
    GameCamera.OnMouse(0, 0, x, y);
}

static void UpdateWindowSize(int width, int height)
{
    ClientWidth = glutGet(GLUT_WINDOW_WIDTH);
    ClientHeight = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, ClientWidth, ClientHeight);

    std::cout << ClientWidth << ' ' << ClientHeight << '\n';

    UpdateGameWindowSize(ClientWidth, ClientHeight);
}

static void RenderScene()
{
    GameFrame();

    DrawGameFrame();

    glutSwapBuffers();

    glutPostRedisplay();
}

static void RegisterGlutCallbacks()
{
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(KeyboardHandler);
    glutSpecialFunc(KeyboardSpecialHandler);
    glutMouseFunc(MouseHandler);
    glutPassiveMotionFunc(PassiveMotionHandler);
    glutReshapeFunc(UpdateWindowSize);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    int win = glutCreateWindow("3D Transformations");
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        std::cerr << "Error '" << glewGetErrorString(res) << "'\n";
        return 1;
    }

    glutReshapeWindow(ClientWidth, ClientHeight);
    glutFullScreen();

    GameKernelInit();
    DrawSubsystemInit();

    CompileShaders();

    RegisterGlutCallbacks();

    glutMainLoop();
}