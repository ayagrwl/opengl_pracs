#include "util.hpp"
#include <stack>

void pushUnfilledRight(int xl, int xr, int y, stack<pii> &seed){
    for(bool span=0;xr>=xl;xr--){
        if((screen[xr][y] != BOUNDARY) && (screen[xr][y] != INSIDE)){
            if(!span){
                seed.push({xr,y});
                span = 1;
            }
        } else {
            span = 0;
        }
    }
}

void scanLineSeedFill(int x, int y){
    stack<pii> seeds;
    seeds.push({x,y});
    
    while(!seeds.empty()){
        pii p = seeds.top();
        seeds.pop();

        x = p.first;
        y = p.second;

        // cout<<"Seed: ("<<x<<","<<y<<")\n";
        if(screen[x][y] == INSIDE){
            // Already painted by some other seed.
            continue;
        }
        screen[x][y] = INSIDE;

        int xr,xl;
        
        // filling left
        for(xl=x-1;xl>=0;xl--){
            if((screen[xl][y] == BOUNDARY)) break;
            
            screen[xl][y] = INSIDE;
        } xl++;

        // filling left
        for(xr=x+1;xr<WIDTH;xr++){
            if((screen[xr][y] == BOUNDARY)) break;
            
            screen[xr][y] = INSIDE;
        } xr--;

        // cout<<"xL: "<<xl - WC<<", xR: "<<xr - WC<<", y: "<<y<<"\n";

        if(y+1 < HEIGHT) pushUnfilledRight(xl, xr, y+1, seeds);
        if(y > 0) pushUnfilledRight(xl, xr, y-1, seeds);
    }
}

int main(int argc, char** argv){
    initPolygon();
    scanLineSeedFill(xc, yc);

    // GLute init and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(600,100);
    glutCreateWindow("Scan Line Seed Fill");
    myInit();

    // Register display callback
    glutDisplayFunc(drawObject);

    glutMainLoop();
}