//
//  main.cpp
//  AngryBricks
//
//  Created by Pablo Guerra on 2/10/20.
//  Copyright © 2020 Pablo Guerra. All rights reserved.
//
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
using namespace std;
GLenum mode = GL_POLYGON;

float displayPoints[4] = {250, 250, -100, 50};  // Points used to display the cube
int initialPoints[2];           // Initial points when mouse is clicked
int finalPoints[2];             // Final points when mouse is released
int directionX = 0;             // X Direction
int directionY = 0;             // Y Direction
int rotationVal = 30;           // Value for rotation of cube
bool btn1 = false;              // If left mouse button clicked
bool startMotion = false;       // Start/Stop brick motion


// Init function for OpenGL
void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, 0, 500);

}



// Draw 3D cube at location
void cube(float midx, float midy, float midz, float size){
   // Define 8 vertices
    float halfLength = size / 2;
    float ax = midx - halfLength, ay = midy - halfLength, az = midz + halfLength;
    float bx = midx + halfLength, by = midy - halfLength, bz = midz + halfLength;
    float cx = midx + halfLength, cy = midy + halfLength, cz = midz + halfLength;
    float dx = midx - halfLength, dy = midy + halfLength, dz = midz + halfLength;
    float ex = midx - halfLength, ey = midy - halfLength, ez = midz - halfLength;
    float fx = midx + halfLength, fy = midy - halfLength, fz = midz - halfLength;
    float gx = midx + halfLength, gy = midy + halfLength, gz = midz - halfLength;
    float hx = midx - halfLength, hy = midy + halfLength, hz = midz - halfLength;

    // Draw 6 faces (polygons)
    glBegin(mode);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(ax, ay, az);
    glVertex3f(bx, by, bz);
    glVertex3f(cx, cy, cz);
    glVertex3f(dx, dy, dz);
    glEnd();

    glBegin(mode);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(ax, ay, az);
    glVertex3f(dx, dy, dz);
    glVertex3f(hx, hy, hz);
    glVertex3f(ex, ey, ez);
    glEnd();

    glBegin(mode);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(ax, ay, az);
    glVertex3f(ex, ey, ez);
    glVertex3f(fx, fy, fz);
    glVertex3f(bx, by, bz);
    glEnd();

    glBegin(mode);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(gx, gy, gz);
    glVertex3f(fx, fy, fz);
    glVertex3f(ex, ey, ez);
    glVertex3f(hx, hy, hz);
    glEnd();

    glBegin(mode);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(gx, gy, gz);
    glVertex3f(cx, cy, cz);
    glVertex3f(bx, by, bz);
    glVertex3f(fx, fy, fz);
    glEnd();

    glBegin(mode);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(gx, gy, gz);
    glVertex3f(hx, hy, hz);
    glVertex3f(dx, dy, dz);
    glVertex3f(cx, cy, cz);
    glEnd();

}



// Display callback for OpenGL
void display(){
    #ifdef __APPLE__
        glViewport(0, 0, 1000, 1000);
    #endif
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(displayPoints[0], displayPoints[1], displayPoints[2]);
    glRotatef(30, 1.0, -1.0, 0.0);
    cube(-25, -25, displayPoints[2], displayPoints[3]);
    glFlush();
}



// Set cube direction from points
void setMotion(){
    int xDifference = finalPoints[0] - initialPoints[0];
    directionX = -xDifference/5;
    int yDifference = finalPoints[1] - initialPoints[1];
    directionY = -yDifference/5;
}



// Obtain Initial points and display cube
void mouse(int btn, int state, int x, int y){
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        displayPoints[0] = x;
        initialPoints[0] = displayPoints[0];
        displayPoints[1] = 500-y;
        initialPoints[1] = displayPoints[1];
        finalPoints[0] = initialPoints[0];
        finalPoints[1] = initialPoints[1];
        btn1 = true;
        rotationVal = 30;
        glutPostRedisplay();
    }
    else{
        btn1 = false;
    }
    
    // Start/Stop brick motion
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP){
        setMotion();
        startMotion = true;
    }
    else{
        startMotion = false;
    }
}



// Redraw cube on mouse motion
// and get final points
void MouseMotion(int x, int y){
    if (btn1){
        displayPoints[0] = x;
        finalPoints[0] = displayPoints[0];
        displayPoints[1] = 500-y;
        finalPoints[1] = displayPoints[1];
        glutPostRedisplay();
    }
}



// This function is called continuosly
// and updates the rotation and movement of the cube
void myidle() {
    if(startMotion){
        if(displayPoints[0] > 450 || displayPoints[0] < 15){
            directionX *= -1;
        }
        displayPoints[0] += directionX;
        displayPoints[1] += directionY;
        if(displayPoints[1] < 25){
            startMotion = false;
        }
        rotationVal += 8;
        directionY -= 1;
        glutPostRedisplay();
    }
}



// Main program
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Cube");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(MouseMotion);
    glutIdleFunc(myidle);
    init();
    glutMainLoop();
    return 0;
}
