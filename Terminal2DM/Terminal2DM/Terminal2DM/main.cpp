#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 40, 0, 40, 0, 20);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(1, 38);
    string line1 = "DISCRETE MATHEMATICS";
    for (char c : line1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
    glRasterPos2f(1, 34);
    string  line2 = "1. Set Theory and Logic.";
    for (char c : line2) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    glRasterPos2f(1, 31);
    string  line3 = "2. Relations and Functions.";
    for (char c : line3) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    glRasterPos2f(1, 28);
    string  line4 = "3. Counting Principles.";
    for (char c : line4) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    glRasterPos2f(1, 25);
    string  line5 = "4. Graph Theory.";
    for (char c : line5) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    glRasterPos2f(1, 22);
    string  line6 = "5. Trees.";
    for (char c : line6) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    glRasterPos2f(1, 19);
    string  line7 = "6. Algebraic Structures and Coding Theory.";
    for (char c : line7) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    glRasterPos2f(1, 9);
    string  line8 = "Choose any lesson (1/6)";
    for (char c : line8) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    glFlush();
}

void display_line(const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cerr << "Failed to open the file: " << filename << endl;
    }
}

void keyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        display_line("D:\\SUB\\DM\\lesson1.txt");
        break;
    case '2':
        display_line("D:\\SUB\\DM\\lesson2.txt");
        break;
    case '3':
        display_line("D:\\SUB\\DM\\lesson3.txt");
        break;
    case '4':
        display_line("D:\\SUB\\DM\\lesson4.txt");
        break;
    case '5':
        display_line("D:\\SUB\\DM\\lesson5.txt");
        break;
    case '6':
        display_line("D:\\SUB\\DM\\lesson6.txt");
        break;
    case 27: // Escape key
        exit(0);
        break;
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(900, 500);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Text within Rectangle");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardCallback);
    glutMainLoop();
    return 0;
}
