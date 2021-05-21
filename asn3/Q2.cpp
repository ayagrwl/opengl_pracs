#include "util.hpp"

void FloodFill(int x, int y){
    // if( screen[x][y] == BG ){
        screen[x][y] = INSIDE;
        
        if(x + 1 < WIDTH && (screen[x+1][y] == BG) ) FloodFill(x+1, y);
        if(y + 1 < HEIGHT && (screen[x][y+1] == BG)) FloodFill(x, y+1);
        
        if(x > 0 && (screen[x-1][y] == BG)) FloodFill(x-1, y);
        if(y > 0 && (screen[x][y-1] == BG)) FloodFill(x, y-1);
    // }
}


int main(int argc, char** argv){
    initPolygon();
    
    if(screen[xc][yc] == BG) FloodFill(xc, yc);

    // GLute init and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(600,100);
    glutCreateWindow("Flood Fill");
    myInit();

    // Register display callback
    glutDisplayFunc(drawObject);

    glutMainLoop();
}

