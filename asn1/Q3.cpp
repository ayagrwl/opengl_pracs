#include <iostream>
#include <GL/glut.h>
#include <vector>
// #include <utility>
using namespace std;

const double WIDTH = 600;
const double HEIGHT = 600;

vector<pair<int,int>> points;

#define inRange(x1,x,x2) ((x>min(x1,x2))&&(x<max(x1,x2)))

void push_octant(int x, int y, int xc, int yc){
    points.push_back({xc+x,xc+y});
    points.push_back({xc+y,xc+x});
    points.push_back({xc+y,xc-x});
    points.push_back({xc+x,xc-y});
    points.push_back({xc-x,xc-y});
    points.push_back({xc-y,xc-x});
    points.push_back({xc-y,xc+x});
    points.push_back({xc-x,xc+y});
}

void makeCircle(int xc, int yc, int r){
    int i=0;
    int x = 0, y = r;
    int P = 5-4*r;
    while(x<y) {
        x++;i++;
        if(P<=0) {
            P += 8*x+12;
        } else {
            y=y-1;
            P += 8*(x-y)+20;
        }
        push_octant(x,y, xc, yc);
    }
}

void initCircle(){
    cout<<"Enter the dim of circle - x_center y_center radius\n";
    cout<<"For the sake of viewing, keep the points in the range -600,600\n";

    int x0 = 200, y0 = 200;
    int r = 200;

    cin>>x0>>y0>>r;

    makeCircle(x0,y0,r);
}


void drawCircle(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
        glVertex2f(-1, 0);
        glVertex2f(1, 0);
    glEnd();
    
    glBegin(GL_LINES);
        glVertex2f(0, -1);
        glVertex2f(0, 1);
    glEnd();

    glBegin(GL_POINTS);
        for(auto &point: points)
            glVertex2f((double)point.first/WIDTH, (double)point.second/HEIGHT);
    glEnd();


    glFlush();
}

int main(int argc, char** argv){
    initCircle();
    // GLute init and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Mid point Circle");

    // Register display callback
    glutDisplayFunc(drawCircle);

    // Glut main Loop
    glutMainLoop();
}








