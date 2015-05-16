#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>

#include "CustomFunctions.h"
#include "Point.h"
#include "Object.h"

#include "Wind.h"
#include "Wire.h"
#include "TempSensor.h"
#include "Turbine.h"
#include "Controller.h"
#include "Boiler.h"
#include "Pipe.h"
#include "Valve.h"

#define ADOffset 10
#define ADHeight 110

Wind wind;
TempSensor TT;
Turbine turbine;
Controller TIC;
Wire TT_TIC;
Boiler boiler;
Pipe boiler_wind[4];
Controller PrI;
Valve oilValve;
Pipe boiler_;
Valve pressureValve;
Wire w[10];

long long oldTimeStamp = 0;

void init_objects() {
    TT.placement(40, 40 + ADOffset, 100, ADHeight + ADOffset - 40);

    turbine.placement(400, ADOffset + ADHeight / 2.0, ADHeight / 2.0);

    TIC.placement(30, 340, 180, 450);

    TT_TIC.placement(mean(TT.getStartX(), TT.getEndX()), TT.getEndY(), mean(TT.getStartX(), TT.getEndX()) ,400);

    wind.placement(ADOffset, ADOffset, WIDTH - ADOffset, ADOffset + ADHeight);

    boiler.placement(280, 220, 445, 330);

    boiler_wind[0].placement(mean(280, 445), mean(220, 330), 248, 152);
    boiler_wind[1].placement(248, 152, 248, 5);
    boiler_wind[2].placement(240, 5, 281, 280);
    boiler_wind[3].placement(248, 5, 240, 5);

    PrI.placement(300 , 390, 400, 440);
    PrI.sensePressure();

    oilValve.placement(mean(280, 445), mean(220, 330) - 80, 20);

    boiler_.placement(mean(280, 445), mean(220, 330), WIDTH, 375);
    pressureValve.placement(444, 375, 20);
    w[0].placement(mean (280, 445) - 20, mean(220, 330), mean(300, 400), mean(390, 440)); // Boiler_PrI
    w[1].placement(444, 375, mean(300, 400), mean(390, 440)); // Pressure Indicator_ PerssureValve
    w[2].placement(mean(40, 100), mean(40 + ADOffset, ADHeight + ADOffset - 40), mean(280, 445), mean(220, 330) - 80);
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);

    init_objects();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Wind
    wind.draw();

    // Wires
    w[0].draw();
    w[1].draw();
    w[2].draw();

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

    // Boiler_Wind pipe
    boiler_wind[0].draw();
    boiler_wind[1].draw();
    boiler_wind[2].draw();
    boiler_wind[3].draw();

    // Pressure Release Pipe
    boiler_.draw();

    // Pressure Valve;
    pressureValve.draw();

    // Boiler
    boiler.draw();

    // Pressure Indicator
    PrI.draw();

    // Oil Valve
    oilValve.draw();

    glPopMatrix();
    glutSwapBuffers();
}

void tick(void) {
    if (clock() > oldTimeStamp + 10){
        oldTimeStamp = clock();

        wind.update(); // The wind is slowly getting colder

        TT.senseTemperature(wind); // The sensor senses the wind's temperature
        TIC.setValue(TT.transmitTemperature()); // The Controller reads the temperature from the sensor

        boiler.update(); // The boiler is slowly getting hotter
        PrI.setValue(boiler.getPressure()); // Transmit the boilers pressure

        if (TIC.getValue() < 40) oilValve.open();
        else if (TIC.getValue() > 60) oilValve.close();

        // Oil Valve
        if (oilValve.isOpen()){
            wind.heat(0.05);
            boiler_wind[0].isFlowing(true);
            boiler_wind[1].isFlowing(true);
            boiler_wind[2].isFlowing(true);
            boiler_wind[3].isFlowing(true);

        }
        else{
            boiler_wind[0].isFlowing(false);
            boiler_wind[1].isFlowing(false);
            boiler_wind[2].isFlowing(false);
            boiler_wind[3].isFlowing(false);
        }

        if (PrI.getValue() > 55) pressureValve.open();
        else if (PrI.getValue() < 35) pressureValve.close();

        if (pressureValve.isOpen()){
            boiler.releasePressure(0.05);
            boiler_.isFlowing(true);
        }
        else{
            boiler_.isFlowing(false);
        }

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
    if (state == GLUT_DOWN){
        std::cout << "X = " << x << std::endl << "Y = " << HEIGHT - y << std::endl;
    }
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
