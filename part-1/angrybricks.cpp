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

int points[4] = {306, 207, -1, 50};
bool btn1 = false;



// Init function for OpenGL
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, 0, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(15.0, -1.0, 1.0, 0.0);
}



// Draw 3D cube at location
void cube(float midx, float midy, float midz, float size)
{
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
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(gx, gy, gz);
    glVertex3f(hx, hy, hz);
    glVertex3f(dx, dy, dz);
    glVertex3f(cx, cy, cz);
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

}



// Display callback for OpenGL
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    cube(points[0], points[1], points[2], points[3]);
    glFlush();
}



// Redraw cube on left button click
void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        points[0] = x;
        points[1] = 500 - abs(y);
        btn1 = true;
        glutPostRedisplay();
    }
    else{
        btn1 = false;
    }
}



// Redraw cube on mouse motion
void MouseMotion(int x, int y)
{
    if (btn1){
      points[0] = x;
      points[1] = 500 - abs(y);
      glutPostRedisplay();
    }
}



// Main program
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Cube");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(MouseMotion);
    init();
    glutMainLoop();
    return 0;
}
