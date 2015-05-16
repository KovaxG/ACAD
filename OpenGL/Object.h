#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

class Object {
protected:
    Point startPoint;
    Point endPoint;
public:
    void placement(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
        startPoint = Point(x1, y1);
        endPoint = Point(x2, y2);
    }

    GLdouble getStartX() {
        return startPoint.x;
    }

    GLdouble getStartY() {
        return startPoint.y;
    }

    GLdouble getEndX() {
        return endPoint.x;
    }

    GLdouble getEndY() {
        return endPoint.y;
    }

    void draw() {
        glBegin(GL_POLYGON);
            glColor3f(0.5, 0.5, 0.5);
            glVertex2f(getStartX(), getStartY());
            glVertex2f(getStartX(), getEndY());
            glVertex2f(getEndX(), getEndY());
            glVertex2f(getEndX(), getStartY());
        glEnd();
    }
};

#endif // OBJECT_H_INCLUDED
