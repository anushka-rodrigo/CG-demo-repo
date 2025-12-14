#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

// Global variables for car movement (controlled by arrow keys)
float carX = 0.0f;
float carZ = -15.0f; // Start car slightly higher to match new road position

// -------------------------
// Draw a single wheel
// -------------------------
void drawWheel(float radius, float innerRadius, int sides) {
 
}

// -------------------------
// Draw entire car
// -------------------------
void drawCar() {

}

// -------------------------
// Draw a Policeman
// -------------------------
void drawPoliceman(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    glScalef(1.5f, 1.5f, 1.5f);

    // --- Legs (NEW) ---
    glColor3f(0.0f, 0.0f, 0.5f); // Darker blue pants

    // Left Leg
    glPushMatrix();
    glTranslatef(-0.15f, 0.3f, 0.0f); // Positioned below body
    glScalef(0.15f, 0.6f, 0.25f);     // Leg shape
    glutSolidCube(1.0f);
    glPopMatrix();

    // Right Leg
    glPushMatrix();
    glTranslatef(0.15f, 0.3f, 0.0f);
    glScalef(0.15f, 0.6f, 0.25f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // --- Body (Blue shirt) ---
    glColor3f(0.0f, 0.0f, 0.8f);
    glPushMatrix();
    glTranslatef(0.0f, 0.9f, 0.0f); // Moved up to sit on top of legs (0.6 leg height + 0.3 half body)
    glScalef(0.5f, 0.6f, 0.3f);     // Torso
    glutSolidCube(1.0f);
    glPopMatrix();

    // --- Head ---
    glColor3f(1.0f, 0.85f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, 1.35f, 0.0f); // Adjusted for new body height
    glutSolidSphere(0.25f, 15, 15);
    glPopMatrix();

    // --- Cap ---
    glColor3f(0.0f, 0.0f, 0.8f);
    glPushMatrix();
    glTranslatef(0.0f, 1.55f, 0.0f);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.05f, 0.25f, 15, 15);
    glutSolidSphere(0.25f, 15, 15);
    glPopMatrix();

    glPopMatrix();
}

// -------------------------
// Draw a Tree
// -------------------------
void drawTree(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    glScalef(1.4f, 1.4f, 1.4f);

    // --- Tree Trunk ---
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    // Made trunk taller (3.0f) so it sticks out
    glScalef(0.5f, 3.0f, 0.5f);
    glTranslatef(0.0f, 0.5f, 0.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // --- Tree Leaves ---
    glColor3f(0.0f, 0.6f, 0.0f);
    glPushMatrix();
    // Moved leaves HIGHER (3.5f) so the trunk underneath is visible
    glTranslatef(0.0f, 3.5f, 0.0f);
    glutSolidSphere(2.2f, 15, 15);
    glPopMatrix();

    glPopMatrix();
}

// -------------------------
// Draw Environment (Road & Grass)
// -------------------------
void drawEnvironment() {
    // 1. Draw Grass
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-100.0f, -0.55f, -100.0f);
        glVertex3f(-100.0f, -0.55f,  100.0f);
        glVertex3f( 100.0f, -0.55f,  100.0f);
        glVertex3f( 100.0f, -0.55f, -100.0f);
    glEnd();

    float roadWidth = 7.0f;
    float roadY = -0.50f;
    float stripeY = -0.49f;

    // --- Road Positioning Variables ---
    // [ADJUST] Extended roadRightStart to 100.0f so it goes out of sight
    float roadRightStart = 100.0f;
    float roadCornerX = -20.0f;
    float roadTopEnd = -100.0f;

    float roadZOffset = -15.0f;

    // --- A. Asphalt Road Surfaces ---
    glColor3f(0.25f, 0.25f, 0.25f);

    // Horizontal Segment (Right to Left)
    glBegin(GL_QUADS);
        glVertex3f(roadCornerX - roadWidth/2, roadY, roadZOffset - roadWidth/2);
        glVertex3f(roadCornerX - roadWidth/2, roadY, roadZOffset + roadWidth/2);
        glVertex3f(roadRightStart, roadY,  roadZOffset + roadWidth/2);
        glVertex3f(roadRightStart, roadY,  roadZOffset - roadWidth/2);
    glEnd();

    // Vertical Segment (Corner to Top End)
    glBegin(GL_QUADS);
        glVertex3f(roadCornerX - roadWidth/2, roadY, roadZOffset - roadWidth/2);
        glVertex3f(roadCornerX + roadWidth/2, roadY, roadZOffset - roadWidth/2);
        glVertex3f(roadCornerX + roadWidth/2, roadY, roadTopEnd);
        glVertex3f(roadCornerX - roadWidth/2, roadY, roadTopEnd);
    glEnd();

    // --- B. White Dotted Lines ---
    glColor3f(1.0f, 1.0f, 1.0f);
    float stripeLen = 3.0f;
    float gapLen = 3.0f;
    float stripeW = 0.4f;

    // Horizontal Lines loop
    for (float x = roadRightStart - 2.0f; x > roadCornerX; x -= (stripeLen + gapLen)) {
        glBegin(GL_QUADS);
            glVertex3f(x - stripeLen, stripeY, roadZOffset - stripeW/2);
            glVertex3f(x - stripeLen, stripeY, roadZOffset + stripeW/2);
            glVertex3f(x, stripeY, roadZOffset + stripeW/2);
            glVertex3f(x, stripeY, roadZOffset - stripeW/2);
        glEnd();
    }

    // Vertical Lines loop
    for (float z = (roadZOffset - roadWidth/2); z > roadTopEnd; z -= (stripeLen + gapLen)) {
        glBegin(GL_QUADS);
            glVertex3f(roadCornerX - stripeW/2, stripeY, z);
            glVertex3f(roadCornerX + stripeW/2, stripeY, z);
            glVertex3f(roadCornerX + stripeW/2, stripeY, z - stripeLen);
            glVertex3f(roadCornerX - stripeW/2, stripeY, z - stripeLen);
        glEnd();
    }

    // --- C. Objects Positioning ---

    // Adjusted Tree position relative to new road
    drawTree(-5.0f, -30.0f);

    // Adjusted Policeman position relative to new road
    drawPoliceman(15.0f, -22.0f);
}

// -------------------------
// Arrow Key Movement Handler
// -------------------------
void specialKeys(int key, int x, int y) {
  
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

    // Camera adjusted to keep the moved road in view
    gluLookAt(
        -5.0, 25.0, 15.0,
        -5.0, 0.0, -25.0,
        0.0, 1.0, 0.0
    );

    drawEnvironment();
    drawCar();

    glutSwapBuffers();
}

// -------------------------
void init() {
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    // [ADJUST] Set background color to GRAY to act as Sky/Horizon
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = {10, 50, 10, 1};
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
    glutCreateWindow("Car on Road");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
