#ifndef WIND_H_INCLUDED
#define WIND_H_INCLUDED

class Wind : public Object {
private:
    double temperature = 50.0;
public:
    double getTemp() {
        return temperature;
    }

    void update() {
        temperature -= 0.01;
    }

    void heat(double t) {
        temperature += t;
    }

    void draw() {
        glBegin(GL_POLYGON);
            glColor3f BLUE;
            glVertex2f(getStartX(), getStartY());
            glVertex2f(getStartX(), getEndY());
            glVertex2f(getEndX(), getEndY());
            glVertex2f(getEndX(), getStartY());
        glEnd();
    }
};

#endif // WIND_H_INCLUDED
