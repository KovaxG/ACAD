#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED

class Pipe : public Wire {
private:
    bool flowing = true;
public:
    void isFlowing(bool b) {
        flowing = b;
    }

    void draw() {
        glLineWidth(4);
        glBegin(GL_LINE_STRIP);
            if (flowing == true) glColor3f(0.5, 0.0, 0.0);
            else glColor3f(0.2, 0.2, 0.2);
            glVertex2f(getStartX(), getStartY());
            glVertex2f(getStartX(), getEndY());
            glVertex2f(getEndX(), getEndY());
        glEnd();
        glLineWidth(1);
    }
};

#endif // PIPE_H_INCLUDED
