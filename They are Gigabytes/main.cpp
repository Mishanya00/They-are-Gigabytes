#include <iostream>

#include <glew.h>
#include <glut.h>

#include "math_3d.h"
#include "world_transform.hpp"
#include "camera.hpp"
#include "shaders.hpp"
#include "draw_subsystem.hpp"
#include "game_kernel.hpp"


static void KeyboardHandler(unsigned char key, int x, int y)
{
    GameCamera.OnKeyboard(key);

    switch (key)
    {
    case 27:
        exit(0);
        break;

    case 'q':
    case 'Q':
        WorldMatrix.Rotate(0, 10.0f, 0);
        break;

    case 'e':
    case 'E':
        WorldMatrix.Rotate(0, -10.0f, 0);
        break;

    case '1':
        glBindVertexArray(CubeVAO);
        break;
    case '2':
        glBindVertexArray(PyramidVAO);
        break;
    case '3':
        glBindVertexArray(0);
        break;
    }
}

static void KeyboardSpecialHandler(int key, int x, int y)
{
    GameCamera.OnKeyboard(key);
   
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
    switch (button)
    {   // mouse wheel lacks special const to determine. So according to docs its 3 and 4
    case 3:
        WorldMatrix.Scale(1.1f);
        break;
    case 4:
        WorldMatrix.Scale(0.9f);
        break;
    }
}

static void PassiveMotionHandler(int x, int y)
{
    //std::cout << x << ' ' << y << '\n';
    GameCamera.OnMouse(x, y);
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

    InitGameKernel();
    DrawSubsystemInit();

    CompileShaders();

    InitGameKernel();

    RegisterGlutCallbacks();

    glutMainLoop();
}