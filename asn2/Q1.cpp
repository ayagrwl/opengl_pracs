#include <iostream>
#include <GL/glut.h>
#include <vector>

using namespace std;

// Set window height and width.

const double WIDTH = 500;
const double HEIGHT = 500;

int x0,yy0,x2,y2;

// take user input
void initPoints(){
    cout<<"Enter the coordinates of the vertices in order.\n";
    cout<<"For the sake of viewing, keep the points in the range -50,50\n";
    cin>>x0>>yy0>>x2>>y2;
}

// main drawing function for glut
void drawObject(){

    // Draw the X-axis
    glBegin(GL_LINES);
        glVertex2f(-50, 0);
        glVertex2f(50, 0);
    glEnd();

    // Draw the y-axis
    glBegin(GL_LINES);
        glVertex2f(0, -50);
        glVertex2f(0, 50);
    glEnd();
    
    // draw rectangle
    glRecti(x0, yy0, x2, y2);
    glFlush();
}

void myInit (void){
    // Reset background color with black (since all three argument is 0.0)
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
      
    // Set width of point to one unit
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
      
    // Set window size in X- and Y- direction
    gluOrtho2D(-50, 50, -50, 50);
}

int main(int argc, char** argv){
    initPoints();
    // GLute init and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(600,100);
    glutCreateWindow("Rectangle");

    myInit();
    glutDisplayFunc(drawObject);
    glutMainLoop();
}




