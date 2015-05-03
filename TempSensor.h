#ifndef TEMPSENSOR_H_INCLUDED
#define TEMPSENSOR_H_INCLUDED

class TempSensor : public Wire{
private:
    double temperature;
public:
    void senseTemperature(double t) {
        temperature = t;
    }

    double transmitTemperature() {
        return temperature;
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

#endif // TEMPSENSOR_H_INCLUDED
