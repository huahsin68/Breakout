#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "GameLevel.h"



using namespace std;


GLuint compile();
void idle();
void initializeOpenGL(int, char**);
GLuint initializeShader(string, string);
void loadShaderFromFile(const GLchar*);
void loadFragmentFromFile(const GLchar*);
void processKey(unsigned char, int, int);
void processSpecialKey(int, int, int);
void processSpecialKeyUp(int, int, int);
void renderScene();
void timer(int);

unsigned vertexShader, fragmentShader;
string vertexSrc, fragmentSrc;
int timeFrame = 0;
int desiredFPS = 1000;
int fps = 1000/desiredFPS;


GameLevel *gameLevel = nullptr;


int main(int argc, char **argv)
{
	initializeOpenGL(argc, argv);

	gameLevel = new GameLevel();
	gameLevel->setAnimationShader(initializeShader(RES_PATH + "animSprite.vert", RES_PATH + "animSprite.frag"));
	gameLevel->setMultiInstanceShader(initializeShader(RES_PATH + "multiSprite.vert", RES_PATH + "multiSprite.frag"));
	gameLevel->setSingleInstanceShader(initializeShader(RES_PATH + "singleSprite.vert", RES_PATH + "singleSprite.frag"));
	gameLevel->launchGame();

	glutMainLoop();

	return 0;
}

GLuint compile()
{
	GLuint program;
	const GLchar* vertexCode = vertexSrc.c_str();
	const GLchar* fragmentCode = fragmentSrc.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, 0);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "vertex shader compilation error: " << infoLog << std::endl;

		return 0;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "fragment shader compilation error: " << infoLog << std::endl;

		return 0;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "shader program compilation error: " << infoLog << std::endl;

		return 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	return program;
}

void idle()
{
}

void initializeOpenGL(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("OpenGL First Window");

	glewInit();
	/*if (glewIsSupported("GL_VERSION_4_6"))
		std::cout << "GLEW version is 4.6" << std::endl;

	cout << "GL version: " << glGetString(GL_VERSION) << endl;
	cout << "Supported GLEW version: " << glewGetString(GLEW_VERSION) << endl;*/

	glutTimerFunc(0, timer, 0);
	glutDisplayFunc(renderScene);
	glutSpecialUpFunc(processSpecialKeyUp);
	glutSpecialFunc(processSpecialKey);
	glutKeyboardFunc(processKey);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutIdleFunc(idle);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

GLuint initializeShader(string vertex, string fragment)
{
	loadShaderFromFile(vertex.c_str());
	loadFragmentFromFile(fragment.c_str());
	return compile();
}

void loadFragmentFromFile(const GLchar* fragmentPath)
{
	ifstream fragmentFile;
	stringstream fragmentStream;

	fragmentFile.exceptions(ifstream::badbit);

	try {
		fragmentFile.open(fragmentPath);
		fragmentStream << fragmentFile.rdbuf();

		fragmentFile.close();
	}
	catch (ifstream::failure e) {
		cout << "Unable to read fragment file." << endl;
	}

	fragmentSrc = fragmentStream.str();
}

void loadShaderFromFile(const GLchar* vertexPath)
{
	ifstream vertexFile;
	stringstream vertexStream;

	vertexFile.exceptions(ifstream::badbit);

	try {
		vertexFile.open(vertexPath);
		vertexStream << vertexFile.rdbuf();

		vertexFile.close();
	}
	catch (ifstream::failure e) {
		cout << "Unable to read vertex file." << endl;
	}

	vertexSrc = vertexStream.str();
}

void processKey(unsigned char key, int x, int y)
{
	switch( key ) {
	case 'x':
		gameLevel->invokeKey(6, false);
		break;

	case ' ':
		gameLevel->invokeKey(7, false);
		break;

	case '\r':
		gameLevel->invokeKey(8, false);
		break;
	}
}

void processSpecialKey(int key, int x, int y)
{
	switch( key ) {
	case GLUT_KEY_LEFT:
		gameLevel->invokeKey(1, false);
		break;

	case GLUT_KEY_RIGHT:
		gameLevel->invokeKey(2, false);
		break;

	case GLUT_KEY_UP:
		gameLevel->invokeKey(3, false);
		break;

	case GLUT_KEY_DOWN:
		gameLevel->invokeKey(4, false);
		break;

	case GLUT_KEY_PAGE_DOWN:
		break;

	case GLUT_KEY_PAGE_UP:
		break;
	}
}

void processSpecialKeyUp(int key, int x, int y)
{
	switch( key ) {
	case GLUT_KEY_LEFT:
		gameLevel->invokeKey(1, true);
		break;

	case GLUT_KEY_RIGHT:
		gameLevel->invokeKey(2, true);
		break;

	case GLUT_KEY_UP:
		gameLevel->invokeKey(3, true);
		break;

	case GLUT_KEY_DOWN:
		gameLevel->invokeKey(4, true);
		break;
	}
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.0f, 0.2f, 0.2f, 0.0f);
//	glClearColor(255.f, 255.f, 255.f, 0.0f);

	gameLevel->render();

	glutSwapBuffers();
}

void timer(int value)
{
	// timer is call every 1 sec
	glutTimerFunc(1000, timer, ++value);
}
