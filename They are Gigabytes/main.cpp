#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>

#include "interface.hpp"
#include "math_3d.h"
#include "game_kernel.hpp"
#include "audio.hpp"

MiniaudioEngine player;

static int glMajorVersion = 0;
static int glMinorVersion = 0;


static void LibInitGLFW()
{
    if (glfwInit() != 1) {
        std::cerr << "Error initializing GLFW";
        exit(1);
    }

    int Major, Minor, Rev;
    glfwGetVersion(&Major, &Minor, &Rev);
    std::cout << "GLFW " << Major << "." << Minor << "." << Rev << "." << " initialized\n";
}

// Must be done after glfw is initialized!
static void InitGLEW()
{
    glewExperimental = GL_TRUE;
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        std::cerr << (const char*)glewGetErrorString(res);
        exit(1);
    }
}

GLFWwindow* InitGLFW(int major_ver, int minor_ver, int width, int height, bool is_full_screen, const char* title)
{
    LibInitGLFW();

    GLFWmonitor* monitor = is_full_screen ? glfwGetPrimaryMonitor() : NULL;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    if (major_ver > 0) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_ver);
    }

    if (minor_ver > 0) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_ver);
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, NULL);

    if (!window) {
        const char* pDesc = NULL;
        int error_code = glfwGetError(&pDesc);

        perror("Error creating window");
        exit(1);
    }

    glfwMakeContextCurrent(window);

    // The following functions must be called after the context is made current
    glGetIntegerv(GL_MAJOR_VERSION, &glMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &glMinorVersion);

    if (major_ver > 0) {
        if (major_ver != glMajorVersion) {
            std::cerr << "Requested major version %d is not the same as created version %d";
            exit(0);
        }
    }

    if (minor_ver > 0) {
        if (minor_ver != glMinorVersion) {
            std::cerr << "Requested minor version %d is not the same as created version %d";
            exit(0);
        }
    }

    InitGLEW();

    glfwSwapInterval(1);

    return window;
}

static void MouseHandler(int button, int state, int x, int y)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
        player.Play("contents/Audio/click.wav");
    if (button == GLFW_MOUSE_BUTTON_RIGHT && state == GLFW_PRESS)
        player.Play("contents/Audio/click2.wav");

    GameMouseHandler(button, state, x, y);
}

static void RenderScene(GLFWwindow* window)
{
    static const double fixed_timestep = 1.0 / 60.0;
    static double accumulated_time = 0.0;
    static double previous_time = glfwGetTime();
    static double current_time;
    static double frame_time;

    current_time = glfwGetTime();
    frame_time = current_time - previous_time;
    previous_time = current_time;
    accumulated_time += frame_time;

    while (accumulated_time >= fixed_timestep) {
        GameFrame();
        accumulated_time -= fixed_timestep;
    }

    DrawGameFrame();

    DrawInterface();

    glfwSwapBuffers(window);

    glfwPollEvents();
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << key << '\n';
    GameKeyboardHandler(key, action);
}

static void CursorPosCallback(GLFWwindow* window, double x, double y)
{
    GamePassiveMotionHandler((int)x, (int)y);
}

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        player.Play("contents/Audio/click.wav");
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        player.Play("contents/Audio/click2.wav");

    GameMouseHandler(button, action, (int)x, (int)y);
}

static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    GameMouseScrollHandler(yoffset);
}

static void RegisterCallbacks(GLFWwindow * window)
{
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetScrollCallback(window, MouseScrollCallback);
}

static void ImGuiInit(GLFWwindow * window)
{
    GUI::Init();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330"); // Here is GLSL version
}

int main(int argc, char** argv)
{
    bool isFullScreen = true;

#ifdef _DEBUG
    isFullScreen = false;
#endif

    GLFWwindow* Window;

    Window = InitGLFW(0, 0, 1920, 1080, isFullScreen, "They Are Gigabytes");
    RegisterCallbacks(Window);
    ImGuiInit(Window);

    GameKernelInit();
    GameInterfaceInit();
    //player.Play("contents/Audio/main_theme.mp3");

    while (!glfwWindowShouldClose(Window))
    {
        RenderScene(Window);
    }
    glfwTerminate();
    return 0;
}