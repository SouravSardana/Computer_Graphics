#include<gl/glut.h>
#include"Header.h"     //Import header file

static const  int screenwidth = 1000;    //Custom window width
static const int screenheight = 1000;     //Custom window height
vector<point> p; //Polygon point set vector
vector<polygon> s; //Polygon vector, used to save the finished polygon
int move_x, move_y; //The current coordinate value of the mouse, used when the mouse moves dynamically to draw a line
bool select = false; //Polygon closed state judgment variable, when it is true, press the right mouse button to close the polygon
bool judge = false;
float red = 1.0, green = 0.0, blue = 0.0;
int lineWidth = 1;   //Use this to change the style of the line segment
GLuint Line;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);              // The role of glClearColor is to specify the color used when refreshing the color buffer
	glMatrixMode(GL_PROJECTION);              
	gluOrtho2D(0.0, screenwidth, 0.0, screenheight);         //Corresponding model coordinate range
}
void lineSegment()
{
	glClear(GL_COLOR_BUFFER_BIT);    //The function of clearing the color buffer is to prevent the original color information in the buffer from affecting the drawing
	glColor3f(red, green, blue);   //Set the color by changing red, green, blue, which is both the line color and the fill color
	int num = 0;//The two loop control variables will be called multiple times in the following vector loop and array loop.
	if (judge) {
		if (!p.empty())
		{
			//Line = glGenLists(1);
			//glNewList(Line, GL_COMPILE);
			// int i = p.size()-1; //Connect the determined last point to the current mouse position, that is, draw a line dynamically
			glBegin(GL_LINES);
			glVertex2i(p[num].x, p[num].y);    //Draw the left point of the mouse click and the current point of the mouse
			glVertex2i(move_x, move_y);
			glEnd();
		}
	}
	glFlush();
}
void myMouse(int button, int state, int x, int y) //Mouse click event response function
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)//When the left mouse button is clicked
	{
		int num = p.size();
		if (!p.empty()) {               //Pop all the vector elements in the stack, the purpose is to delete the first line when drawing the second line
			for (int i = 0;i < num;i++) {
				p.pop_back();
			}
		}
		point v;   //Apply for a point class variable, the point class is a custom class, defined in zl.h
		v.x = x;   //Store the coordinates of the clicked point, that is, the values ​​of x and y into v
		v.y = screenheight - y;
		p.push_back(v);    //Store the point information into the polygon point set vector p
		glutPostRedisplay();   //Redraw the window
	}

	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON) //Judging whether the mouse is released, if the mouse is released, the next time you click the left button of the mouse, the line will not be connected
	{
		judge = false;
	}
}
void myMotionFunc(int x, int y) //Mouse movement event response function
{
	move_x = x;          //Save the value of the coordinates of the current mouse
	move_y = screenheight - y;
	judge = true;            //Judge the pressed button, if you release the mouse and move, draw the line
	glutPostRedisplay();
}

void processSpqcialKeys(int key, int x, int y) {       //Press the button to change the color of the line
	if (key == 27)
		exit(0);
	switch (key)
	{
	case GLUT_KEY_F1:              //Change the color of the line segment when clicking the F1 button on the mouse
		red = 0.5;
		green = 0.5;
		blue = 0.0;
		break;
	case GLUT_KEY_F2:
		red = 0.0;
		green = 1.0;
		blue = 0.0;
		break;
	case GLUT_KEY_F3:
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		break;
	case GLUT_KEY_UP:             //Press the up arrow key on the keyboard to make the line thicker
		lineWidth = lineWidth + 2;
		glLineWidth(lineWidth);
		break;
	case GLUT_KEY_DOWN:  //Press the up arrow key on the keyboard to make the line segment thinner
		lineWidth = lineWidth - 2;
		glLineWidth(lineWidth);
		break;
	default:
		break;
	}
}

//At this time, pay attention to pressing CTRL+a when pressing the key. At this time, the ascall of a changes to 1, and z changes to 26. Others change according to this rule 
void processNormalKey(unsigned char key, int x, int y) {   //Use the key combination to change the color of the line segment
	printf("shift:%d ", key);
	int mod = glutGetModifiers();
	if (mod == GLUT_ACTIVE_CTRL)   //Press CTRL+a to change the color of the line segment
	{
		if (key == 1)       //Corresponding to a
		{
			red = 1.0;
			green = 0.0;
			blue = 0.0;
		}
		if (key == 26)    //Corresponding to CTRL+z
		{
			red = 0.0;
			green = 1.0;
			blue = 0.0;
		}
		else if (key == 24)   //Corresponding to CTRL+x
		{
			red = 0.0;
			green = 0.0;
			blue = 1.0;
		}
		else
		{
			red = 1.0;
		}

	}
	else if (mod == GLUT_ACTIVE_SHIFT) {    //When you hold down shift + a, replace the solid line with a dotted line, and correspond to different formats
		if (key == 65)
		{
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(2, 0x4444);
			//printf("line drawing ok"); //corresponding to a
		}
		else if (key == 90)    //Corresponding to z
		{
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(2, 0xffcc);
			//printf("Line drawing ok2");
		}
		else if (key == 88)   //Replace the dotted line with a solid line corresponding to x
		{
			//Line = glGenLists(1);
			//glNewList(Line, GL_COMPILE);
			glDisable(GL_LINE_STIPPLE);           //At this time, cancel the dotted line format and return to the original solid line mode
			//glEnable(GL_LINES);
			//glTranslatef(-50.0, 20.0, 0.0);
			//printf("Draw a line ok3");
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(screenwidth, screenheight);
	glutCreateWindow("Rubber Band Algorithm");
	init();
	glutMouseFunc(myMouse); //Mouse click message monitoring, that is, monitor whether the mouse is clicked, if it is clicked, call the myMouse function
	glutDisplayFunc(lineSegment);//1. The content of the window is drawn 2. The window size is changed 3. The window is redrawn The window will be redrawn
	glutMotionFunc(myMotionFunc); //Mouse movement message monitoring, that is, monitor whether the mouse moves, if it moves, call the myPassiveMotion function
	glutSpecialFunc(processSpqcialKeys);         //Change the color of the button and the thickness of the line
	glutKeyboardFunc(processNormalKey);       //Change the color of the line segment when a key combination is pressed
	glutMainLoop();
	return 0;
}