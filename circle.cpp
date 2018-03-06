#include <GL/freeglut.h>
#include <cmath>
#include "circle.h"

void Circle::draw()
{
    glColor3f(this->RGB[0], this->RGB[1], this->RGB[2]);
    glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 360; i++)
        {
            float rad = i*(M_PI/180.0);
            glVertex2f(cos(rad)*radius + this->cx, sin(rad)*radius + this->cy);
        }
    glEnd();
}

GLfloat Circle::getcx()
{
    return this->cx;
}

GLfloat Circle::getcy()
{
    return this->cy;
}

GLint Circle::getId()
{
    return this->id;
}

GLfloat Circle::getRadius()
{
    return this->radius;
}

string Circle::getFill()
{
    return this->fill;
}
