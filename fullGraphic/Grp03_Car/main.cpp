#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

// Include our custom modules
#include "Car.h"
#include "Environment.h"

// Define M_PI if necessary
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Global Variables for Car Movement (Defined here, accessed by Car.cpp using 'extern')
float carX = 20.0f;
float carZ = -15.0f;
float carAngle = 0.0f;
float carSpeed = 0.0f; //forward, backward speech
float wheelRotation = 0.0f; //for wheels to rotate
float wheelSteerAngle = 0.0f; //variable to turn the wheels


// ----------------------------------------------------
// CORE CALLBACK FUNCTIONS
// ----------------------------------------------------

// Car movement with arrow keys (from car.cpp)
void specialKeys(int key, int x, int y) {
    float moveSpeed = 0.5f;
    //float rotateSpeed = 5.0f;

    /* this is correct implementation before turning
    switch (key) {
        case GLUT_KEY_DOWN:
            carX += moveSpeed * cos(carAngle * M_PI / 180.0f);
            carZ -= moveSpeed * sin(carAngle * M_PI / 180.0f);
            break;
        case GLUT_KEY_UP:
            carX -= moveSpeed * cos(carAngle * M_PI / 180.0f);
            carZ += moveSpeed * sin(carAngle * M_PI / 180.0f);
            break;
        case GLUT_KEY_LEFT:
            carAngle += rotateSpeed;
            break;
        case GLUT_KEY_RIGHT:
            carAngle -= rotateSpeed;
            break;
        case GLUT_KEY_PAGE_UP:
            carZ -= moveSpeed;
            break;
        case GLUT_KEY_PAGE_DOWN:
            carZ += moveSpeed;
            break;
    }
    */
    float accel = 0.045f;
    float steering = 2.0f;

    switch (key) {
        case GLUT_KEY_UP:
            if (carSpeed < 0.0f){
                carSpeed += accel * 2.5f;  // braking while reversing
            }
            else{
                carSpeed += accel;
            }
            break;

        case GLUT_KEY_DOWN:
            if (carSpeed > 0.0f){
                carSpeed -= accel * 2.5f;  // braking while moving forward
            }
            else{
                carSpeed -= accel;
            }
            break;

        case GLUT_KEY_LEFT:
            if (carSpeed >= 0.0f){
                carAngle += steering; //forward
            }
            else{
                carAngle -= steering; //backward steering
            }
            wheelSteerAngle = 25.0f;   // steer left
            break;

        case GLUT_KEY_RIGHT:
            if (carSpeed >= 0.0f){
                carAngle -= steering; //forward
            }
            else{
                carAngle += steering; //backward steering
            }
            wheelSteerAngle = -25.0f;   // steer right
            break;

        case GLUT_KEY_PAGE_UP:
            carZ -= moveSpeed;
            break;

        case GLUT_KEY_PAGE_DOWN:
            carZ += moveSpeed;
            break;
    }

    // Auto-center steering
    if (key != GLUT_KEY_LEFT && key != GLUT_KEY_RIGHT) {
        wheelSteerAngle *= 0.85f; // smooth return
    }

    glutPostRedisplay();
}

//arc motion for car
void updateCar() {
    float rad = carAngle * M_PI / 180.0f;

    // move forward in the direction the car is facing
    carX -= carSpeed * cos(rad);
    carZ += carSpeed * sin(rad);

    // Rotate wheels based on speed
    wheelRotation += carSpeed * 50.0f; // multiplier controls spin speed

    // natural slowing down
    carSpeed *= 0.95f;

    // speed limits (IMPORTANT)
    if (carSpeed > 0.5f)  carSpeed = 0.45f;   // max forward speed
    if (carSpeed < -0.3f) carSpeed = -0.25f;  // max reverse speed
}



// Reshaping window (from both files)
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Lighting and setup (from environment.cpp init)
void init() {
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f); //sky color

    // Lighting setup
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = {10, 50, 10, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    GLfloat ambient[] = {0.5, 0.5, 0.5, 1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

}

// Redrawing window (The main drawing loop)
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    updateCar(); //added to car turning functionality

    // Camera setup
    gluLookAt(
        -5.0f, 25.0f, 15.0f,   // eye
        -5.0f, 0.0f, -25.0f,    // center
        0.0f, 1.0f, 0.0f    // up
    );

    // Call drawing functions from other modules
    drawEnvironment(); // Defined in Environment.cpp
    drawCar();         // Defined in Car.cpp

    glutSwapBuffers();
}

// Main function (from both files)
int main(int argc, char** argv) {
    // Print instructions to console
    std::cout << "********** 3D Car Simulation Controls **********\n\n";
    std::cout << "Arrow Up    : Accelerate / Move Forward\n";
    std::cout << "Arrow Down  : Brake / Reverse\n";
    std::cout << "Arrow Left  : Turn Left\n";
    std::cout << "Arrow Right : Turn Right\n\n";
    std::cout << "**********************************************\n\n";

    //initializing GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Race Car speeding");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
