#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <GL/gl.h>
#include <fstream>
#include <string>

using namespace std;

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 500

GLfloat lineVertices[] = {
    50 * 4, 20 * 4, 0,
    80 * 4, 20 * 4, 0,
    80 * 4, 50 * 4, 0,
    50 * 4, 50 * 4, 0,
    50 * 4, 20 * 4, 0,

    100 * 4, 20 * 4, 0,
    130 * 4, 20 * 4, 0,
    130 * 4, 50 * 4, 0,
    100 * 4, 50 * 4, 0,
    100 * 4, 20 * 4, 0,

    150 * 4, 20 * 4, 0,
    180 * 4, 20 * 4, 0,
    180 * 4, 50 * 4, 0,
    150 * 4, 50 * 4, 0,
    150 * 4, 20 * 4, 0,

    70 * 4, 70 * 4, 0,
    100 * 4, 70 * 4, 0,
    100 * 4, 100 * 4, 0,
    70 * 4, 100 * 4, 0,
    70 * 4, 70 * 4, 0,

    130 * 4, 70 * 4, 0,
    160 * 4, 70 * 4, 0,
    160 * 4, 100 * 4, 0,
    130 * 4, 100 * 4, 0,
    130 * 4, 70 * 4, 0
};

struct Box {
    double x1, y1, x2, y2;
    const char* filename;
};

Box boxes[5] = {
    {50 * 4, 480 - 50 * 4, 80 * 4, 480 - 20 * 4, "H:\\Miniproject\\Terminal2OOP\\Terminal2OOP\\x64\\Debug\\Terminal2OOP.exe"},
    {100 * 4, 480 - 50 * 4, 130 * 4, 480 - 20 * 4, "H:\\Miniproject\\Terminal2FDS\\Terminal2FDS\\x64\\Debug\\Terminal2FDS.exe"},
    {150 * 4, 480 - 50 * 4, 180 * 4, 480 - 20 * 4, "H:\\Miniproject\\Terminal2DM\\Terminal2DM\\x64\\Debug\\Terminal2DM.exe"},
    {70 * 4, 480 - 100 * 4, 100 * 4, 480 - 70 * 4, "H:\\Miniproject\\Terminal2CG\\Terminal2CG\\x64\\Debug\\Terminal2CG.exe"},
    {130 * 4, 480 - 100 * 4, 160 * 4, 480 - 70 * 4, "H:\\Miniproject\\Terminal2DELD\\Terminal2DELD\\x64\\Debug\\Terminal2DELD.exe"}
};


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        xpos /= SCREEN_WIDTH;
        ypos /= SCREEN_HEIGHT;

        for (int boxIndex = 0; boxIndex < 5; boxIndex++) {
            double x1 = boxes[boxIndex].x1 / SCREEN_WIDTH;
            double y1 = boxes[boxIndex].y1 / SCREEN_HEIGHT;
            double x2 = boxes[boxIndex].x2 / SCREEN_WIDTH;
            double y2 = boxes[boxIndex].y2 / SCREEN_HEIGHT;

            if (xpos >= x1 && xpos <= x2 && ypos >= y1 && ypos <= y2) {
                const char* command = boxes[boxIndex].filename;
                std::system(command);
            }
        }
    }
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Terminal1", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cerr << "GLEW initialization failed" << endl;
        return -1;
    }

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, lineVertices);

        for (int i = 0; i < 5; i++) {
            glDrawArrays(GL_LINE_LOOP, i * 5, 5);
        }

        glDisableClientState(GL_VERTEX_ARRAY);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
