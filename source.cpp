#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>

#include "CustomFunctions.h"
#include "Point.h"
#include "Wire.h"
#include "TempSensor.h"
#include "Turbine.h"
#include "Controller.h"

#define ADOffset 10
#define ADHeight 110

TempSensor TT;
Turbine turbine;
Controller TIC;
Wire TT_TIC;

long long oldTimeStamp = 0;

void init_objects() {
    TT.initialize(40, 40 + ADOffset, 100, ADHeight + ADOffset - 40);
    turbine.initialize(400, ADOffset + ADHeight / 2.0, ADHeight / 2.0);
    TIC.initialize(30, 340, 180, 470);
    TT_TIC.initialize(mean(TT.getStartX(), TT.getEndX()), TT.getEndY(), mean(TT.getStartX(), TT.getEndX()) ,400);
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    init_objects();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Air duct
    glColor3f WHITE;
    glLine(ADOffset, ADOffset, WIDTH - ADOffset, ADOffset);
    glLine(ADOffset, ADOffset + ADHeight, WIDTH - ADOffset, ADOffset + ADHeight);

    // Air sensor - controller connection
    TT_TIC.draw();

    // Air temperature sensor
    TT.draw();

    // Controller
    TIC.draw();

    // Air turbine
    glColor3f WHITE;
    turbine.draw();

    glPopMatrix();
    glutSwapBuffers();
}

void tick(void) {
    if (clock() > oldTimeStamp + 10){
        oldTimeStamp = clock();
        turbine.spinIt();
        glutPostRedisplay();
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) std::cout << "X = " << x << std::endl << "Y = " << HEIGHT - y << std::endl;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialization
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Buffers and color
    glutInitWindowSize((int)WIDTH, (int)HEIGHT); // Size
    glutInitWindowPosition (100, 100); // Window Position
    glutCreateWindow (argv[0]); // Creates the window

    init();

    glutIdleFunc(tick);

    glutDisplayFunc(display); // Display function (draw)
    glutReshapeFunc(reshape); // Activates when resizing window
    glutMouseFunc(mouse); // Mouse
    glutMainLoop(); // Main Loop
    return 0;
}
