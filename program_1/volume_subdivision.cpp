#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef float point[3];
int m;

point vertices[4] = { {0,100,-100}, {0,0,-100}, {100,-100,-100}, {-100,-100,-100} };

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glOrtho(-250, 250, -250, 250, -250, 250);
}

void draw_triangle(point p1, point p2, point p3) {
	glBegin(GL_POLYGON);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glEnd();
}

void draw_tetrahedron(point p1, point p2, point p3, point p4) {
	glColor3f(1, 0, 0);
	draw_triangle(p1, p2, p3);

	glColor3f(0, 1, 0);
	draw_triangle(p1, p3, p4);

	glColor3f(0, 0, 1);
	draw_triangle(p1, p2, p4);

	glColor3f(1, 1, 0);
	draw_triangle(p2, p3, p4);
}

void divide_tetrahedron(point p1, point p2, point p3, point p4, int m) {
	if (m > 0) {
		point mid[6];
		for (int i = 0; i < 3; i++) {
			mid[0][i] = (p1[i] + p2[i]) / 2;
			mid[1][i] = (p1[i] + p3[i]) / 2;
			mid[2][i] = (p1[i] + p4[i]) / 2;
			mid[3][i] = (p2[i] + p3[i]) / 2;
			mid[4][i] = (p2[i] + p4[i]) / 2;
			mid[5][i] = (p3[i] + p4[i]) / 2;
		}

		divide_tetrahedron(p1, mid[0], mid[1], mid[2], m - 1);
		divide_tetrahedron(p2, mid[0], mid[3], mid[4], m - 1);
		divide_tetrahedron(p3, mid[1], mid[3], mid[5], m - 1);
		divide_tetrahedron(p4, mid[2], mid[4], mid[5], m - 1);
	}
	else
		draw_tetrahedron(p1, p2, p3, p4);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	divide_tetrahedron(vertices[0], vertices[1], vertices[2], vertices[3], m);
	glFlush();
}

int main(int argc, char** argv) {
	printf("Enter the number of iterations\n");
	scanf_s("%d", &m);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tetrahedron");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	myInit();
	
	glutMainLoop();
}
