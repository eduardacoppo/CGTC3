#ifndef ARENA_H
#define ARENA_H

#include <iostream>
#include <GL/freeglut.h>
#include <string>
#include <list>
#include "player.h"
#include "bullet.h"

using namespace std;

class Circle;
class Arena
{
    private:
        list<Circle> circleList;
        Circle *onCircle;

    public:
        Arena() { onCircle = NULL; }
        void addToCircleList(Circle circle);
        void drawArena();
        void checkCollision(Player *player);
        void checkBulletCollision(Player *player);
        GLfloat getRadius(string fill);
        GLint getcx(string fill);
        GLint getcy(string fill);
        void checkOnCircle(Player* player);
        void checkIfLandedOnCircle(Player* player);
};

#endif
