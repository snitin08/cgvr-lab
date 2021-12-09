#include<stdio.h>
#include<gl/glut.h>

static GLfloat spin = 0;
int t, wid1, wid2;

void display1()
{
	glutSetWindow(t);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1);
	glPushMatrix();
	glLoadIdentity();
	
	if (t == wid2)
		glRotatef(spin, 0, 0, 1);

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-0.25, -0.25);			//Use different coordinates to change the width and height
	glColor3f(0, 1, 0);
	glVertex2f(0.25, -0.25);
	glColor3f(0, 0, 1);
	glVertex2f(0.25, 0.25);
	glColor3f(1, 1, 0);
	glVertex2f(-0.25, 0.25);
	glEnd();
	glPopMatrix();

	if (t == wid1) {
		glFlush();
		t = wid2;
	}
	else {
		glutSwapBuffers();
		t = wid1;
	}
}

void spinDisplay() {
	spin += 0.02;
	glutPostRedisplay();
}

void mouse1(int button, int state, int x, int y) {

	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:break;
	}
}



void myinit()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1);
	glColor3f(1, 0, 0);
	glOrtho(-1, 1, -1, 1, -1, 1);
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitWindowSize(500, 500);
	wid1 = glutCreateWindow("Single");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutDisplayFunc(display1);
	glutMouseFunc(mouse1);


	glutInitWindowSize(500, 500);
	wid2 = glutCreateWindow("Double");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	t = wid1;


	glutDisplayFunc(display1);
	glutMouseFunc(mouse1);


	myinit();
	glutMainLoop();
}
