#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

// Global variables for car movement (controlled by arrow keys)
float carX = 0.0f;
float carZ = 0.0f;

// -------------------------
// Draw a single wheel
// -------------------------
void drawWheel(float radius) {
    glColor3f(0.0f, 0.0f, 0.0f); // black color for the wheel

    glPushMatrix();
    glRotatef(90, 0, 0, 1); // rotate 90 around Y axis
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f); // center
        int sides = 30; // smoothness of circle
        for (int i = 0; i <= sides; ++i) {
            float angle = 2.0f * M_PI * i / sides;
            glVertex3f(radius * cos(angle), radius * sin(angle), 0.0f);
        }
    glEnd();
    glPopMatrix();
}

//car's nose
void drawTriangleNose() {
    glColor3f(0.3f, 0.0f, 0.0f); // red color for nose

    glPushMatrix();
    // Position the triangle at the front of the car
    glTranslatef(-1.2f, 0.0f, 0.0f); // adjusted based on car body

    glBegin(GL_TRIANGLES);
        glVertex3f(0.25f, 0.25f, 0.0f);   // top-left
        glVertex3f(-0.25f, -0.25f, 0.0f); // bottom-left
        glVertex3f(0.25f, -0.25f, 0.0f);  // bottom-right (90° corner)

    glEnd();

    glPopMatrix();
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
    glColor3f(0.3f, 0.0f, 0.0f); // red body
    glTranslatef(0.0f, -0.2f, 0.0f);

    // Dimensions
    float lengthBottom = 2.0f;   // bottom length
    float lengthTop    = 1.4f;   // shorter top
    float height       = 0.3f;
    float width        = 0.5f;

    float frontX =  lengthBottom / 2;      // RIGHT side (vertical)
    float backBottomX = -lengthBottom / 2; // bottom-left
    float backTopX    = backBottomX + (lengthBottom - lengthTop); // slanted left

    glBegin(GL_QUADS);

    // -------- Bottom --------
    glVertex3f(backBottomX, 0.0f, -width/2);
    glVertex3f(frontX,      0.0f, -width/2);
    glVertex3f(frontX,      0.0f,  width/2);
    glVertex3f(backBottomX, 0.0f,  width/2);

    // -------- Top --------
    glVertex3f(backTopX, height, -width/2);
    glVertex3f(frontX,   height, -width/2);
    glVertex3f(frontX,   height,  width/2);
    glVertex3f(backTopX, height,  width/2);

    // -------- Front (vertical) --------
    glVertex3f(frontX, 0.0f,  width/2);
    glVertex3f(frontX, 0.0f, -width/2);
    glVertex3f(frontX, height, -width/2);
    glVertex3f(frontX, height,  width/2);

    // -------- Back (slanted) --------
    glVertex3f(backBottomX, 0.0f,  width/2);
    glVertex3f(backBottomX, 0.0f, -width/2);
    glVertex3f(backTopX,    height, -width/2);
    glVertex3f(backTopX,    height,  width/2);

    // -------- Left side --------
    glVertex3f(backBottomX, 0.0f, -width/2);
    glVertex3f(frontX,      0.0f, -width/2);
    glVertex3f(frontX,      height, -width/2);
    glVertex3f(backTopX,    height, -width/2);

    // -------- Right side --------
    glVertex3f(backBottomX, 0.0f, width/2);
    glVertex3f(frontX,      0.0f, width/2);
    glVertex3f(frontX,      height, width/2);
    glVertex3f(backTopX,    height, width/2);

    glEnd();
    glPopMatrix();

}

