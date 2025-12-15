#include "environment.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

// Draw a Policeman
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


    // --- Arms ---
    glColor3f(0.0f, 0.0f, 0.8f); // Same blue as shirt

    // Left Arm
    glPushMatrix();
    glTranslatef(-0.45f, 1.05f, 0.0f); // Shoulder position
    glRotatef(10.0f, 0, 0, 1);         // Slight outward angle
    glScalef(0.15f, 0.6f, 0.2f);       // Arm shape
    glutSolidCube(1.0f);
    glPopMatrix();

    // Right Arm
    glPushMatrix();
    glTranslatef(0.45f, 1.05f, 0.0f);
    glRotatef(-10.0f, 0, 0, 1);
    glScalef(0.15f, 0.6f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Hands
    glColor3f(1.0f, 0.85f, 0.7f); // Skin color

    // Left Hand
    glPushMatrix();
    glTranslatef(-0.45f, 0.7f, 0.0f);
    glutSolidSphere(0.08f, 10, 10);
    glPopMatrix();

    // Right Hand
    glPushMatrix();
    glTranslatef(0.45f, 0.7f, 0.0f);
    glutSolidSphere(0.08f, 10, 10);
    glPopMatrix();


    glPopMatrix();

}

// Draw a Tree
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

// Draw Environment (Road & Grass)
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
    float roadRightStart = 1000.0f;
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
