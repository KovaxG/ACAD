#ifndef BOILER_H_INCLUDED
#define BOILER_H_INCLUDED

class Boiler : public Object {
private:
    double pressure = 20;
public:
    void setPressure(double p) {
        pressure = p;
    }

    double getPressure() {
        return pressure;
    }

    void releasePressure(double p) {
        pressure -= p;
    }

    void update() {
        pressure += 0.007;
    }

    void draw() {
        glBegin(GL_POLYGON);
            glColor3f(0.5, 0.0, 0.5);
            glVertex2f(getStartX(), getStartY());
            glVertex2f(getStartX(), getEndY());
            glVertex2f(getEndX(), getEndY());
            glVertex2f(getEndX(), getStartY());
        glEnd();
    }
};

#endif // BOILER_H_INCLUDED
