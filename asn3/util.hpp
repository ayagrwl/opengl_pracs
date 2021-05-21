#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <unistd.h>
// #include <utility>


using namespace std;

typedef pair<int,int> pii;

const int WIDTH = 500;
const int HEIGHT = 500;

const int WC = 250;
const int HC = 250;

const float PIXEL_SIZE = 3;

const int BG = 0;
const int BOUNDARY = 1;
const int INSIDE = 2;

int xc = 0, yc = 0;

const int numColors = 5;

double colors[numColors][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0.5, 0.5, 0.5},    
};



int screen[WIDTH + 1][HEIGHT + 1];

void printScreen(){
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            cout<<screen[j][i]<<" ";
        }
        cout<<"\n";
    }
}

void fetchSeed(int ys){
    // we'll scan for the seed along y = ys;
    for(int i=1;i<WIDTH;i++){
        if((screen[i-1][ys] == BOUNDARY) && ((screen[i][ys] != BOUNDARY))){
            xc = i;
            yc = ys;
            break;
        }
    }
}

void setBoundary(int x1, int y1, int x2, int y2){
    screen[x1 + WC][y1 + HC] = BOUNDARY;

	int dx = x2-x1;
	int dy = y2-y1;

    bool mInv = 0;

    if(abs(dy) > abs(dx)){
        mInv = 1;
        swap(x1, y1);
        swap(x2, y2);
        swap(dx, dy);
    }

    int stepX = (dx > 0);
    int stepY = (dy > 0);
    
    if(dx < 0) {
        stepX = -1;
        dx = -dx;
    }
    if(dy < 0) {
        stepY = -1;
        dy = -dy;
    }

	int x = x1;
	int y = y1;
 
	int p = 2*dy-dx;

	while( x != x2 ){
		if(p >= 0){
			y += stepY;
			p -= 2*dx;
		}

        if(mInv){
            screen[y + WC][x + HC] = BOUNDARY;
        } else {
            screen[x + WC][y + HC] = BOUNDARY;
        }

        p += 2*dy;
		x += stepX;
	}
}

void initPolygon(){
    cout<<"For the sake of viewing, keep the points in the range ±100\n";

    cout<<"Enter the Number of vertices\n";
    int n;cin>>n;
    if(n < 3) {
        cout<<"Atleast 3 vertices\n";
    }
    vector<pair<int,int>> points = vector<pair<int,int>>(n);


    cout<<"Enter Each vertice one by one\n";

    for(int i=0;i<n;i++){
        cin>>points[i].first>>points[i].second;

        xc += points[i].first;
        yc += points[i].second;
    }

    // Choose default seed as center of figure
    xc = xc/n + WC; 
    yc = yc/n + HC;
    
    for(int i=0;i<n;i++){
        int x1 = points[i].first;
        int y1 = points[i].second;

        int x2 = points[(i+1)%n].first;
        int y2 = points[(i+1)%n].second;
        
        cout<<"Edge from: "<<x1<<","<<y1<<" to "<<x2<<","<<y2<<"\n";
        setBoundary(x1,y1,x2,y2);
    }
    cout<<"Scanning for seed along Y = "<<yc - HC<<"\n";
    fetchSeed(yc);

    xc = 10 + WC;
    yc = 10 + HC;

    cout<<"Using Seed "<<xc-WC<<","<<yc-HC<<" as seed\n";
}

void drawObject(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
        glVertex2d(-50, 0);
        glVertex2d(50, 0);
        glVertex2d(0, -50);
        glVertex2d(0, 50);
    glEnd();

    glBegin(GL_POINTS);
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            glColor3dv(colors[screen[j][i]]);
            glVertex2i(j - WC, i - HC);
        }
    }
    glEnd();
    glFlush();
}


void myInit (void){
    // Reset background color with black (since all three argument is 0.0)
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
      
    // Set width of point to one unit
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glPointSize(PIXEL_SIZE);
    // Set window size in X- and Y- direction
    gluOrtho2D(-50, 50, -50, 50);
}





