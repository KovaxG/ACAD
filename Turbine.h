#ifndef TURBINE_H_INCLUDED
#define TURBINE_H_INCLUDED

class Turbine {
private:
    Point midPoint;
    GLdouble radius;
    GLdouble spin;
public:
    void setMidPoint(Point mp){
        midPoint = mp;
    }

    void setRadius(GLdouble r) {
        radius = r;
    }

    void initialize(GLdouble x, GLdouble y, GLdouble r) {
        setMidPoint(Point(x, y));
        setRadius(r);
        spin = 0.0;
    }

    void spinIt() {
        spin += 5.0;
        if (spin >= 360.0) spin -= 360.0;
    }

    void draw() {
        glPushMatrix();
        glTranslatef(midPoint.x, midPoint.y, 0.0);
        glRotatef(spin, 0.0, 0.0, 1.0);
        glCircle(0, 0, radius);
        glEllipse(0, 0, radius, radius / 10.0);
        glEllipse(0, 0, radius / 10.0, radius);
        glCircle(0, 0, radius / 10.0);
        glPopMatrix();
    }
};

#endif // TURBINE_H_INCLUDED
