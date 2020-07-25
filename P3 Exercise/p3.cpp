#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Pratical Exercise 3"

int qNo = 1;
double xfirst = 0;
double yfirst = 0;
double x2 = 0;
double y2 = 0;
double distance = 0.1;
const double pi = 3.141591;
int night = 0;

//windmail

double angle = 0;
double speed = -0.02;
double leafcolorB = 0;

//moon
double moonR = 0.6;
double moonG = 1;
double moonB = 1;
//sun
double sunR = 1;

//clound
double move = 0;
double cloundRGB = 1;

//sea
double seaColorG = 0.745;
double seaColorB = 1;

//Hint
double hideHintX = 0;
double hideHintY = 0;
double showHintX = -1;
double showHintY = -1;
double textRGB = 0;

//
double r = 0.6;
double g = 1;
double b = 1;


#define MAX_CHAR        128

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;

		lists = glGenLists(MAX_CHAR);

		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_LEFT)
		{
			if (qNo == 1)
			{
				xfirst += distance;
				x2 -= distance;
			}
		}
		else if (wParam == VK_RIGHT)
		{
			if (qNo == 1)
			{
				xfirst -= distance;
				x2 += distance;
			}
		}
		else if (wParam == VK_UP)
		{
			if (qNo == 1)
			{
				yfirst -= distance;
				y2 += distance;
			}
		}
		else if (wParam == VK_DOWN)
		{
			if (qNo == 1)
			{
				yfirst += distance;
				y2 -= distance;
			}
		}
		else if (wParam == VK_SPACE)
		{
			if (qNo == 1)
			{
				xfirst = 0;
				x2 = 0;
				yfirst = 0;
				y2 = 0;
			}
			else if (qNo == 2)
			{
				speed = 0;
			}
		}
		else if (wParam == '2')
		{
			qNo = 2;
		}
		else if (wParam == '1')
		{
			qNo = 1;
		}
		else if (wParam == 'Q')
		{
			//anti clock
			if (qNo == 2)
			{
				if (speed < 0)
					speed = speed * -1;
			}
		}
		else if (wParam == 'E')
		{
			if (qNo == 2)
			{
				if (speed > 0)
					speed = speed * -1;
			}
		}

		else if (wParam == 'W')
		{
			if (qNo == 2)
			{
				if (speed <= 0)
					speed = speed - 0.01;
				else 
					speed = speed + 0.01;
			}
		}
		else if (wParam == 'S')
		{
			if (qNo == 2)
			{
				if (speed < 0)
				{
					speed = speed + 0.01;
					if (speed >= 0)
						speed = 0;

				}

				else if (speed > 0)
				{
					speed = speed - 0.01;
					if (speed <= 0)
						speed = 0;
				}
			}
		}
		else if (wParam == 'H')
		{
			if (qNo == 2 && hideHintX==0)
			{
				hideHintX = -1;
				hideHintY = -1;
				showHintX = 0;
				showHintY = 0;
			}
			else
			{
				hideHintX = 0;
				hideHintY = 0;
				showHintX = -1;
				showHintY = -1;
			}

		}
		else if (wParam == 'N')
		{
			if (qNo == 2)
			{
				if (night == 0)
				{
					r = 0;
					b = 0;
					g = 0;
					leafcolorB = 1;
					sunR = 0;
					moonR = 1;
					moonG = 1;
					moonB = 0;
					cloundRGB = 0.2;
					seaColorG = 0;
					seaColorB = 0.4;
					night = 1;
					textRGB = 1;
				}
				else if(night==1)
				{
					r = 0.6;
					g = 1;
					b = 1;
					leafcolorB = 0;
					sunR = 1;
					moonR = 0.6;
					moonG = 1;
					moonB = 1;
					cloundRGB = 1;
					seaColorG = 0.745;
					seaColorB = 1;
					night = 0;
					textRGB = 0;
				}

			}
		}
		break;

	default:
		break;
	}
	 
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------


