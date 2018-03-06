#include <GL/freeglut.h>
#include <list>
#include <cmath>
#include "arena.h"

using namespace std;

void Arena::addToCircleList(Circle circle)
{
    circleList.push_back(circle);
    
    return;
}

void Arena::drawArena()
{
    for (Circle &it : circleList)
    {
        it.draw();
    }
}

void Arena::checkOnCircle(Player* player)
{
    if (onCircle != NULL)
	{
		float dx = player->getgX() - onCircle->getcx();
		float dy = player->getgY() - onCircle->getcy();

		float d = sqrt(dx*dx + dy*dy);

		if (d >= player->getRadius() + onCircle->getRadius())
		{
            onCircle = NULL;
            player->setOnCircle(false);
        }
        else
        {
            player->setOnCircle(true);
        }
    }
}

void Arena::checkIfLandedOnCircle(Player* player)
{
    GLfloat leastDistance = 1000;

    for (Circle &it : circleList)
    {
        if (it.getFill() != "green")
        {
            float distanceX = player->getgX() - it.getcx();
            float distanceY = player->getgY() - it.getcy();

            float distance = sqrt(distanceX*distanceX + distanceY*distanceY);

            if (distance < leastDistance)
            {
                leastDistance = distance;
            }

            if ( ( distance < ( player->getRadius() + it.getRadius() ) ) && distance == leastDistance )
            {
                onCircle = &it;
            }
        }
    }
}

void Arena::checkBulletCollision(Player* player)
{
    GLint size = player->getBulletListSize();

    for (GLint i = 0; i < size; i++)
    {
        GLfloat bulletgX = player->getBulletgX(i);
        GLfloat bulletgY = player->getBulletgY(i);

        GLfloat bulletRadius = player->getBulletRadius(i);

        for (Circle &it : circleList)
        {
            GLfloat circlecx = it.getcx();
            GLfloat circlecy = it.getcy();
        
            GLfloat distanceX;
            GLfloat distanceY;
            GLfloat distance;
    
            distanceX = bulletgX - circlecx;
            distanceY = bulletgY - circlecy;
    
            distance = sqrt(distanceX*distanceX + distanceY*distanceY);
    
            bool touching = distance < (bulletRadius + it.getRadius());
    
            if ( touching && ( it.getFill() != "green" && it.getFill() != "blue" && it.getFill() != "red") )
            {
                player->destroyBullet(i);
                return;
            }
            else if (it.getFill() == "blue")
            {
                // Distance from bullet to circle border
                distanceX = bulletgX - circlecx;
                distanceY = bulletgY - circlecy;
    
                distance = sqrt(distanceX*distanceX + distanceY*distanceY);
                distance += bulletRadius;
    
                if (distance > it.getRadius())
                {
                    player->destroyBullet(i);
                    return;
                }
            }
        }
    }
}

void Arena::checkCollision(Player *player)
{   
    for (Circle &it : circleList)
    {
        GLfloat playergX = player->getgX();
        GLfloat playergY = player->getgY();
    
        GLfloat circlecx = it.getcx();
        GLfloat circlecy = it.getcy();
    
        GLfloat distanceX;
        GLfloat distanceY;
        GLfloat distance;

        distanceX = playergX - circlecx;
        distanceY = playergY - circlecy;

        distance = sqrt(distanceX*distanceX + distanceY*distanceY);

        bool touching = distance < (player->getRadius() + it.getRadius());

        if ( touching && ( it.getFill() == "white" || it.getFill() == "red" ) )
        {
            player->handleCollision(touching);
            return;
        }
        else if ( touching && !player->isJumping() && it.getFill() == "black" )
        {
            if ( onCircle != NULL && it.getId() != onCircle->getId() )
			{
                //player->handleCollision(touching);
                player->handleCollision(touching);
                return;
			}
			else if (onCircle == NULL)
			{
                player->handleCollision(touching);
                return;
			}
        }
        else if (it.getFill() == "blue")
        {
			// Distance from player to circle border
			distanceX = playergX - circlecx;
			distanceY = playergY - circlecy;

			distance = sqrt(distanceX*distanceX + distanceY*distanceY);
			distance += player->getRadius();

			if (distance > it.getRadius())
			{
                player->handleCollision(touching);
                return;
			}
        }
        else
        {
            player->handleCollision(false);
        }
    }
}

GLfloat Arena::getRadius(string fill)
{
    for (Circle &it : circleList)
    {
        if (it.getFill() == fill)
        {
            return it.getRadius();
        }
    }
}

GLint Arena::getcx(string fill)
{
    for (Circle &it : circleList)
    {
        if (it.getFill() == fill)
        {
            return it.getcx();
        }
    }
}

GLint Arena::getcy(string fill)
{
    for (Circle &it : circleList)
    {
        if (it.getFill() == fill)
        {
            return it.getcy();
        }
    }
}
