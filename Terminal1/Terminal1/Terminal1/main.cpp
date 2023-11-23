#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <windows.h>
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
    const char* filename; // Add a filename field for each square
};

Box boxes[5] = {
    {50 * 4, 480 - 50 * 4, 80 * 4, 480 - 20 * 4, "D:\\Projects\\MiniProj\\t2oop.cpp"},
    {100 * 4, 480 - 50 * 4, 130 * 4, 480 - 20 * 4, "D:\\Projects\\MiniProj\\t2fds.cpp"},
    {150 * 4, 480 - 50 * 4, 180 * 4, 480 - 20 * 4, "D:\\Projects\\MiniProj\\t2dm.cpp"},
    {70 * 4, 480 - 100 * 4, 100 * 4, 480 - 70 * 4, "D:\\Projects\\MiniProj\\t2cg.cpp"},
    {130 * 4, 480 - 100 * 4, 160 * 4, 480 - 70 * 4, "D:\\Projects\\MiniProj\\t2deld.cpp"}
};


static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
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
                const char* filename = boxes[boxIndex].filename;
                char command[256]; // Create a char array to store the command
                snprintf(command, sizeof(command), "g++ your_program.cpp -o compiled -lGL -lglut -lGLU", filename); // Format the command

                int result = system(command);

                if (result == 0) {
                    cout << "Program compiled and executed successfully." << endl;
                }
                else {
                    cerr << "Compilation or execution failed." << endl;
                }
            }
        }
    }
}

int main(void) {
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Terminal1", NULL, NULL);

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalized to pixels
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

    // projection matrix defines the properties of the camera that views the objects in the world coordinate frame.
    glMatrixMode(GL_PROJECTION);

    // replace the current matrix with the identity matrix and starts us fresh because matrix transforms such as glOrtho and glRotate cumulate, basically puts us at (0, 0, 0)
    glLoadIdentity();

    // essentially set the coordinate system
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);

    // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation, and scaling) in your world
    glMatrixMode(GL_MODELVIEW);

    // same as above comment
    glLoadIdentity();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, lineVertices);

        // Render the squares
        for (int i = 0; i < 5; i++) {
            glDrawArrays(GL_LINE_LOOP, i * 5, 5);
        }

        glDisableClientState(GL_VERTEX_ARRAY);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}