//car cabin trapezoidal
void carCabin(){
    // --- Car Cabin (rectangle)---
    //glPushMatrix();
    //glColor3f(0.8f, 0.8f, 0.8f);
    //glTranslatef(0.1f, 0.35f, 0.0f);
    //glScalef(0.8f, 0.3f, 0.4f);
    //glutSolidCube(1.0f);
    //glPopMatrix();

    glPushMatrix();
    glColor3f(0.8f, 0.8f, 0.8f);
    glTranslatef(0.25f, 0.05f, 0.0f); // position on top of car body

    float cabinLengthTop = 0.4f;
    float cabinLengthBottom = 0.7f;
    float cabinHeight = 0.2f;
    float cabinWidth = 0.4f;

    // Draw trapezoidal cabin as 6 faces
    glBegin(GL_QUADS);
    // Bottom face
    glVertex3f(-cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    glVertex3f(-cabinLengthBottom/2, 0.0f, cabinWidth/2);
    glVertex3f(cabinLengthBottom/2, 0.0f, cabinWidth/2);
    glVertex3f(cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    // Top face
    glVertex3f(-cabinLengthTop/2, cabinHeight, -cabinWidth/2);
    glVertex3f(-cabinLengthTop/2, cabinHeight, cabinWidth/2);
    glVertex3f(cabinLengthTop/2, cabinHeight, cabinWidth/2);
    glVertex3f(cabinLengthTop/2, cabinHeight, -cabinWidth/2);
    // Front face
    glVertex3f(cabinLengthBottom/2, 0.0f, cabinWidth/2);
    glVertex3f(cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    glVertex3f(cabinLengthTop/2, cabinHeight, -cabinWidth/2);
    glVertex3f(cabinLengthTop/2, cabinHeight, cabinWidth/2);
    // Back face
    glVertex3f(-cabinLengthBottom/2, 0.0f, cabinWidth/2);
    glVertex3f(-cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    glVertex3f(-cabinLengthTop/2, cabinHeight, -cabinWidth/2);
    glVertex3f(-cabinLengthTop/2, cabinHeight, cabinWidth/2);
    // Left face
    glVertex3f(-cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    glVertex3f(cabinLengthBottom/2, 0.0f, -cabinWidth/2);
    glVertex3f(cabinLengthTop/2, cabinHeight, -cabinWidth/2);
    glVertex3f(-cabinLengthTop/2, cabinHeight, -cabinWidth/2);
    // Right face
    glVertex3f(-cabinLengthBottom/2, 0.0f, cabinWidth/2);
    glVertex3f(cabinLengthBottom/2, 0.0f, cabinWidth/2);
    glVertex3f(cabinLengthTop/2, cabinHeight, cabinWidth/2);
    glVertex3f(-cabinLengthTop/2, cabinHeight, cabinWidth/2);
    glEnd();
    glPopMatrix();
}

//car spoiler
void carSpoiler(){
    // --- Spoiler base angled ---
    glPushMatrix();
    glColor3f(0.05f, 0.05f, 0.05f); // grey spoiler base
    // Position: rear-top of car
    glTranslatef(1.0f, 0.1f, 0.0f); // X = rear, Y = top of body, Z = center
    //rotate spoiler
    glRotatef(30.0f, 0.0f, 0.0f, 1.0f); //angle,x,y,z axis
    // Scale: thin long rectangle
    glScalef(0.4f, 0.05f, 0.3f); // length, height, width
    glutSolidCube(1.0f);
    glPopMatrix();


    // --- Spoiler flat ---
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // black spoiler
    // Position: rear-top of car
    glTranslatef(1.2f, 0.2f, 0.0f); // X = rear, Y = top of body, Z = center
    // Scale: thin long rectangle
    glScalef(0.4f, 0.05f, 0.3f); // length, height, width
    glutSolidCube(1.0f);
    glPopMatrix();
}

//car wheels
void carWheels(){
    float wheelRadiusBack = 0.17f;
    float wheelRadiusFront = 0.17f;

    glPushMatrix();
    glTranslatef(0.65f, -0.25f, 0.3f); ////wheel position given by gltranslatef, in gltranslatef X = half body + offset, Z = half width + offset
    drawWheel(wheelRadiusBack);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.65f, -0.25f, -0.3f);
    drawWheel(wheelRadiusBack);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.40f, -0.25f, 0.3f);
    drawWheel(wheelRadiusFront);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.40f, -0.25f, -0.3f);
    drawWheel(wheelRadiusFront);
    glPopMatrix();
}

// -------------------------
// Draw entire car
// -------------------------
void drawCar() {
    glPushMatrix();
    glTranslatef(carX, 0.0f, carZ);

    // --- Car Body ---
    carBody();

    // --- Car Cabin (trapizium)---
    carCabin();

    // --- Front Nose (triangular prism) ---
    //drawTriangleNose();

    //car spoiler
    carSpoiler();

    // --- Wheels ---
    carWheels();

    glPopMatrix();
}

// -------------------------
// Arrow Key Movement Handler
// -------------------------
void specialKeys(int key, int x, int y) {
    float speed = 0.2f;

    switch (key) {
        case GLUT_KEY_UP:
            carX -= speed;
            break;
        case GLUT_KEY_DOWN:
            carX += speed;
            break;
        case GLUT_KEY_LEFT:
            carZ += speed;  // Move forward (toward the screen)
            break;
        case GLUT_KEY_RIGHT:
            carZ -= speed;  // Move backward (into camera)
            break;
    }

    glutPostRedisplay();
}

// -------------------------
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// -------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        0.0, 1.5, 6.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    // --- Road ---
    /*glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-10.0f, -0.5f, -10.0f);
        glVertex3f(-10.0f, -0.5f,  10.0f);
        glVertex3f( 10.0f, -0.5f,  10.0f);
        glVertex3f( 10.0f, -0.5f, -10.0f);
    glEnd();
    */

    drawCar();

    glutSwapBuffers();
}

// -------------------------
void init() {
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = {2, 5, 3, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    GLfloat ambient[] = {0.5, 0.5, 0.5, 1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// -------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Move Car with Arrow Keys");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);  // <<<<<< ENABLE ARROW KEYS

    glutMainLoop();
    return 0;
}
