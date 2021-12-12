#include<stdio.h>
#include<GL\glut.h>

typedef float point[3];
int n;
point tetrahedron[4] = { {0,250,-250},{0,0,250},{250,-250,-250},{-250,-250,-250} };

void draw_triangle(point a, point b, point c)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void draw_tetrahedron(point a, point b, point c, point d)
{
	glColor3f(1, 1, 0);
	draw_triangle(a,b,c);
	glColor3f(0, 1, 0);
	draw_triangle(a,c,d);
	glColor3f(1, 0, 0);
	draw_triangle(a,b,d);
	glColor3f(0, 0, 1);
	draw_triangle(b,c,d);
}

void divide_tetrahedron(point p1 ,point p2, point p3,point p4, int n)
{
	point mid[6];
	if (n > 0)
	{
		for (int j = 0; j < 3; j++)
		{
			mid[0][j] = (p1[j] + p2[j]) / 2;
		}
		for (int j = 0; j < 3; j++)
		{
			mid[1][j] = (p1[j] + p3[j]) / 2;
		}
		for (int j = 0; j < 3; j++)
		{
			mid[2][j] = (p1[j] + p4[j]) / 2;
		}
		for (int j = 0; j < 3; j++)
		{
			mid[3][j] = (p2[j] + p3[j]) / 2;
		}
		for (int j = 0; j < 3; j++)
		{
			mid[4][j] = (p3[j] + p4[j]) / 2;
		}
		for (int j = 0; j < 3; j++)
		{
			mid[5][j] = (p2[j] + p4[j]) / 2;
		}
		divide_tetrahedron(p1, mid[0], mid[1], mid[2], n - 1);
		divide_tetrahedron(p2, mid[0], mid[3], mid[5], n - 1);
		divide_tetrahedron(p3, mid[1], mid[3], mid[4], n - 1);
		divide_tetrahedron(p4, mid[2], mid[4], mid[5], n - 1);
	}
	else
	{
		draw_tetrahedron(p1, p2, p3, p4);
	}
}

void myinit()
{
	glClearColor(0, 0, 0, 0);
	glOrtho(-300, 300, -300, 300,-300,300);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		divide_tetrahedron(tetrahedron[0], tetrahedron[1],tetrahedron[2],tetrahedron[3],n);
	glEnd();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h >= w)
	{
		glOrtho(-300, 300, -300 * (GLdouble)h / (GLdouble)w, 300 * (GLdouble)h / (GLdouble)w, -300, 300);
	}
	else
	{
		glOrtho(-300 * (GLdouble)w / (GLdouble)h, 300 * (GLdouble)w / (GLdouble)h, -300, 300, -300, 300);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

void main(int argc,char ** argv)
{
	glutInit(&argc, argv);
	printf("enter the number of iterations ");
	scanf_s("%d", &n);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("sierpenski");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	myinit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
