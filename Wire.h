#ifndef WIRE_H_INCLUDED
#define WIRE_H_INCLUDED

class Wire : public Object{
public:
    void draw() {
        // TODO Line Stipplevel lehet konnyebb lenne megcsinalni amit akarok
        glBegin(GL_LINE_STRIP);
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(getStartX(), getStartY());
        glVertex2f(getStartX(), getEndY());
        glVertex2f(getEndX(), getEndY());
        glEnd();
    }
};

#endif // WIRE_H_INCLUDED
