#include <GL/glut.h>

// skeleton of the entire project

float carPosX = 5.0f;  // Car starts at the right side of the screen

// Function to draw the car facing left
void drawCar() {
    glPushMatrix();
    glTranslatef(carPosX, 0.5f, 0.0f); // Move car along X-axis

    // Car body
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(2.0f, 0.5f, 1.0f); // Make it wider along X
    glutSolidCube(1.0);
    glPopMatrix();

    // Wheels
    glColor3f(0.0f, 0.0f, 0.0f);
    float wheelOffsetX = 0.7f;
    float wheelOffsetZ = 0.5f;
    for (int i = -1; i <= 1; i += 2) {       // Left/Right
        for (int j = -1; j <= 1; j += 2) {   // Front/Back
            glPushMatrix();
            glTranslatef(i * wheelOffsetX, -0.25f, j * wheelOffsetZ);
            glRotatef(90, 0, 1, 0); // Rotate wheels to align with car
            glutSolidTorus(0.1, 0.2, 12, 12);
            glPopMatrix();
        }
    }

    glPopMatrix();
}

// Draw horizontal road (right to left)
void drawRoad() {
    glColor3f(0.2f, 0.2f, 0.2f); // dark gray
    glBegin(GL_QUADS);
        glVertex3f(5.0f, 0.0f, -2.0f);  // Top-right
        glVertex3f(5.0f, 0.0f, 2.0f);   // Bottom-right
        glVertex3f(-5.0f, 0.0f, 2.0f);  // Bottom-left
        glVertex3f(-5.0f, 0.0f, -2.0f); // Top-left
    glEnd();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera setup
    gluLookAt(0.0, 5.0, 10.0,  // Camera position
              0.0, 0.0, 0.0,   // Look at center
              0.0, 1.0, 0.0);  // Up vector

    drawRoad();
    drawCar();

    glutSwapBuffers();
}

// Timer callback to animate the car
void timer(int value) {
    carPosX -= 0.05f; // Move left
    if (carPosX < -5.0f) carPosX = 5.0f; // Loop back to right
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

// Reshape callback
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Horizontal Car Moving Right to Left");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
