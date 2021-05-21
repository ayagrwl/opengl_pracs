#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <unistd.h>
// #include <utility>
using namespace std;

const double WIDTH = 500;
const double HEIGHT = 500;

int x0,yy0,x2,y2;

char inp;


void initPoints(){
    cout<<"Enter the coordinates of the vertices in order.\n";
    cout<<"For the sake of viewing, keep the points in the range -40,40\n";

    cin>>x0>>yy0>>x2>>y2;
}

void drawObject(){
    glClear(GL_COLOR_BUFFER_BIT);

    // not available by default so using matrix multiplication

    GLfloat m[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        2.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glMultMatrixf(m);

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
    glutCreateWindow("Sheer Rectangle");
    myInit();

    // Register display callback
    glutDisplayFunc(drawObject);

    glutMainLoop();
}


