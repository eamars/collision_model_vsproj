/*
I love this keyboard. This makes me more likely to write some powerful code
Hopefully

Ran Bao
*/


#include <iostream>
#include <GL/freeglut.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <string>
#include "ball.h"
#include "GLColor.h"
#include "TextBox.h"
#include "FPS.h"

#define ENABLE_COLLISION 1
#define ENABLE_RELATIVE_GRAVITY 1
#define ENABLE_GRAVITY 0

#define NUM_OF_BALLS 5
#define X_BOUNDARY 100
#define Y_BOUNDARY 100

#define RANDOM(X) rand() % (X * 100) / 100.0
#define RANDOM_N(X) (rand() % (X * 100) - X * 100 / 2) / 100.0

static Ball balllist[NUM_OF_BALLS];
NewTextBox fps = NewTextBox(0, 0.98 * Y_BOUNDARY, GLColor::GL_WHITE_COLOR, GLUT_BITMAP_HELVETICA_12);

void init_ball_list(void){
	/*
	for (int i = 0; i < NUM_OF_BALLS; i++) {
		balllist[i] = Ball(RANDOM(X_BOUNDARY), RANDOM(Y_BOUNDARY), 0, 0, 0.5, 50);

		if (ENABLE_GRAVITY) {
		balllist[i].ay(10);
		}
	}
	*/
	
	
	balllist[0] = Ball(50, 50, 0, 0, 3, 1000, false);
	balllist[1] = Ball(50, 20, 10, 0, 0.5, 1, false);
	balllist[2] = Ball(50, 10, 10, 0, 1, 20, false);
	balllist[3] = Ball(10, 50, 0, -10, 0.5, 5, false);
	balllist[4] = Ball(30, 60, -12, -12, 1, 10, false);
	

	/*
	balllist[0] = Ball(30, 50, 0, -15, 1, 50);
	balllist[1] = Ball(70, 50, 0, 15, 1, 50);
	balllist[2] = Ball(50, 50, 0, 0, 2, 500);
	*/

}

void simulation(void){
	for (int i = 0; i < NUM_OF_BALLS; i++) {
		balllist[i].collide_with_boundary(0, X_BOUNDARY, 0, Y_BOUNDARY);
		for (int j = i + 1; j < NUM_OF_BALLS; j++) {
			if (ENABLE_COLLISION) {
				balllist[i].collide_with_ball(balllist[j]);
			}

		}
		if (ENABLE_RELATIVE_GRAVITY) {
			balllist[i].gravity_with_ball(balllist, i, NUM_OF_BALLS);
		}
		balllist[i].advance();
	}
}

void draw(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);


	// draw balls
	for (int i = 0; i < NUM_OF_BALLS; i++) {
		balllist[i].draw();
	}

	fps.update("FPS = " + std::to_string(get_fps_2()));
	fps.draw();
	glFlush();

	glutSwapBuffers();
}

void idle(void){
	simulation();
	draw();
}

void init(void)
{
	/* clearing background */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, X_BOUNDARY, 0, Y_BOUNDARY, -1, 1);

	glLineWidth(1.0f);//default line width =1

	init_ball_list();
}


int main(int argc, char **argv)
{
	srand((unsigned int)time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Bouncing Ball");
	init();
	glutDisplayFunc(simulation);
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}