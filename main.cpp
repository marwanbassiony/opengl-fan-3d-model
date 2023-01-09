#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include<stdio.h>
#include<math.h>
#include <iostream>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include <random>
#include <array>
#include <vector>
#include <algorithm>
using std::vector;
using std::array;
void drawquad(array<array<double, 3>, 4> a){
    glBegin(GL_POLYGON);
    for(auto i : a){ //for each vertex in array a
        glVertex3d(i[0], i[1], i[2]);
    }
    glEnd();
}

void fan(double r,double width){
    glutSolidSphere(r/10, 10, 10);
    double theta=2*acos(-1)/5;
    for(int i =0;i<5;i++){
        double x=r*cos(theta*i);
        double y=r*sin(theta*i);
        array<double, 3> a[4];
        a[0] ={0,0,width/2};
        a[1] ={0,0,-width/2};
        a[2] ={x,y,-width/2};
        a[3] ={x,y,width/2};
        drawquad({a[0],a[1],a[2],a[3]});
    }
}
void body (double r1 , double r2 , double width) {
    if(r1>r2){
       std:: swap(r1,r2);
        
    }
    vector<vector<array<double,3>>>v(4); //array of points
    int point =30;
    double theta = 2*acos(-1)/30;
    for(int i = 0 ; i<=30;i++){
        double x=cos(theta*i);
        double y=sin(theta*i);
        v[0].push_back({r1*x,r1*y,width/2}); //cirle 1
        v[1].push_back({r1*x,r1*y,-width/2}); //circle 2
        v[2].push_back({r2*x,r2*y,width/2}); //3
        v[3].push_back({r2*x,r2*y,-width/2}); //4
    }
    for(int i =1 ;i<=30;i++){
        drawquad({v[0][i],v[0][i-1],v[1][i-1],v[1][i]});
        drawquad({v[2][i],v[2][i-1],v[3][i-1],v[3][i]});
        drawquad({v[1][i],v[1][i-1],v[3][i-1],v[3][i]});
        drawquad({v[2][i],v[2][i-1],v[0][i-1],v[0][i]});

    }
  
}
void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
double angle=0;
double speed =0;
double fanangle=0;
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslated(0, 0, -20); //move origin
    glRotated(angle, 0, 1, 0);
    glColor3d(0, 0, 1);
    body(3, 4, 2);
    glColor3d(0.75, 0.75, 0.75);
    glRotated(fanangle, 0, 0, 1);
    fan(2.8,2);
    fanangle+=speed;
    glutSwapBuffers();
    
}
void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}
void reshape(GLsizei width, GLsizei height) {
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
    glViewport(0, 0, width, height);
 
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.1, 100.0);
}
void normalinput(unsigned char key, int x, int y){
    if(key == 'a'){
        angle --;
    }
    else if(key =='d'){
        angle ++;
    }
    else if(key>='0'&&key<='4'){
        speed=key-'0';
    }
}
void specialinput(int key, int x, int y){
    
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1280, 720); //dim
    glutInitWindowPosition(50, 50); //start top left
    glutCreateWindow("20103415"); //title
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(normalinput); //read input
    glutSpecialFunc(specialinput); //spec case
    initGL();
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
