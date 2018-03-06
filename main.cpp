#define _USE_MATH_DEFINES

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <list>
#include <cmath>
#include <ctime>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "arena.h"
#include "circle.h"
#include "player.h"
#include "bullet.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"

using namespace std;

Arena arena;
Player player;
int keyFlags[256];
int mouseFlags[2];
bool jumping = false;
float start;

void keyboardUp(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'W':
        case 'w':
            keyFlags['w'] = 0;
            break;

        case 'S':
        case 's':
            keyFlags['s'] = 0;
            break;

        case 'A':
        case 'a':
            keyFlags['a'] = 0;
            break;

        case 'D':
        case 'd':
            keyFlags['d'] = 0;
			break;

		case 'P':
		case 'p':
			keyFlags['p'] = 0;
			break;

        default:
            break;
    }
}

void keyPressed(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'W':
        case 'w':
            keyFlags['w'] = 1;
            break;

        case 'S':
        case 's':
            keyFlags['s'] = 1;
            break;

        case 'A':
        case 'a':
            keyFlags['a'] = 1;
            break;

        case 'D':
        case 'd':
            keyFlags['d'] = 1;
			break;
		
		case 'P':
		case 'p':
			keyFlags['p'] = 1;
			break;

        default:
            break;
    }
}

void mouseClick(GLint buttonPressed, GLint state, GLint x, GLint y)
{
	switch (buttonPressed)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				mouseFlags[0] = 1;
				player.shoot();
			}
			else if (state == GLUT_UP)
			{
				mouseFlags[0] = 0;
			}

			break;

		default:
			break;
	}
}

void mousePassiveMove(GLint x, GLint y)
{
	player.rotateGun(x, y);
}

void idle()
{
	arena.checkOnCircle(&player);

	if (keyFlags['w'] == 1)
    {
        player.moveY(-1.0);
    }
    if (keyFlags['s'] == 1)
    {
        player.moveY(1.0);
    }
    if (keyFlags['a'] == 1)
    {
        player.rotate(-1.0);
    }
    if (keyFlags['d'] == 1)
    {
        player.rotate(1.0);
	}
	if (keyFlags['p'] == 1)
	{
		if (!jumping)
		{
			jumping = true;
			player.setJumping(jumping);
			start = glutGet(GLUT_ELAPSED_TIME);
		}
	}

	// Jump
	// How much should the radius change per ms
	float deltaR = (player.getRadius()/20)*0.165;

	if (jumping)
	{	
		if ( (glutGet(GLUT_ELAPSED_TIME) - start) <= 1000 )
		{
			player.increasegr(deltaR);
		}
		else if ( (glutGet(GLUT_ELAPSED_TIME) - start) <= 2000 )
		{
			player.increasegr(-deltaR);
		}
		else
		{
			player.setgr(0);
			jumping = false;
			player.setJumping(jumping);

			arena.checkIfLandedOnCircle(&player);
		}
	}
	
	arena.checkCollision(&player);
	arena.checkBulletCollision(&player);
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	arena.drawArena();
	player.draw();
	glutSwapBuffers();
	glFlush();
}

void init()
{
	glClearColor(1, 1, 1, 1.0);

	glMatrixMode(GL_PROJECTION);

	GLfloat cx, cy;
	GLfloat radius;
	cx = arena.getcx("blue");
	cy = arena.getcy("blue");
	radius = arena.getRadius("blue");

	glOrtho(cx - radius,
			cx + radius,
			cy + radius,
			cy - radius,
			-1.0,
			1.0);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

float returnWindowSize()
{
	GLfloat radius, cx;
	cx = arena.getcx("blue");
	radius = arena.getRadius("blue");

	player.setwindowRatio(cx - radius);
	player.setWindowSize(radius*2);

	return radius*2;
}

/* Parsing do svg */
void loadArenaScenario(string path)
{
	TiXmlDocument doc(path.c_str());
	bool loaded = doc.LoadFile();
	if (loaded)
	{
		// Le o arquivo svg e cria as instancias dos circulos
		TiXmlElement* objectTree = doc.FirstChildElement("svg")->FirstChildElement("circle");
		for(TiXmlElement* e = objectTree; e != NULL; e = e->NextSiblingElement())
		{
			if (e->Attribute("fill") == string("green"))
			{
				player.set(atof(e->Attribute("cx")), atof(e->Attribute("cy")),
						   atof(e->Attribute("r")),
					   	   e->Attribute("fill"),
					   	   atoi(e->Attribute("id")));
			}
			else
			{
				Circle novo(atof(e->Attribute("cx")), atof(e->Attribute("cy")),
							atof(e->Attribute("r")),
							e->Attribute("fill"),
							atoi(e->Attribute("id")));

				arena.addToCircleList(novo);
			}
		}
	}
	else
	{
		printf("Could not find or load file\n");
		exit(0);
	}

	return;
}
/* */

/* Parsing do xml */
void parsing(const char* loc)
{
	TiXmlDocument doc(loc);
	bool loadOkay = doc.LoadFile();

	if (!loadOkay)
	{
        printf("Could not find or load file\n");
        exit(0);
  	}

	TiXmlHandle xmlHandler(&doc);
	TiXmlElement *aplicacao, *arquivoDaArena, *jogador;

	aplicacao = doc.FirstChildElement("aplicacao");
    arquivoDaArena = aplicacao->FirstChildElement("arquivoDaArena");
    
    // nome do arquivo
    const char* nome = arquivoDaArena->Attribute("nome");
    // extensao do arquivo
    const char* tipo = arquivoDaArena->Attribute("tipo");
    // caminho do arquivo
    const char* caminho = arquivoDaArena->Attribute("caminho");

	string n = nome;
	string c = caminho;
	string t = tipo;
	string path = c + n + "." + t;

	jogador = arquivoDaArena->NextSiblingElement("jogador");
	// Atributos do jogador
	float velTiro = atof(jogador->Attribute("velTiro"));
	float vel = atof(jogador->Attribute("vel"));

	player.set(velTiro, vel);
	
	loadArenaScenario(path);
}

int main(int argc, char** argv)
{
    /* Parsing do xml */
    if (argc != 2)
    {
        printf("Modelo: %s local_do_arquivo\n", argv[0]);
        return 1;
    }

	string s = argv[1];
	string filename = "config.xml";

	string path = s + filename;

	const char* localizacao = path.c_str();
	parsing(localizacao);
	/* */

	float windowSize = returnWindowSize();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowSize, windowSize);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("arena");
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mousePassiveMove);
    glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}
