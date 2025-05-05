
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

#define ScreenWidth 900 
#define ScreenHeight 900 


float scaleY = (float)1/(ScreenHeight);
float scaleX = (float)1/(ScreenWidth);


struct vec2{
	vec2(double x,double y): x(x), y(y) {}
	double x;
	double y;
};
float julia(vec2 z,vec2 c,int max_iter){
	int j=0;
	
	for(int i=0;i<max_iter;i++){
		j++;
		z = vec2(z.x * z.x - z.y * z.y + c.x, 2.0 * z.x * z.y + c.y);
		if(sqrt(z.x*z.x+z.y*z.y)> float(4)){
			break;
		}
	}
	return float(j)/float(max_iter);
}
int main(void){

	srand(time(NULL));
	GLFWwindow* window; 

	if(!glfwInit()){
		return -1;
	}
	window = glfwCreateWindow(ScreenWidth,ScreenHeight,"Fractal",NULL,NULL);	

	if(!window){
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	float a = -1;
	while(!glfwWindowShouldClose(window)){

		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
 	   	glLoadIdentity();
	    glOrtho(0, ScreenWidth, 0, ScreenHeight, -1, 1);

		glBegin(GL_POINTS);	
		a +=0.01;

		//vec2 c{-1.476*a,a};
		//vec2 c{0.285,0.001};
		vec2 c{0.3499993,0.3499993};
		//vec{a,a}
		for(int i=0;i<ScreenWidth;i++){
			for(int j=0;j<ScreenHeight;j++){
				
				int max_iter = int(abs(sin(time(NULL) * 0.01)) * 1000.0);
				
				float x = (i - ScreenWidth / 2.0) / (ScreenWidth / 4.0);
		        	float y = (j - ScreenHeight / 2.0) / (ScreenHeight / 4.0);


				float f = julia({x,y},c,max_iter);
				glColor3f(f,f,f);
				glVertex2f(i,j);
			}
		}
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	cout.precision(7);
	cout << a << "\n";			
	glfwTerminate();
}
