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
	//fontSetColor(0, 0xff, 0);
	fontHeight(FONT_DEFAULT_HEIGHT);//FONT_DEFAULT_SIZE/40);
	//float lineHeight = fontGetHeight() * 1.5;
	//float y = windowSize.y - lineHeight * 2;

	fontPosition(0,0);
	fontWeight(fontGetWeightMin());
	//fontDraw("min:%f", fontGetWeightMin());

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
	//audioLength(1000);
	//audioDecay(.98);
	//audioPitchTarget(4);
	//audioSweep(1.1);
	//audioFreq(440*2);

	switch (key) {
	case 0x1b:
		exit(0); 
		break;
	case 'p': 
		audioFreq(220);
		audioSweep(1.05,440*2); 
		audioPlay(); 
		break;
		
	case 's': 
		audioStop(); 
		break;
	}
	/*if ((key >= '1') && (key <= '5')) {
		audioWaveform(key - '1');
		audioStop();
		audioPlay();
	}*/
	/*if ((key >= '0') && (key <= '4')) {
		
		audioStop();
		audioWaveform(key - '0');
		audioFreq(440);
		audioSweep(.99, 440 / 2);
		audioPlay();
	}*/
	if ((key >= '0') && (key <= '9')) {
		audioWaveform(AUDIO_WAVEFORM_PULSE_12_5);
		audioStop();
		int k = key - '0';
		audioWaveform(AUDIO_WAVEFORM_PULSE_12_5);
		audioFreq(440 *pow(2,(1+k/12.f)));
		//audioSweep(.99, 440 / 2);
		//audioDecay(.9f);
		audioPlay();
	}
	keys[key] = true;
}
void keyboardUp(unsigned char key, int x, int y) {
	//printf("keyboardUp:\'%c\'(%#x)\n", key, key);
	keys[key] = false;
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