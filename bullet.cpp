#include <GL/freeglut.h>
#include "bullet.h"
#include <cmath>
#include <iostream>

using namespace std;

Bullet::Bullet(GLfloat bulletRadius, GLfloat posX, GLfloat posY, GLfloat bulletTheta, GLfloat gunPosX, GLfloat gunPosY, GLfloat velTiro)
{
    this->radius = bulletRadius;
    this->gX = posX;
    this->gY = posY;
    this->gTheta = bulletTheta;
    this->gunPosX = gunPosX;
    this->gunPosY = gunPosY;
    this->velTiro = velTiro;
}

void Bullet::drawBullet()
{
    glPushMatrix();
        glTranslatef(gX, gY, 0);
        glRotatef(gTheta, 0, 0, 1);
        glTranslatef(gunPosX, gunPosY, 0);
        drawCircle(.75, 0, 0);
    glPopMatrix();
}

void Bullet::drawCircle(GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 360; i++)
        {
            float rad = i*(M_PI/180.0);
            glVertex2f(cos(rad)*(this->radius), sin(rad)*(this->radius));
        }
    glEnd();
}

void Bullet::updateBullet()
{
    gX += velTiro*sin(gTheta*(M_PI/180.0));
    gY -= velTiro*cos(gTheta*(M_PI/180.0));
}

GLfloat Bullet::getgX()
{
    return (this->gX + this->gunPosX*sin(gTheta*(M_PI/180.0)));
}

GLfloat Bullet::getgY()
{
    return (this->gY + this->gunPosY*cos(gTheta*(M_PI/180.0)));
}

GLfloat Bullet::getRadius()
{
    return this->radius;
}
