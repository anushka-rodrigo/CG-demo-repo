#include "car.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

//draw a single wheel
void drawWheel(float radius, float width) {
    glColor3f(0.0f, 0.0f, 0.0f); // black color wheel

    GLUquadric* quad = gluNewQuadric(); // create a quadric object

    glPushMatrix();
    glRotatef(90, 0, 0, 1); // rotate to align cylinder along X-axis
    gluCylinder(quad, radius, radius, width, 30, 1); // base radius, top radius, height, slices, stacks

    // Draw the two wheel caps
    gluDisk(quad, 0.0, radius, 30, 1);       // one end
    glTranslatef(0.0f, 0.0f, width);         // move to the other end
    gluDisk(quad, 0.0, radius, 30, 1);       // other end

    glPopMatrix();
    gluDeleteQuadric(quad);
}

//car body
void carBody(){
    //rectangle shape
    /*
    glPushMatrix();
    glColor3f(0.3f, 0.0f, 0.0f);
    //glscalef is the size of obj, x,y,z
    glScalef(2.0f, 0.5f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    */

    glPushMatrix();
    glColor3f(0.7f, 0.0f, 0.0f); //dark red body
    glTranslatef(0.0f, -0.2f, 0.0f);

    //dimensions
    float lengthBottom = 2.0f;
    float lengthTop    = 1.4f;
    float height       = 0.35f;
    float width        = 0.7f;

    float frontX =  lengthBottom / 2; //vertical side
    float backBottomX = -lengthBottom / 2;
    float backTopX    = backBottomX + (lengthBottom - lengthTop); //left slanted

    glBegin(GL_QUADS);

    //Bottom
    glVertex3f(backBottomX, 0.0f, -width/2);
    glVertex3f(frontX,      0.0f, -width/2);
    glVertex3f(frontX,      0.0f,  width/2);
    glVertex3f(backBottomX, 0.0f,  width/2);

    //Top
    glVertex3f(backTopX, height, -width/2);
    glVertex3f(frontX,   height, -width/2);
    glVertex3f(frontX,   height,  width/2);
    glVertex3f(backTopX, height,  width/2);

    //Front (vertical)
    glVertex3f(frontX, 0.0f,  width/2);
    glVertex3f(frontX, 0.0f, -width/2);
    glVertex3f(frontX, height, -width/2);
    glVertex3f(frontX, height,  width/2);

    //Back (slanted)
    glVertex3f(backBottomX, 0.0f,  width/2);
    glVertex3f(backBottomX, 0.0f, -width/2);
    glVertex3f(backTopX,    height, -width/2);
    glVertex3f(backTopX,    height,  width/2);

    //left
    glVertex3f(backBottomX, 0.0f, -width/2);
    glVertex3f(frontX,      0.0f, -width/2);
    glVertex3f(frontX,      height, -width/2);
    glVertex3f(backTopX,    height, -width/2);

    //right
    glVertex3f(backBottomX, 0.0f, width/2);
    glVertex3f(frontX,      0.0f, width/2);
    glVertex3f(frontX,      height, width/2);
    glVertex3f(backTopX,    height, width/2);

    glEnd();
    glPopMatrix();
}

