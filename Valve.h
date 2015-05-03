#ifndef VALVE_H_INCLUDED
#define VALVE_H_INCLUDED

class Valve {
private:
    Point midPoint;
    GLdouble radius;
    bool openB = false;
public:
    bool isOpen() {
        return openB;
    }

    void open() {
        openB = true;
    }

    void close() {
        openB = false;
    }

    void placement(GLdouble x, GLdouble y, GLdouble r) {
        midPoint = Point(x, y);
        radius = r;
    }

    void draw() {
        if (isOpen()) glColor3f(0.5, 0.0, 0.0);
        else glColor3f(0.2, 0.2, 0.2);
        glDisk(midPoint.x, midPoint.y, radius);
    }
};

#endif // VALVE_H_INCLUDED
