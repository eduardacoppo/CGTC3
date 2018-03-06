#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <GL/freeglut.h>

using namespace std;

class Bullet
{
    private:
        GLfloat gX;
        GLfloat gY;
        GLfloat gTheta;
        GLfloat radius;
        GLfloat gunPosX;
        GLfloat gunPosY;
        GLfloat velTiro;

    public:
        Bullet(GLfloat bulletRadius, GLfloat posX, GLfloat posY, GLfloat bulletTheta, GLfloat gunPosX, GLfloat gunPosY, GLfloat velTiro);
        void drawBullet();
        void drawCircle(GLfloat R, GLfloat G, GLfloat B);
        void updateBullet();

        GLfloat getgX();
        GLfloat getgY();
        GLfloat getRadius();

};

#endif