//car cabin trapezoidal
void carCabin(){
    //Car Cabin (rectangle)
    //glPushMatrix();
    //glColor3f(0.8f, 0.8f, 0.8f);
    //glTranslatef(0.1f, 0.35f, 0.0f);
    //glScalef(0.8f, 0.3f, 0.4f);
    //glutSolidCube(1.0f);
    //glPopMatrix();

    glPushMatrix();
    glColor3f(0.9f, 0.8f, 0.4f);
    glTranslatef(0.25f, 0.1f, 0.0f); // position on top of car body

    float cabinLengthTop = 0.4f;
    float cabinLengthBottom = 0.7f;
    float cabinHeight = 0.2f;
    float cabinWidth = 0.5f;

    // Draw trapezoidal cabin as 6 faces
    glBegin(GL_QUADS);

    //bottom face
    glVertex3f(-cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    glVertex3f(-cabinLengthBottom/2, 0.0f,  cabinWidth/2);
    glVertex3f( cabinLengthBottom/2, 0.0f,  cabinWidth/2);
    glVertex3f( cabinLengthBottom/2, 0.0f, -cabinWidth/2);

    //top face
    glVertex3f(-cabinLengthTop/2, cabinHeight, -cabinWidth/2);
    glVertex3f(-cabinLengthTop/2, cabinHeight,  cabinWidth/2);
    glVertex3f( cabinLengthTop/2, cabinHeight,  cabinWidth/2);
    glVertex3f( cabinLengthTop/2, cabinHeight, -cabinWidth/2);

    //front face
    glVertex3f( cabinLengthBottom/2, 0.0f,  cabinWidth/2);
    glVertex3f( cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    glVertex3f( cabinLengthTop/2,    cabinHeight, -cabinWidth/2);
    glVertex3f( cabinLengthTop/2,    cabinHeight,  cabinWidth/2);

    //back face
    glVertex3f(-cabinLengthBottom/2, 0.0f,  cabinWidth/2);
    glVertex3f(-cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    glVertex3f(-cabinLengthTop/2,    cabinHeight, -cabinWidth/2);
    glVertex3f(-cabinLengthTop/2,    cabinHeight,  cabinWidth/2);

    //left face
    glVertex3f(-cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    glVertex3f( cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    glVertex3f( cabinLengthTop/2,    cabinHeight, -cabinWidth/2);
    glVertex3f(-cabinLengthTop/2,    cabinHeight, -cabinWidth/2);

    //right face
    glVertex3f(-cabinLengthBottom/2, 0.0f,  cabinWidth/2);
    glVertex3f( cabinLengthBottom/2, 0.0f,  cabinWidth/2);
    glVertex3f( cabinLengthTop/2,    cabinHeight,  cabinWidth/2);
    glVertex3f(-cabinLengthTop/2,    cabinHeight,  cabinWidth/2);

    glEnd();
    glPopMatrix();
}

//car spoiler
void carSpoiler(){
    //spoiler base angled
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f); //grey base
    glTranslatef(1.0f, 0.2f, 0.0f); // X = rear, Y = top of body, Z = center
    glRotatef(30.0f, 0.0f, 0.0f, 1.0f); //rotate spoiler: (angle,x,y,z)
    glScalef(0.4f, 0.05f, 0.5f); //scale: (length, height, width)
    glutSolidCube(1.0f);
    glPopMatrix();

    //spoiler top flat
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); //black main part
    glTranslatef(1.2f, 0.3f, 0.0f);
    glScalef(0.4f, 0.05f, 0.7f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

//car wheels
void carWheels(){
    float radius = 0.17f;
    float width = 0.1f; // thickness of wheel

    //back wheel left side
    glPushMatrix();
    glTranslatef(0.65f, -0.2f, 0.3f); //wheel position
    drawWheel(radius, width);
    glPopMatrix();

    //back wheel right side
    glPushMatrix();
    glTranslatef(0.65f, -0.2f, -0.4f);
    drawWheel(radius, width);
    glPopMatrix();

    //front wheel left side
    glPushMatrix();
    glTranslatef(-0.40f, -0.2f, 0.3f);
    drawWheel(radius, width);
    glPopMatrix();

    //front wheel right side
    glPushMatrix();
    glTranslatef(-0.40f, -0.2f, -0.4f);
    drawWheel(radius, width);
    glPopMatrix();
}

//draw entire car
void drawCar() {
    glPushMatrix();

    glTranslatef(carX, 0.6f, carZ);
    glRotatef(carAngle, 0.0f, 1.0f, 0.0f);


    glScalef(3.0f, 3.0f, 3.0f); //scale car

    carBody();
    carCabin();
    carSpoiler();
    carWheels();

    glPopMatrix();
}
