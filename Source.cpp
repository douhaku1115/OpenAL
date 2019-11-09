#include <stdio.h>
#include <stdlib.h>
#include "glut.h"
#include "font.h"
#include "glm/glm.hpp"
#include <time.h>
#include "audio.h"
using namespace glm;
#define BALL_MAX 2
ivec2 windowSize = { 800, 600 };

bool keys[256];

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);//(GLenum mode);
	glLoadIdentity();
	gluOrtho2D(
		0,//GLdouble left,
		windowSize.x,//GLdouble right,
		windowSize.y,	//GLdouble bottom,
		0);	//GLdouble top);
	glMatrixMode(GL_MODELVIEW);//GLenum mode
	glLoadIdentity();

	static float angle;
	if (keys['d']) angle += 1;
	if (keys['a']) angle -= 1;

	glColor3ub(0xff, 0xff, 0xff);


	fontBegin();
	{
		fontHeight(FONT_DEFAULT_HEIGHT);//FONT_DEFAULT_SIZE/40);
		fontWeight(fontGetWeightMax());
		fontPosition(fontGetWeight() * 20, fontGetWeight() * 20);								  //float lineHeight = fontGetHeight() * 1.5;
		for (int i = 0; i < 128; i++)
			if (keys[i])
				fontDraw("%c\n", i);
	}
	fontEnd();

	glutSwapBuffers();

};

void idle(void) {
	audioUpdate();
	glutPostRedisplay();
}



void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}
void reshape(int width, int height) {
	//printf("rehape:width:%d height:%d\n",width,height);
	glViewport(0, 0, width, height);
	//GLint x, GLint y, GLsizei width, GLsizei height);

}
void keyboard(unsigned char key, int x, int y) {
	printf("keyboard:\'%c\'(%#x)\n", key, key);
	keys[key] = true;
	
	if ((key >= '0') && (key <= '3')) {
		int channel = key - '0';
		audioStop(channel);
		switch (channel) {

		case AUDIO_CHANNEL_PULSE0:
			audioGain(channel, AUDIO_DEFAULT_GAIN);
			audioFreq(channel, 440 * pow(2, (0 / 12.f)));
			break;
		case AUDIO_CHANNEL_PULSE1:
			audioGain(channel, AUDIO_DEFAULT_GAIN * .5);
			audioFreq(channel, 440 * pow(2, (0 / 12.f)));
			break;
		case AUDIO_CHANNEL_TRIANGLE:
			audioGain(channel, AUDIO_DEFAULT_GAIN);
			audioFreq(channel, 440 * pow(2, (3 / 12.f)));
			break;
		case AUDIO_CHANNEL_NOISE:
			audioGain(channel, AUDIO_DEFAULT_GAIN * .5);
			audioDecay(channel, .9f);
			break;
		}
		audioPlay(channel);
	}
	switch (key) {
	case 0x1b:
		exit(0);
		break;
	}
		
}
void keyboardUp(unsigned char key, int x, int y) {
	//printf("keyboardUp:\'%c\'(%#x)\n", key, key);
	keys[key] = false;
	if ((key >= '0') && (key <= '3')) {
		int channel = key - '0';
		audioStop(channel);
	}
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	if (audioInit() != 0)
		return 1;


	glutInit(&argc, argv);

	glutInitDisplayMode(GL_DOUBLE);
	glutInitWindowPosition(640, 0);
	glutInitWindowSize(windowSize.x, windowSize.y);
	glutCreateWindow("a");
	glutDisplayFunc(display);
	//glutTimerFunc(0, timer, 0);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);//void (GLUTCALLBACK *func)(int width, int height));
	glutKeyboardFunc(keyboard);//GLUTCALLBACK *func)(unsigned char key, int x, int y));
	glutKeyboardUpFunc(keyboardUp);//void (GLUTCALLBACK *func)(unsigned char key, int x, int y));
	//glutPassiveMotionFunc(passiveMotion); //void (GLUTCALLBACK * func)(int x, int y));
	//glutMotionFunc(motion); void (GLUTCALLBACK * func)(int x, int y));
	glutIgnoreKeyRepeat(GL_TRUE);//int ignore
	glutMainLoop();
}