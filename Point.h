#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class Point {
public:
    GLdouble x;
    GLdouble y;

    void setPoint(GLdouble iksz, GLdouble ipsz) {
        x = iksz;
        y = ipsz;
    }

    Point(GLdouble a, GLdouble b) {
        x = a;
        y = b;
    }
    Point() {
        x = 0.0;
        y = 0.0;
    }
};

#endif // POINT_H_INCLUDED
