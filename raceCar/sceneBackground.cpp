#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

// Global variables for car movement (controlled by arrow keys)
float carX = 0.0f;
float carZ = 0.0f;

// -------------------------
// Draw a single wheel
// -------------------------
void drawWheel(float radius, float innerRadius, int sides) {
    glColor3f(0.1f, 0.1f, 0.1f);
    glutSolidTorus(innerRadius, radius, sides, sides);
}

// -------------------------
// Draw entire car
// -------------------------
void drawCar() {
    glPushMatrix();
    glTranslatef(carX, 0.0f, carZ);

    // --- Car Body ---
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glScalef(1.5f, 0.5f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // --- Car Cabin ---
    glPushMatrix();
    glColor3f(0.8f, 0.8f, 0.8f);
    glTranslatef(0.1f, 0.35f, 0.0f);
    glScalef(0.8f, 0.3f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // --- Wheels ---
    float wheelRadius = 0.2f;
    float inner = 0.05f;

    glPushMatrix();
    glTranslatef(0.5f, -0.25f, 0.25f);
    drawWheel(wheelRadius, inner, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, -0.25f, -0.25f);
    drawWheel(wheelRadius, inner, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, -0.25f, 0.25f);
    drawWheel(wheelRadius, inner, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, -0.25f, -0.25f);
    drawWheel(wheelRadius, inner, 20);
    glPopMatrix();

    glPopMatrix();
}

// -------------------------
// Draw a Policeman
// -------------------------
void drawPoliceman(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    // Body (Blue shirt)
    glColor3f(0.0f, 0.0f, 0.8f); // Blue
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    glScalef(0.5f, 0.8f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Head (Peach/Skin color)
    glColor3f(1.0f, 0.85f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, 1.2f, 0.0f);
    glutSolidSphere(0.25f, 15, 15);
    glPopMatrix();

    // Cap (Blue)
    glColor3f(0.0f, 0.0f, 0.8f);
    glPushMatrix();
    glTranslatef(0.0f, 1.4f, 0.0f);
    glRotatef(90, 1, 0, 0); // Rotate to sit flat
    glutSolidTorus(0.05f, 0.25f, 15, 15); // Brim
    glutSolidSphere(0.25f, 15, 15); // Top of cap
    glPopMatrix();

    glPopMatrix();
}

// -------------------------
// Draw a Tree
// -------------------------
void drawTree(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    // Tree Trunk (Brown)
    glColor3f(0.55f, 0.27f, 0.07f);
    glPushMatrix();
    glScalef(0.4f, 2.0f, 0.4f);
    glTranslatef(0.0f, 0.5f, 0.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tree Leaves (Green Sphere) - Made larger
    glColor3f(0.0f, 0.6f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    glutSolidSphere(1.8f, 15, 15); // Increased size from 1.5 to 1.8
    glPopMatrix();

    glPopMatrix();
}

// -------------------------
// Draw Environment (Road & Grass)
// -------------------------
void drawEnvironment() {
    // 1. Draw Grass (Infinite Green Plane)
    glColor3f(0.2f, 0.6f, 0.2f); // Grass Green
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-100.0f, -0.55f, -100.0f);
        glVertex3f(-100.0f, -0.55f,  100.0f);
        glVertex3f( 100.0f, -0.55f,  100.0f);
        glVertex3f( 100.0f, -0.55f, -100.0f);
    glEnd();

    // Road Dimensions - Made wider
    float roadWidth = 6.0f;   // Increased width from 5.0 to 6.0
    float roadY = -0.50f;
    float stripeY = -0.49f;

    // ROAD GEOMETRY:
    // 1. Horizontal segment: From Right (X=30) to Left (X=-20)
    // 2. Vertical segment: From Corner (X=-20) to Top (Z=-40)

    // --- A. Asphalt Road Surfaces ---
    glColor3f(0.25f, 0.25f, 0.25f); // Dark Gray

    // Horizontal Segment
    glBegin(GL_QUADS);
        glVertex3f(-20.0f - roadWidth/2, roadY, -roadWidth/2); // Extend to corner edge
        glVertex3f(-20.0f - roadWidth/2, roadY,  roadWidth/2);
        glVertex3f( 30.0f, roadY,  roadWidth/2);
        glVertex3f( 30.0f, roadY, -roadWidth/2);
    glEnd();

    // Vertical Segment (Starts at X=-20, goes UP to Z=-40)
    glBegin(GL_QUADS);
        glVertex3f(-20.0f - roadWidth/2, roadY, -roadWidth/2);
        glVertex3f(-20.0f + roadWidth/2, roadY, -roadWidth/2);
        glVertex3f(-20.0f + roadWidth/2, roadY, -40.0f);
        glVertex3f(-20.0f - roadWidth/2, roadY, -40.0f);
    glEnd();

    // --- B. White Dotted Lines ---
    glColor3f(1.0f, 1.0f, 1.0f); // White
    float stripeLen = 2.0f;
    float gapLen = 2.0f;
    float stripeW = 0.3f;

    // Stripes for Horizontal Segment (Right to Left)
    for (float x = 28.0f; x > -20.0f; x -= (stripeLen + gapLen)) {
        glBegin(GL_QUADS);
            glVertex3f(x - stripeLen, stripeY, -stripeW/2);
            glVertex3f(x - stripeLen, stripeY,  stripeW/2);
            glVertex3f(x, stripeY,  stripeW/2);
            glVertex3f(x, stripeY, -stripeW/2);
        glEnd();
    }

    // Stripes for Vertical Segment (Upwards)
    for (float z = -roadWidth/2; z > -40.0f; z -= (stripeLen + gapLen)) {
        glBegin(GL_QUADS);
            glVertex3f(-20.0f - stripeW/2, stripeY, z);
            glVertex3f(-20.0f + stripeW/2, stripeY, z);
            glVertex3f(-20.0f + stripeW/2, stripeY, z - stripeLen);
            glVertex3f(-20.0f - stripeW/2, stripeY, z - stripeLen);
        glEnd();
    }

    // --- C. Objects (Tree and Policeman) ---

    // Tree: "Inside" the curve (Top right relative to corner)
    drawTree(-10.0f, -15.0f);

    // Policeman: Beside the horizontal road (Right side of screen)
    // Standing on the grass, looking at the road
    drawPoliceman(10.0f, -5.0f);
}

// -------------------------
// Arrow Key Movement Handler
// -------------------------
void specialKeys(int key, int x, int y) {
    float speed = 0.5f;

    switch (key) {
        case GLUT_KEY_LEFT:
            carX -= speed;
            break;
        case GLUT_KEY_RIGHT:
            carX += speed;
            break;
        case GLUT_KEY_UP:
            carZ -= speed;
            break;
        case GLUT_KEY_DOWN:
            carZ += speed;
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

    // CAMERA SETUP
    // Much closer zoom to make objects appear larger
    gluLookAt(
        -5.0, 18.0, 8.0,    // Eye position (Lower and significantly closer in Z)
        -5.0, 0.0, -12.0,   // Look-at center (Focused on the road curve/middle)
        0.0, 1.0, 0.0       // Up vector
    );

    drawEnvironment();
    drawCar();

    glutSwapBuffers();
}

// -------------------------
void init() {
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    // Background color matches the grass green to hide "sky" edges
    glClearColor(0.2f, 0.6f, 0.2f, 1.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Light coming from top-right
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
