#include "util.hpp"

void Boundary(int x, int y){
    if( (screen[x][y] != BOUNDARY) && (screen[x][y] != INSIDE)){
        screen[x][y] = INSIDE;
        
        if(x + 1 < WIDTH) Boundary(x+1, y);
        if(y + 1 < HEIGHT) Boundary(x, y+1);
        
        if(x > 0) Boundary(x-1, y);
        if(y > 0) Boundary(x, y-1);
    }
}


int main(int argc, char** argv){
    initPolygon();
    Boundary(xc, yc);

    // GLute init and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(600,100);
    glutCreateWindow("Boundary Fill");
    myInit();

    // Register display callback
    glutDisplayFunc(drawObject);

    glutMainLoop();
}

