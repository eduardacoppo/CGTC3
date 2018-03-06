#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>

#include <GL/freeglut.h>
#include <string>

using namespace std;

class Circle
{
    protected:
        GLfloat cx;
        GLfloat cy;
        GLfloat radius;
        string fill;
        GLint id;
        GLfloat RGB[3];

    public:
        Circle() { }
        Circle(GLfloat cx, GLfloat cy, GLfloat radius, string fill, GLint id)
        {
            this->cx = cx;
            this->cy = cy;
            this->radius = radius;
            this->fill = fill;
            this->id = id;

            if (this->fill == "blue")
            {
                this->RGB[0] = 0; this->RGB[1] = .15; this->RGB[2] = 1;
            }
            else if (this->fill == "white")
            {
                this->RGB[0] = 1; this->RGB[1] = 1; this->RGB[2] = 1;
            }
            else if (this->fill == "black")
            {
                this->RGB[0] = 0; this->RGB[1] = 0; this->RGB[2] = 0;
            }
            else if (this->fill == "green")
            {
                this->RGB[0] = 0; this->RGB[1] = .5; this->RGB[2] = 0;
            }
            else if (this->fill == "red")
            {
                this->RGB[0] = 1; this->RGB[1] = 0; this->RGB[2] = 0;
            }
        }

        GLfloat getcx();
        GLfloat getcy();
        GLfloat getRadius();
        string getFill();
        GLint getId();

        void draw();
};

#endif
