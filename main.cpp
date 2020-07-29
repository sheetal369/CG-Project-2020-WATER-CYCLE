#include <windows.h>
#include <GL/glut.h>

/* Global variables */
char title[] = "[CG Project] WATER CYCLE";
int refreshMills = 360;        // refresh interval in milliseconds
GLfloat z = -2.0;

GLfloat sunRadius = 0.115;
GLfloat dx = 0;

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest

   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test

   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void Cloud()
{


}
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   //SUN
   glLoadIdentity();                 // Reset the model-view matri
   glColor3f(1.0, 1.0, 0.0);
   glTranslatef(-2+4*sunRadius, 1-3*sunRadius, -3.0);
   glutSolidSphere(sunRadius, 100, 100);

   //SEA
   glLoadIdentity();
   glColor3f(0.31,0.26,1.0);
   glBegin(GL_POLYGON);
      glVertex3f(2, -0.5, -5);
      glVertex3f(-2, -0.5, -5);
      glVertex3f(-2, -1, -5);
      glVertex3f(2, -1, -5);
   glEnd();

   //GRASS
   glLoadIdentity();
   glColor3f(0.6,0.8,0.196078);
   glBegin(GL_POLYGON);
      glVertex3f(2, -0.3, -5);
      glVertex3f(-2, 0.0, -5);
      glVertex3f(-2, -0.5, -5);
      glVertex3f(2, -0.5, -5);
   glEnd();

   //SKY
   glLoadIdentity();
   glColor3f(0.53,0.81,0.92);
   glBegin(GL_POLYGON);
      glVertex3f(2, 1, -5);
      glVertex3f(-2, 1, -5);
      glVertex3f(-2, 0.0, -5);
      glVertex3f(2, -0.3, -5);
   glEnd();

   Cloud();
   glutSwapBuffers();
}

/* Called back when timer expired [NEW] */
void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
    if (width >= height) {
      glOrtho(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0, 0.1, 100);
   } else {
     glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, 0.1, 100);
   }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(1200, 600);   // Set the window's initial width & height
   glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title

   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization

   glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
