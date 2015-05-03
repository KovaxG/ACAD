#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "SevenSegment.h"

class Controller : public  Object{
private:
    SevenSegment ss[3];
    int value;
    int lastDisplay = 'c';
public:
    void setValue(double temp) {
        value = (int) temp;
    }

    int getValue() {
        return value;
    }

    void sensePressure() {
        lastDisplay = 'p';
    }

    void placement(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
        startPoint = Point(x1, y1);
        endPoint = Point(x2, y2);
        ss[0].placement(x1, y1,((x2 - x1) / 3.0) + x1, y2);
        ss[1].placement(((x2 - x1) / 3.0) + x1, y1, ((x2 - x1) / 3.0 * 2.0) + x1, y2);
        ss[2].placement(((x2 - x1) / 3.0 * 2.0) + x1, y1, x2, y2);
    }

    void draw() {
        glBegin(GL_POLYGON);
            glColor3f(0.5, 0.5, 0.5);
            glVertex2f(getStartX(), getStartY());
            glVertex2f(getStartX(), getEndY());
            glVertex2f(getEndX(), getEndY());
            glVertex2f(getEndX(), getStartY());
        glEnd();

        ss[0].displayNumber(value / 10);
        ss[0].draw();
        ss[1].displayNumber(value % 10);
        ss[1].draw();
        ss[2].displayNumber(lastDisplay);
        ss[2].draw();
    }
};

#endif // CONTROLLER_H_INCLUDED
