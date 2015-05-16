#ifndef SEVENSEGMENT_H_INCLUDED
#define SEVENSEGMENT_H_INCLUDED

class SevenSegment : public Object {
private:
    bool light[7];
    enum Segments{a, b, c, d, e, f, g};
public:
    void placement(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
        startPoint = Point(x1, y1);
        endPoint = Point(x2, y2);

        // No lights to be displayed at beginning
        for (int i = 0; i < 7; i++) {
            light[i] = false;
        }
    }

    void displayNumber(int number) {
        for (int i = 0; i < 7; i++) {
            light[i] = false;
        }

        switch(number){
        case 0:
            light[a] = true;
            light[b] = true;
            light[c] = true;
            light[d] = true;
            light[e] = true;
            light[f] = true;
            break;
        case 1:
            light[b] = true;
            light[c] = true;
            break;
        case 2:
            light[a] = true;
            light[b] = true;
            light[g] = true;
            light[e] = true;
            light[d] = true;
            break;
        case 3:
            light[a] = true;
            light[b] = true;
            light[g] = true;
            light[c] = true;
            light[d] = true;
            break;
        case 4:
            light[f] = true;
            light[g] = true;
            light[b] = true;
            light[c] = true;
            break;
        case 5:
            light[a] = true;
            light[f] = true;
            light[g] = true;
            light[c] = true;
            light[d] = true;
            break;
        case 6:
            light[a] = true;
            light[f] = true;
            light[e] = true;
            light[d] = true;
            light[c] = true;
            light[g] = true;
            break;
        case 7:
            light[a] = true;
            light[b] = true;
            light[c] = true;
            break;
        case 8:
            for (int i = 0; i < 7; i++) light[i] = true;
            break;
        case 9:
            light[f] = true;
            light[a] = true;
            light[b] = true;
            light[g] = true;
            light[c] = true;
            light[d] = true;
            break;
        case 'c':
            light[g] = true;
            light[e] = true;
            light[d] = true;
            break;
        case 'p':
            light[a] = true;
            light[b] = true;
            light[g] = true;
            light[f] = true;
            light[e] = true;
            break;
        default:
            break;
        }
    }

    void draw() {
        glBegin(GL_POLYGON);
            glColor3f WHITE;
            glVertex2f(getStartX(), getStartY());
            glVertex2f(getStartX(), getEndY());
            glVertex2f(getEndX(), getEndY());
            glVertex2f(getEndX(), getStartY());
        glEnd();

        glLineWidth(4);
        glBegin(GL_LINE_LOOP);
            glColor3f(0.1, 0.1, 0.1);
            glVertex2f(getStartX(), getStartY());
            glVertex2f(getStartX(), getEndY());
            glVertex2f(getEndX(), getEndY());
            glVertex2f(getEndX(), getStartY());
        glEnd();

        GLfloat x1 = getStartX() + (getEndX() - getStartX()) / 10.0; // West with padding
        GLfloat y1 = getEndY() - (getEndY() - getStartY()) / 10.0; // North with padding
        GLfloat x2 = getEndX() - (getEndX() - getStartX()) / 10.0; // East with padding
        GLfloat y2 = getStartY() + (getEndY() - getStartY()) / 10.0; // South with padding

        glBegin(GL_LINES);
            // a
            if (light[0]) glColor3f RED;
            else glColor3f WHITE;
            glVertex2f(x1 , y1);
            glVertex2f(x2 , y1);

            // b
            if (light[1]) glColor3f RED;
            else glColor3f WHITE;
            glVertex2f(x2 , y1);
            glVertex2f(x2 , mean(y2, y1));

            // c
            if (light[2]) glColor3f RED;
            else glColor3f WHITE;
            glVertex2f(x2 , mean(y2, y1));
            glVertex2f(x2 , y2);

            // d
            if (light[3]) glColor3f RED;
            else glColor3f WHITE;
            glVertex2f(x1, y2);
            glVertex2f(x2, y2);

            // e
            if (light[4]) glColor3f RED;
            else glColor3f WHITE;
            glVertex2f(x1, y2);
            glVertex2f(x1, mean(y1, y2));

            // f
            if (light[5]) glColor3f RED;
            else glColor3f WHITE;
            glVertex2f(x1, mean(y1, y2));
            glVertex2f(x1, y1);

            // g
            if (light[6]) glColor3f RED;
            else glColor3f WHITE;
            glVertex2f(x1, mean(y1, y2));
            glVertex2f(x2, mean(y1, y2));
        glEnd();

        glLineWidth(1);
    }
};

#endif // SEVENSEGMENT_H_INCLUDED