void windmill()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, 1);

	//moon
	glBegin(GL_POLYGON);
	glColor3f(moonR, moonG, moonB);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(-0.82 + 0.2 * cos(2 * pi / 360 * i), 0.80+ 0.2 * sin(2 * pi / 360 * i));
	}
	glEnd();


	//sun
	glBegin(GL_POLYGON);
	glColor3f(sunR, 0, 0);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(1 + 0.28 * cos(2 * pi / 360 * i), 1 + 0.28 * sin(2 * pi / 360 * i));
	}
	glEnd();

	glPointSize(8.0);
	glBegin(GL_POINTS);
	glColor3f(sunR, 0, 0);
	for (int i = 0; i < 25; i++)
	{
		glVertex2f(1 + 0.32 * cos(2 * pi / 25 * i), 1 + 0.32 * sin(2 * pi / 25 * i));
	}
	glEnd();



	//sea
	glBegin(GL_POLYGON);
	glColor3f(0, seaColorG, seaColorB);
	glVertex2f(-1, -0.7);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, -0.7);
	glEnd();
	
	glPushMatrix();
	glTranslatef(move, 0, 0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0.2);

	glVertex2f(-0.9, -0.8);
	glVertex2f(-0.6, -0.8);

	glVertex2f(-0.52, -0.8);
	glVertex2f(-0.46, -0.8);

	glVertex2f(-0.33, -0.9);
	glVertex2f(-0.072, -0.9);

	glVertex2f(0.028, -0.9);
	glVertex2f(0.01, -0.9);

	glVertex2f(0.26, -0.82);
	glVertex2f(0.54, -0.82);

	glVertex2f(0.68, -0.82);
	glVertex2f(0.8, -0.82);

	glEnd();
	glPopMatrix();

	

	
	
	//clound
	glPushMatrix();
	glTranslatef(move, 0, 0);
	move = move + (-1*speed/100);
	if (move >2)
	{
		move = -0.5;
		
	}
	else if (move < -2)
	{
		move = 0.5;
	}

	glBegin(GL_POLYGON);
	glColor3f(cloundRGB, cloundRGB, cloundRGB);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(-0.882 + 0.06* cos(2 * pi / 360 * i), 0.626 + 0.06 * sin(2 * pi / 360 * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(cloundRGB, cloundRGB, cloundRGB);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(-0.802 + 0.1 * cos(2 * pi / 360 * i), 0.662 + 0.1 * sin(2 * pi / 360 * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(cloundRGB, cloundRGB, cloundRGB);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(-0.7 + 0.15 * cos(2 * pi / 360 * i), 0.7 + 0.15 * sin(2 * pi / 360 * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(cloundRGB, cloundRGB, cloundRGB);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(-0.557 + 0.1 * cos(2 * pi / 360 * i), 0.661 + 0.1 * sin(2 * pi / 360 * i));
	}
	glEnd();

	//clound2
	glBegin(GL_POLYGON);
	glColor3f(cloundRGB, cloundRGB, cloundRGB);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(0.39 + 0.06 * cos(2 * pi / 360 * i), 0.425 + 0.06 * sin(2 * pi / 360 * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(cloundRGB, cloundRGB, cloundRGB);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(0.471 + 0.1 * cos(2 * pi / 360 * i), 0.462 + 0.1 * sin(2 * pi / 360 * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(cloundRGB, cloundRGB, cloundRGB);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(0.573 + 0.15 * cos(2 * pi / 360 * i), 0.5 + 0.15 * sin(2 * pi / 360 * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(cloundRGB, cloundRGB, cloundRGB);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(0.716 + 0.1 * cos(2 * pi / 360 * i), 0.46 + 0.1 * sin(2 * pi / 360 * i));
	}
	glEnd();
	glPopMatrix();



	//mountain
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.745, 0);
	glVertex2f(-1,-0.7);
	glVertex2f(-0.6,0);
	glVertex2f(-0.2,-0.7);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.745, 0);
	glVertex2f(0.3, -0.7);
	glVertex2f(0.6, -0.2);
	glVertex2f(0.9, -0.7);
	glEnd();

	//windmill

	//roof
	

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.361, 0.2);
	glVertex2f(-0.2, 0.1);
	glVertex2f(0, 0.3);
	glVertex2f(0.2, 0.1);
	glEnd();

	glColor3f(0.7, 0.7, 0.7);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-0.05, 0.25);
	glVertex2f(0, 0.25);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0.03, 0.25);
	glVertex2f(0.05, 0.25);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.1, 0.2);
	glVertex2f(-0.05, 0.2);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0.05, 0.2);
	glVertex2f(0.1, 0.2);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.15, 0.15);
	glVertex2f(-0.1, 0.15);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.05, 0.15);
	glVertex2f(0.1, 0.15);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0.361, 0.2);
	glVertex2f(-0.2, 0);
	glVertex2f(-0.2, 0.1);
	glVertex2f(0.2, 0.1);
	glVertex2f(0.2, 0);
	glEnd();

	//outline roof
	glLineWidth(1.5);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(-0.2, 0.1);
	glVertex2f(0.2, 0.1);

	glVertex2f(-0.2, 0.1);
	glVertex2f(0, 0.3);

	glVertex2f(0, 0.3);
	glVertex2f(0.2, 0.1);

	glVertex2f(-0.2, 0.1);
	glVertex2f(-0.2, 0);

	glVertex2f(0.2, 0.1);
	glVertex2f(0.2, 0);

	glVertex2f(-0.2, 0);
	glVertex2f(0.2, 0);
	glEnd();

	//WALL
	glBegin(GL_POLYGON);
	glColor3f(0.9, 1, 1);
	glVertex2f(-0.3, -0.6);
	glVertex2f(-0.18, 0);
	glVertex2f(0.18, 0);
	glVertex2f(0.3, -0.6);
	glEnd();
	//texture

	glColor3f(0.7, 0.7, 0.7);
	glLineWidth(1);
	glBegin(GL_LINES);

	glVertex2f(-0.15, -0.1);
	glVertex2f(-0.05, -0.1);

	glVertex2f(0.1, -0.1);
	glVertex2f(0.2, -0.1);

	glVertex2f(-0.22, -0.2);
	glVertex2f(-0.14, -0.2);

	glVertex2f(0.22, -0.2);
	glVertex2f(0.15, -0.2);

	glVertex2f(-0.24, -0.3);
	glVertex2f(-0.12, -0.3);

	glVertex2f(0.2, -0.3);
	glVertex2f(0.1, -0.3);

	glVertex2f(0.2, -0.4);
	glVertex2f(0.26, -0.4);

	glVertex2f(-0.08, -0.4);
	glVertex2f(-0.26, -0.4);

	glVertex2f(0, -0.4);
	glVertex2f(0.1, -0.4);

	glVertex2f(-0.28, -0.5);
	glVertex2f(-0.14, -0.5);

	glVertex2f(0.1, -0.5);
	glVertex2f(0.28, -0.5);



	glEnd();

	//outline
	glLineWidth(1.5);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);

	glVertex2f(-0.3, -0.6);
	glVertex2f(-0.18, 0);

	glVertex2f(0.18, 0);
	glVertex2f(0.3, -0.6);

	glEnd();

	//window
	glBegin(GL_POLYGON);
	glColor3f(1, 0.2, 0.4);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(0.06 * cos(2 * pi / 360 * i), -0.16 + 0.06 * sin(2 * pi / 360 * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 0.2, 0.4);
	glVertex2f(-0.06, -0.16);
	glVertex2f(-0.06, -0.28);
	glVertex2f(0.06, -0.28);
	glVertex2f(0.06, -0.16);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-0.08, -0.28);
	glVertex2f(-0.08, -0.3);
	glVertex2f(0.08, -0.3);
	glVertex2f(0.08, -0.28);
	glEnd(); 

	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.06, -0.16);
	glVertex2f(0.06,-0.16);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(0, -0.16);
	glVertex2f(0, -0.28);
	glEnd();



	//door
	glBegin(GL_POLYGON);
	glColor3f(1, 0.2, 0.4);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f( 0.06 * cos(2 * pi / 360 * i), -0.5+ 0.06 * sin(2 * pi / 360 * i));
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1, 0.2, 0.4);
	glVertex2f(-0.06, -0.5);
	glVertex2f(-0.06, -0.6);
	glVertex2f(0.06, -0.6);
	glVertex2f(0.06, -0.5);
	glEnd();

	glPointSize(3);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	glVertex2f(0.04, -0.53);
	glEnd();



	glBegin(GL_POLYGON);
	glColor3f(0.5, 0, 0);
	glVertex2f(-0.4, -0.6);
	glVertex2f(-0.4, -0.65);
	glVertex2f(0.4, -0.65);
	glVertex2f(0.4, -0.6);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0.8, 0);
	glVertex2f(-0.55, -0.65);
	glVertex2f(-0.6, -0.75);
	glVertex2f(0.6, -0.75);
	glVertex2f(0.55, -0.65);
	glEnd();

	
	//up
	glPushMatrix();
	glTranslatef(0, 0.2, 0);

	glPushMatrix();
	glRotatef(angle, 0, 0, 1);
	glTranslatef(0, -0.2, 0);
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-0.005, 0.205);
	glVertex2f(-0.005, 0.701);
	glVertex2f(0.005, 0.701);
	glVertex2f(0.005, 0.205);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, leafcolorB);
	glVertex2f(0.005, 0.701);
	glVertex2f(0.005, 0.351);
	glVertex2f(0.15, 0.351);
	glVertex2f(0.15, 0.701);
	glEnd();
	//

	//right
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(0.005, 0.195);
	glVertex2f(0.005, 0.205);
	glVertex2f(0.501, 0.205);
	glVertex2f(0.501, 0.195);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, leafcolorB);
	glVertex2f(0.151, 0.05);
	glVertex2f(0.151, 0.195);
	glVertex2f(0.501, 0.195);
	glVertex2f(0.501, 0.05);
	glEnd();
	//

	//down
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-0.005, 0.195);
	glVertex2f(-0.005, -0.3);
	glVertex2f(0.005, -0.3);
	glVertex2f(0.005, 0.195);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, leafcolorB);
	glVertex2f(-0.15, 0.05);
	glVertex2f(-0.15, -0.301);
	glVertex2f(-0.005, -0.301);
	glVertex2f(-0.005, 0.05);
	glEnd();
	
	//left
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(-0.005, 0.195);
	glVertex2f(-0.005, 0.205);
	glVertex2f(-0.501, 0.205);
	glVertex2f(-0.501, 0.195);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, leafcolorB);
	glVertex2f(-0.501, 0.205);
	glVertex2f(-0.501, 0.35);
	glVertex2f(-0.151, 0.35);
	glVertex2f(-0.151, 0.205);
	glEnd();
	//

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(0.02 * cos(2*pi / 360 * i), 0.2 + 0.02 * sin(2*pi / 360 * i));
	}
	glEnd();
	angle += speed;
	if (angle > 358)
		angle = 0;
	
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(hideHintX,hideHintY,0);
	glColor3f(textRGB, textRGB, textRGB);
	glRasterPos2f(-0.95, -0.95);
	drawString("Press 'H' for Hint/Guide");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(showHintX, showHintY, 0);
	glColor3f(textRGB, textRGB, textRGB);
	glRasterPos2f(-0.95, -0.85);
	drawString("Q/E for anticlockwise/clockwise, W/S for speed increase/decrease.");
	glRasterPos2f(-0.95, -0.9);
	drawString("Space for stop the spining 'W' continue, 'N' for toggle between day/night");
	glRasterPos2f(-0.95, -0.95);
	drawString("1/2 for togle between question, Please 'H' again to hide the hint.");
	glPopMatrix();
}

void display()
{
	
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	if (qNo == 2)
	{
		windmill();
	}
	else if(qNo==1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 0,0);
		glPushMatrix();
		glTranslatef(xfirst, yfirst, 0);
		glBegin(GL_QUADS);
		glColor3f(0, 1, 0);
		glVertex2f(-0.3, 0);
		glVertex2f(-0.3, 0.3);
		glVertex2f(0.3, 0.3);
		glVertex2f(0.3, 0);
		glEnd();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(x2, y2, 0);
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex2f(-0.3, 0);
		glVertex2f(-0.3, 0.3);
		glVertex2f(0.3, 0.3);
		glVertex2f(0.3, 0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 1);
		glRasterPos2f(-0.95, -0.90);
		drawString("Try arrow key up,down,left,right");
		glRasterPos2f(-0.95, -0.95);
		drawString("1/2 To toggle between question, space to reset");
		glPopMatrix();

	}
	
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------