#ifndef CUSTOMFUNCTIONS_H_INCLUDED
#define CUSTOMFUNCTIONS_H_INCLUDED

#include <cmath>

#define PI 3.14159

#define HEIGHT 500.0
#define WIDTH 500.0

#define WHITE (1.0, 1.0, 1.0)
#define BLACK (0.0, 0.0, 0.0)
#define RED (1.0, 0.0, 0.0)
#define GREEN (0.0, 1.0, 0.0)
#define BLUE (0.0, 0.0, 1.0)

GLdouble mean(GLdouble d1, GLdouble d2) {
    return (d1 + d2) / 2.0;
}

void glDisk(GLdouble x, GLdouble y, GLdouble r) {
    glBegin(GL_POLYGON);
    for (GLdouble i = 0.0; i < 2 * PI; i += 0.1){
        glVertex2f((r * cos(i)) + x, (r * sin(i)) + y);
    }
    glEnd();
}

void glCircle(GLdouble x, GLdouble y, GLdouble r) {
    glBegin(GL_LINE_LOOP);
    for (GLdouble i = 0.0; i < 2 * PI; i += 0.1){
        glVertex2f((r * cos(i)) + x, (r * sin(i)) + y);
    }
    glEnd();
}

void glEllipse(GLdouble x, GLdouble y, GLdouble r1, GLdouble r2) {
    glBegin(GL_LINE_LOOP);
    for (GLdouble i = 0.0; i < 2 * PI; i += 0.1){
        glVertex2f((r1 * cos(i)) + x, (r2 * sin(i)) + y);
    }
    glEnd();
}

void glLine(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

#endif // CUSTOMFUNCTIONS_H_INCLUDED
