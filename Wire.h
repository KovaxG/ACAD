#ifndef WIRE_H_INCLUDED
#define WIRE_H_INCLUDED

class Wire {
protected:
    Point startPoint;
    Point endPoint;
public:
    void initialize(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
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
        // TODO Line Stipplevel lehet konnyebb lenne megcsinalni amit akarok
        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 0.5, 0.0);
        glVertex2f(getStartX(), getStartY());
        glVertex2f(getStartX(), getEndY());
        glVertex2f(getEndX(), getEndY());
        glEnd();
    }
};

#endif // WIRE_H_INCLUDED
