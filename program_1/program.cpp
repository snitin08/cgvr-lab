#include<stdio.h>
#include<iostream>
#include<gl\glut.h>

using namespace std;

int flag = 0;
int x1, yc1, x2, y2;

void draw_pixel(int x, int y)
{
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void draw_line()
{
	int dx = x2 - x1;
	int dy = y2 - yc1;
	if (dx < 0)
		dx = -dx;
	if(dy < 0)
		dy = -dy;
	int incx = 1;
	if (x2 < x1)
		incx = -1;
	int incy = 1;
	if (y2 < yc1)
		incy = -1;
	int x = x1;
	int y = yc1;
	if (dx > dy)
	{
		draw_pixel(x, y);
		int e = 2 * dy - dx;
		int inc1 = 2 * (dy - dx);
		int inc2 = 2 * dy;
		for (int i = 0; i < dx; i++)
		{
			if (e > 0)
			{
				e += inc1;
				y += incy;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}
	}
	else
	{
		draw_pixel(x, y);
		int e = 2 * dx - dy;
		int inc1 = 2 * (dx - dy);
		int inc2 = 2 * dx;
		for (int i = 0; i < dy; i++)
		{
			if (e > 0)
			{
				e += inc1;
				x += incx;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}
void mymouse(int btn,int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (flag == 0)
		{
			printf("values of x1 and y1 is\n");
			x1 = x - 250;
			yc1 = 250 - y;
			flag++;
			cout << x1 << " " << yc1 << endl;
		}
		else
		{
			printf("values of x2 and y2 is \n");
			x2 = x - 250;
			y2 = 250 - y;
			flag = 0;
			cout << x2 << " " << y2 << endl;
			draw_line();
		}
	}
}

void myinit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 0);
	gluOrtho2D(-250, 250, -250, 250);
}

void mydisplay()
{

}
int flag1 = 0;
void mykeyboard(unsigned char key, int x, int y)
{
	if (key == 'Q' || key ==  'q')
	{
		if (flag1 == 0)
		{
			printf("values of x1 and y1 is\n");
			x1 = x - 250;
			yc1 = 250 - y;
			flag1++;
			cout << x1 << " " << yc1 << endl;
		}
		else
		{
			printf("values of x2 and y2 is \n");
			x2 = x - 250;
			y2 = 250 - y;
			flag1 = 0;
			cout << x2 << " " << y2 << endl;
			draw_line();
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("bresenham's line");
	myinit();
	glutMouseFunc(mymouse);
	glutKeyboardFunc(mykeyboard);
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
